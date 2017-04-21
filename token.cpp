#ifndef TOKEN
#define TOKEN

#include <algorithm>
#include <iostream>
#include <map>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "token.hpp"

namespace token {
  const auto integer_regex = std::regex("^[[:digit:]]+(\\.0+)?$");
  const auto float_regex = std::regex("^[[:digit:]]+\\.[[:digit:]]+$");  
  const auto string_regex = std::regex("\".*\"");
  const auto token_types = std::map<TokenType, std::string> {
    {TokenType::UNDEFINED, "UNDEFINED"},
    {TokenType::LIST, "LIST"},
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::LITERAL, "LITERAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"},
    {TokenType::LAMBDA, "LAMBDA"}
  };

  auto get_type(const std::unique_ptr<token::Token>& token) {
    return token::token_types.find(token->type)->second;
  }

  void print_token(const std::unique_ptr<Token>& token) {
    if (token->is_list) {
      std::cout << "New list:\n";
      std::for_each(begin(token->list), end(token->list),
		    [](auto& a_token) { print_token(a_token); });
      std::cout << "End list:\n";
    } else {
      std::cout << token->value << " -- " << get_type(token) << std::endl;
    }
  }

  TokenType discover_type(const std::string& value) {
    if (std::regex_match(value, integer_regex))
      return TokenType::INTEGER;
    else if (std::regex_match(value, float_regex))
      return TokenType::FLOAT;
    else if (std::regex_match(value, string_regex))
      return TokenType::LITERAL;
    else
      return TokenType::IDENTIFIER;
  }
}




#endif
