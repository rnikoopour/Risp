#ifndef PARSER_HPP
#define PARSER_HPP
#include <iostream>
#include <memory>
#include <regex>
#include <sstream>
#include <string>

#include "token.hpp"

namespace parser {
  token::UniqueTokenPointer parse(const std::string& input);
  namespace test {
    std::string normalize(const std::string& input);
    std::stringstream tokenize(const std::string& input);
    token::UniqueTokenPointer parse_tokens(std::stringstream& tokens);
  }
}
#endif
