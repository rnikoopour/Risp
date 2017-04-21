#ifndef PARSER_HPP
#define PARSER_HPP

#include "token.hpp"

namespace parser {
  template <typename T> auto create_token(const T& value);
  auto normalize(const std::string& input);
  auto tokenize(const std::string& input);
  token::Token parse(const std::string& input);
  token::Token parse_tokens(std::stringstream& tokens);
}
#endif
