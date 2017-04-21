#ifndef TOKEN_HPP
#define TOKEN_HPP
#define NEVER_PRINT "__RISP_THIS_SHOULD_NEVER_PRINT__"
namespace token {
  enum TokenType { UNDEFINED, LIST, INTEGER, FLOAT, LITERAL, IDENTIFIER, LAMBDA };
  TokenType discover_type(const std::string& value);

  struct Token {
    const std::string value = NEVER_PRINT;
    const bool is_list = false;
    const TokenType type = UNDEFINED;
    std::vector<std::unique_ptr<Token>> list;
    Token(std::string val) : value(val), type(discover_type(val)) {std::cout << "string\n";};
    Token(bool is_a_list) : is_list(is_a_list), type(TokenType::LIST) {std::cout << "list\n";};
    ~Token() { std::cout << "deleted\n"; };
  };

  void print_token(const std::unique_ptr<Token>& token);

  template <typename T>
  auto create_token(const T& value) {
    return std::make_unique<token::Token>(value);
  }
}
#endif
