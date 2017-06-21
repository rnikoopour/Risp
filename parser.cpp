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

  token::UniqueTokenPointer parse_tokens(std::stringstream& tokens) {
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
      // We only get here if there is an missing ')'
      //  Can't return token_list because it may
      //  have been modified
      return token::create_token("Missing \")\": " + tokens.str());
    } else {
      // Hack to ignore the whitespace at the very end added
      //  by the regex_replace
      if (token_str != "")
	token_list->list.push_back(token::create_token(token_str));
      return token_list;
    }
  }

  token::UniqueTokenPointer parse(const std::string& input) {
    auto tokens = tokenize(input);
    auto result = token::create_token(TOKEN_LIST);
    while (!tokens.eof()) {
      auto parsed_tokens = parse_tokens(tokens);
      // If there isn't anything in the list, it's an empty
      //  token and we don't need it
      if (parsed_tokens->list.size()) 
	result->list.push_back(std::move(parsed_tokens));
    }
    return result;
  }

  namespace test {
    std::string normalize(const std::string& input) {
      return parser::normalize(input);
    }
    std::stringstream tokenize(const std::string& input) {
      return parser::tokenize(input);
    }
    token::UniqueTokenPointer parse_tokens(std::stringstream& tokens) {
      return parser::parse_tokens(tokens);
    }
  }

}

#endif
