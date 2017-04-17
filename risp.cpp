#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "external/linenoise.hpp"

#include "token.hpp"
#include "environment.hpp"

#define TOKEN_LIST true
#define BACK_TWO -2

struct Input {
  std::string input;
  bool should_exit;
};

template <typename T>
auto create_token(T value) {
  return token::Token(value);
}

auto read() {
  std::string input;
  auto should_exit = linenoise::Readline("risp> ", input);
  return Input{input, should_exit};
}

auto normalize(std::string& input) {
  auto parens_regex = std::regex("\\)|\\(");
  return std::regex_replace(input, parens_regex, " $& ");
}

auto tokenize(std::string& input) {
  std::cout << normalize(input) << std::endl;
  return std::stringstream(normalize(input));
}

token::Token parse_tokens(std::stringstream& tokens) {
  std::string token_str;
  auto token_list = create_token(TOKEN_LIST);
  tokens >> token_str;
  if (token_str == "(") {
    auto close_paren_found = false;
    while (tokens >> token_str) {
      if (token_str == ")") {
	close_paren_found = true;
      } else if (token_str == "(") {
	tokens << "( ";
	tokens.seekg(BACK_TWO, tokens.cur);
	token_list.list.push_back(parse_tokens(tokens));
      } else {
	token_list.list.push_back(create_token(token_str));
      }
      if (close_paren_found)
	return token_list;
    }
    std::cout << "Missing \")\": " << tokens.str() << "\"\n";
    // Can't return token_list because it may
    //  have been modified
    return token::Token(create_token(TOKEN_LIST));
  } else {
    if (tokens >> token_str) {
      std::cout << "S-expression require (): \"" << tokens.str() << "\"\n";
    } else {
      token_list.list.push_back(create_token(token_str));
    }
    // Can safely return token_list because it will
    //  either be empty of have one token it
    return token_list;
  }
}

auto parse(std::string input) {
  auto tokens = tokenize(input);
  token::Token parsed_tokens = parse_tokens(tokens);
  return parsed_tokens;
}

token::Token eval_token(token::Token& token, const Library* libarary) {
  if (token.type == token::TokenType::LIST) {
    auto tokens = std::begin(token.list);
    auto function_name = tokens->value;
    auto library_entry = library->find(function_name);
    if (library_entry != library->end()) {
      auto function_args = std::vector<token::Token>();
      auto function = library_entry->second;
      tokens++;
      std::transform(tokens, std::end(token.list), 
		     std::back_inserter(function_args),
		     [&function_name](auto arg) {
		       return function_name == "define" ?
			 arg :
			 eval_token(arg, library);
		     });
      return function(function_args);
    } else {
      auto result = std::vector<token::Token>();
      std::transform(std::begin(token.list), std::end(token.list),
		     std::back_inserter(result), [] (auto token_to_eval) {
		       return eval_token(token_to_eval, library);
		     });
      return result.back();
    }
  } else if (token.type == token::TokenType::IDENTIFIER) {
    return user_value->find(token.value)->second;
  } else {
    return token;
  }
}

auto eval(const std::string& input) {
  auto parsed_tokens = parse(input);
  //token::print_token(parsed_tokens);
  auto result = eval_token(parsed_tokens, library);
  std::cout << "Evaled: ";
  token::print_token(result);
  return 7;
}

int main(int argc, char* argv[]) {
  std::cout << "Risp v0.0.1\n"
	    << "Press ctrl-c to exit\n\n";

  linenoise::SetMultiLine(true);
  
  while(true) {
    auto input = read();
    if (input.should_exit) break;
    eval(input.input);
    linenoise::AddHistory(input.input.c_str());
  }
}
