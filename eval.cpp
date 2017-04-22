#ifndef EVAL
#define EVAL
#include "eval.hpp"

namespace risp_eval {
  typedef std::function<token::UniqueTokenPointer(const std::vector<token::UniqueTokenPointer>&)> LibraryFunc;


  auto add_ints(const std::vector<token::UniqueTokenPointer>& args) {
    try {
      const auto result = std::accumulate(std::begin(args), std::end(args), 0,
					 [](auto acc, auto& token) {
					    return acc + std::stoi(token->value);
					 });
      return token::create_token(std::to_string(result));
    } catch (std::exception e) {
      return token::create_token("Can only add same typed value");
    }
  }

  auto add_floats(const std::vector<token::UniqueTokenPointer>& args) {
    try {
      const auto result = std::accumulate(std::begin(args), std::end(args), 0.0,
					 [](auto acc, auto& token) {
					    return acc + std::stod(token->value);
					 });
      return token::create_token(std::to_string(result));
    } catch (std::exception e) {
      return token::create_token("Can only add same typed value");
    }
  }

  auto add_tokens(const std::vector<token::UniqueTokenPointer>& args) {
    auto add_args = [&]() {
      switch(args[0]->type) {
      case token::TokenType::INTEGER:
      return add_ints(args);
      case token::TokenType::FLOAT:
      return add_floats(args);
      }
    };
    return add_args();
  }

  std::map<std::string, LibraryFunc> Library = {
    {"+", [](const auto& args) {
	return add_tokens(args);
      }}
  };

  auto eval_token_list(token::UniqueTokenPointer& token) {
    auto resolved_tokens = std::vector<token::UniqueTokenPointer>();
    std::transform(std::begin(token->list), std::end(token->list),
		   std::back_inserter(resolved_tokens),[] (auto& a_token) {
		     return eval(a_token);
		   });
    if (resolved_tokens[0]->type == token::TokenType::IDENTIFIER) {
      const auto op = std::move(resolved_tokens[0]);
      resolved_tokens.erase(resolved_tokens.begin());
      return Library.find(op->value)->second(resolved_tokens);
    }
    return token::create_token("BAD LIST");

  }

  auto eval_token_general(token::UniqueTokenPointer& token) {
    return std::move(token);
  }

  token::UniqueTokenPointer eval(token::UniqueTokenPointer& token) {
    switch(token->type) {
    case token::TokenType::LIST:
      return eval_token_list(token);
    case token::TokenType::INTEGER:
    case token::TokenType::FLOAT:
    case token::TokenType::STRING:
    case token::TokenType::IDENTIFIER:
      return eval_token_general(token);
    }
  }
}
#endif

