#ifndef TOKEN_HEADER
#define TOKEN_HEADER

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

  struct Token {
    const std::string value = NEVER_PRINT;
    const bool is_list = false;
    std::vector<Token> list;
    const TokenType type = UNDEFINED;
    Token(std::string val) : value(val), type(discover_type(val)){};
    Token(bool is_a_list) : is_list(is_a_list), type(TokenType::LIST)  {};
    TokenType discover_type(std::string& value);
  };

  auto get_type(Token token);

  void print_token(Token& token);
}
#endif
