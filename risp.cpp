#include <iostream>
#include <string>
#include <regex>
#include <sstream>
#include <algorithm>
#include <numeric>
#include <iterator>
#include "external/linenoise.hpp"

#include "token.hpp"
#include "parser.hpp"
#include "environment.hpp"

#ifndef EVAL_TOKEN_FUNCTION
#define EVAL_TOKEN_FUNCTION std::function<token::Token(token::Token&, const Library*)>
#endif

struct Input {
  std::string input;
  bool should_exit;
};

auto read() {
  std::string input;
  auto should_exit = linenoise::Readline("risp> ", input);
  return Input{input, should_exit};
}

auto eval_list(token::Token& token, const Library* library, EVAL_TOKEN_FUNCTION eval_token) {
  auto tokens = std::begin(token.list);
  auto function_name = tokens->value;
  auto library_entry = library->find(function_name);

  if (library_entry != library->end()) {
    auto function_args = std::vector<token::Token>();
    auto function = library_entry->second;
    tokens++;
    std::transform(tokens, std::end(token.list), 
		   std::back_inserter(function_args),
		   [&function_name, &eval_token, &library](auto arg) {
		     return function_name == "define" || function_name == "lambda" ?
		       arg :
		       eval_token(arg, library);
		   });
    return function(function_args);
  } else {
    auto result = std::vector<token::Token>();
    std::transform(std::begin(token.list), std::end(token.list),
		   std::back_inserter(result), [&eval_token, &library] (auto token_to_eval) {
		     return eval_token(token_to_eval, library);
		   });
    return result.back();
  }
}

token::Token eval_token(token::Token& token, const Library* library) {
  if (token.type == token::TokenType::LIST) {
    return eval_list(token, library, eval_token);
  } else if (token.type == token::TokenType::IDENTIFIER) {
    return user_value->find(token.value)->second;
  } else {
    return token;
  }
}

auto eval(const std::string& input) {
  auto parsed_tokens = parser::parse(input);
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
