#include <map>

#ifndef TOKEN_HPP
#define TOKEN_HPP
#define NEVER_PRINT "__RISP_THIS_SHOULD_NEVER_PRINT__"

namespace token {
  const auto integer_regex = std::regex("^[[:digit:]]+(\\.0+)?$");
  const auto float_regex = std::regex("^[[:digit:]]+\\.[[:digit:]]+$");  
  const auto string_regex = std::regex("\".*\"");

  enum TokenType { UNDEFINED, LIST, INTEGER, FLOAT, LITERAL, IDENTIFIER };
  const auto token_types = std::map<TokenType, std::string> {
    {TokenType::UNDEFINED, "UNDEFINED"},
    {TokenType::LIST, "LIST"},
    {TokenType::INTEGER, "INTEGER"},
    {TokenType::FLOAT, "FLOAT"},
    {TokenType::LITERAL, "LITERAL"},
    {TokenType::IDENTIFIER, "IDENTIFIER"}
  };
  TokenType discover_type(const std::string& value);

  struct Token {
    const std::string value = NEVER_PRINT;
    const bool is_list = false;
    const TokenType type = UNDEFINED;
    std::vector<Token> list;
    Token(std::string val) : value(val), type(discover_type(val)){};
    Token(bool is_a_list) : is_list(is_a_list), type(TokenType::LIST)  {};
  };
  auto get_type(const Token& token);
  void print_token(const Token& token);
}
#endif
