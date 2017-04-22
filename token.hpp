#ifndef TOKEN_HPP
#define TOKEN_HPP
#define NEVER_PRINT "__RISP_THIS_SHOULD_NEVER_PRINT__"

#include <algorithm>
#include <iostream>
#include <exception>
#include <map>
#include <memory>
#include <numeric>
#include <regex>
#include <string>
#include <vector>

namespace token {
  enum TokenType { UNDEFINED, LIST, INTEGER, FLOAT, STRING, IDENTIFIER, LAMBDA };
  TokenType discover_type(const std::string& value);

  struct Token {
    const std::string value = NEVER_PRINT;
    const bool is_list = false;
    const TokenType type = UNDEFINED;
    std::vector<std::unique_ptr<Token>> list;
    Token(const std::string val) : value(val), type(discover_type(val)) {};
    Token(const char* val) : value(std::string(val)), type(discover_type(val)) {};
    Token(const bool is_a_list) : is_list(is_a_list), type(TokenType::LIST) {/*std::cout << "list\n";*/};
    ~Token() { /*std::cout << "deleted\n";*/ };
  };

  template <typename T>
  auto create_token(const T& value) {
    return std::make_unique<token::Token>(value);
  }
  typedef std::unique_ptr<token::Token> UniqueTokenPointer;
  void print_token(const UniqueTokenPointer& token);


}
#endif
