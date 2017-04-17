#ifndef TOKEN
#define TOKEN
#include <string>
#include <iostream>
#include <map>
#include <regex>

#define NEVER_PRINT "__RISP_THIS_SHOULD_NEVER_PRINT__"

namespace token {
  const auto number_regex = std::regex("^[[:digit:]]+$");
  const auto string_regex = std::regex("\".*\"");

  enum TokenType { UNDEFINED, LIST, LITERAL, IDENTIFIER };
  const auto token_types = std::map<TokenType, std::string> {
    {TokenType::UNDEFINED, "UNDEFINED"},
    {TokenType::LIST, "LIST"},
    {TokenType::LITERAL, "LITERAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"}
  };

  struct Token {
    const std::string value = NEVER_PRINT;
    const bool is_list = false;
    std::vector<Token> list;
    const TokenType type = UNDEFINED;
    Token(std::string val) : value(val), type(discover_type(val)){};
    Token(bool is_a_list) : is_list(is_a_list), type(TokenType::LIST)  {};
    TokenType discover_type(std::string& value) {
      if (std::regex_match(value, number_regex) ||
	  std::regex_match(value, string_regex))
	return TokenType::LITERAL;
      else
	return TokenType::IDENTIFIER;
    }
  };

  auto get_type(Token token) {
    return token_types.find(token.type)->second;
  }
}
#endif
