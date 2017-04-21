#ifndef PARSER_HPP
#define PARSER_HPP
namespace parser {
  std::unique_ptr<token::Token> parse(const std::string& input);
}
#endif
