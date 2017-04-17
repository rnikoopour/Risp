#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>
#include <numeric>
#include "external/linenoise.hpp"

#include "token.hpp"

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

auto print() {
  std::cout << "risp> ";
  return true;
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

void print_token(token::Token& token) {
  if (token.is_list) {
    std::cout << "New list:\n";
    std::for_each(begin(token.list), end(token.list),
		  [](auto a_token) { print_token(a_token); });
    std::cout << "End list:\n";
  } else {
    std::cout << token.value << " -- " << get_type(token) << std::endl;
  }
}

auto parse(std::stringstream& tokens) {
  token::Token parsed_tokens = parse_tokens(tokens);
  return parsed_tokens;
}

auto eval(std::string& input) {
  auto tokens = tokenize(input);
  auto parsed_tokens = parse(tokens);
  print_token(parsed_tokens);
  return 7;
}

int main(int argc, char* argv[]) {
  std::cout << "Risp v0.0.1\n"
	    << "Press ctrl-c to exit\n\n";

  linenoise::SetMultiLine(true);
  
  while(true) {
    auto input = read();
    std::cout << "here\n";
    if (input.should_exit) break;
    eval(input.input);
    linenoise::AddHistory(input.input.c_str());
  }
}
