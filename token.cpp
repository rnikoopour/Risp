#ifndef TOKEN
#define TOKEN

#include "token.hpp"

namespace token {
  const auto integer_regex = std::regex("^[[:digit:]]+$");
  const auto float_regex = std::regex("^[[:digit:]]+\\.[[:digit:]]+$");  
  const auto string_regex = std::regex("\".*\"");
  const auto token_types = std::map<TokenType, std::string> {
    {TokenType::UNDEFINED, "UNDEFINED"},
    {TokenType::LIST, "LIST"},
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::STRING, "STRING"},
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
    if (std::regex_match(value, integer_regex)) {
      //std::cout << "INTEGER\n";
      return TokenType::INTEGER;
    } else if (std::regex_match(value, float_regex)) {
      //std::cout << "FLOAT\n";
      return TokenType::FLOAT;
    } else if (std::regex_match(value, string_regex)) {
      //std::cout << value << "    STRING\n";
      return TokenType::STRING;
    } else {
      //std::cout << "IDENTIFIER\n";
      return TokenType::IDENTIFIER;
    }
  }
}
#endif
