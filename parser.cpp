#ifndef PARSER
#define PARSER

#include <map>
#include <regex>
#include <string>
#include <sstream>
#include <iostream>

#include "parser.hpp"

#define TOKEN_LIST true
#define BACK_TWO -2

template <typename T>
auto parser::create_token(const T& value) {
  return token::Token(value);
}

auto parser::normalize(const std::string& input) {
  auto parens_regex = std::regex("\\)|\\(");
  return std::regex_replace(input, parens_regex, " $& ");
}

auto parser::tokenize(const std::string& input) {
  return std::stringstream(normalize(input));
}

token::Token parser::parse_tokens(std::stringstream& tokens) {
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

token::Token parser::parse(const std::string& input) {
  auto tokens = tokenize(input);
  token::Token parsed_tokens = parse_tokens(tokens);
  return parsed_tokens;
}
#endif
