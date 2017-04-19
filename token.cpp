#ifndef TOKEN
#define TOKEN

#include <iostream>
#include <string>
#include <iostream>
#include <map>
#include <regex>

#include "token.hpp"

auto token::get_type(Token token){
    return token_types.find(token.type)->second;
  }

void token::print_token(Token& token) {
    if (token.is_list) {
      std::cout << "New list:\n";
      std::for_each(begin(token.list), end(token.list),
		    [](auto a_token) { print_token(a_token); });
      std::cout << "End list:\n";
    } else {
      std::cout << token.value << " -- " << get_type(token) << std::endl;
    }
  }

token::TokenType token::discover_type(std::string& value) {
    if (std::regex_match(value, integer_regex))
      return TokenType::INTEGER;
    else if (std::regex_match(value, float_regex))
      return TokenType::FLOAT;
    else if (std::regex_match(value, string_regex))
      return TokenType::LITERAL;
    else
      return TokenType::IDENTIFIER;
  }

#endif
