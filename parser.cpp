#ifndef PARSER
#define PARSER

#include "parser.hpp"

#define TOKEN_LIST true
#define BACK_TWO -2

namespace parser {
  auto normalize(const std::string& input) {
    auto parens_regex = std::regex("\\)|\\(");
    return std::regex_replace(input, parens_regex, " $& ");
  }

  auto tokenize(const std::string& input) {
    return std::stringstream(normalize(input));
  }

  std::unique_ptr<token::Token> parse_tokens(std::stringstream& tokens) {
    std::string token_str;
    auto token_list = token::create_token(TOKEN_LIST);
    tokens >> token_str;
    if (token_str == "(") {
      auto close_paren_found = false;
      while (tokens >> token_str) {
	if (token_str == ")") {
	  close_paren_found = true;
	} else if (token_str == "(") {
	  tokens << "( ";
	  tokens.seekg(BACK_TWO, tokens.cur);
	  token_list->list.push_back(parse_tokens(tokens));
	} else {
	  token_list->list.push_back(token::create_token(token_str));
	}
	if (close_paren_found)
	  return token_list;
      }
      // We only get here if there is an missing )
      //  otherwise this code doesn't execute
      std::cout << "Missing \")\": " << tokens.str() << "\"\n";
      // Can't return token_list because it may
      //  have been modified
      return token::create_token("Missing \")\": " + tokens.str());
    } else {
      if (tokens >> token_str) {
	std::cout << "S-expression require (): \"" << tokens.str() << "\"\n";
	return token::create_token("S-expression require (): \"" + tokens.str());
      } else {
	token_list->list.push_back(token::create_token(token_str));
      }
      // Can safely return token_list because it will
      //  either be empty of have one token it
      return token_list;
    }
  }
}

std::unique_ptr<token::Token> parser::parse(const std::string& input) {
  auto tokens = tokenize(input);
  auto parsed_tokens = parse_tokens(tokens);
  return parsed_tokens;
}
#endif
