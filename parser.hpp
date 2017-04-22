#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>

#include "token.hpp"

namespace parser {
  std::unique_ptr<token::Token> parse(const std::string& input);
}
#endif
