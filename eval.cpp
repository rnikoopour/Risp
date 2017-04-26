#ifndef EVAL
#define EVAL
#include "eval.hpp"

namespace risp_eval {
  typedef std::function<token::UniqueTokenPointer(std::vector<token::UniqueTokenPointer>)> LibraryFunc;

  auto add_tokens(std::vector<token::UniqueTokenPointer> args) {
    try {
      auto result = std::accumulate(std::begin(args), std::end(args), token::create_token("0"),
					 [](auto& acc, auto& token) {
					    if (acc->type == token::TokenType::FLOAT ||
						token->type == token::TokenType::FLOAT) {
					      const auto result = std::stod(acc->value) + std::stod(token->value);
					      return token::create_token(std::to_string(result));
					    }
					    else {
					      const auto result = std::stoi(acc->value) + std::stoi(token->value);
					      return token::create_token(std::to_string(result));
					    }
					 });
      return result;
    } catch (std::exception e) {
      return token::create_token("Can only add numbers");
    }
  }

  auto multiply_tokens(std::vector<token::UniqueTokenPointer> args) {
    try {
      auto result = std::accumulate(std::begin(args), std::end(args), token::create_token("1"),
					 [](auto& acc, auto& token) {
					    if (acc->type == token::TokenType::FLOAT ||
						token->type == token::TokenType::FLOAT) {
					      const auto result = std::stod(acc->value) * std::stod(token->value);
					      return token::create_token(std::to_string(result));
					    }
					    else {
					      const auto result = std::stoi(acc->value) * std::stoi(token->value);
					      return token::create_token(std::to_string(result));
					    }
					 });
      return result;
    } catch (std::exception e) {
      return token::create_token("Can only multiple numbers");
    }
  }

  auto subtract_tokens(std::vector<token::UniqueTokenPointer> args) {
    if (args.size() == 1) {
      if (args[0]->type == token::TokenType::FLOAT) {
	const auto value = std::stod(args[0]->value);
	return token::create_token(std::to_string(value * -1));
      } else {
	const auto value = std::stoi(args[0]->value);
	return token::create_token(std::to_string(value * -1));
      }
    } else {
      try {
	const auto start = std::begin(args);
	auto result = std::accumulate(std::next(start), std::end(args), token::create_token((*start)->value),
				      [](auto& acc, auto& token) {
					if (acc->type == token::TokenType::FLOAT ||
					    token->type == token::TokenType::FLOAT) {
					  const auto result = std::stod(acc->value) - std::stod(token->value);
					  return token::create_token(std::to_string(result));
					}
					else {
					  const auto result = std::stoi(acc->value) - std::stoi(token->value);
					  return token::create_token(std::to_string(result));
					}
				      });
	return result;
      } catch (std::exception e) {
	return token::create_token("Can only subtract numbers");
      }
    }
  }

  auto divide_tokens(std::vector<token::UniqueTokenPointer> args) {
    if (args.size() == 1) {
      const auto value = std::stod(args[0]->value);
      return token::create_token(std::to_string(1 / value));
    } else {
      try {
	const auto start = std::begin(args);
	auto result = std::accumulate(std::next(start), std::end(args), token::create_token((*start)->value),
				      [](auto& acc, auto& token) {
					const auto result = std::stod(acc->value) / std::stod(token->value);
					return token::create_token(std::to_string(result));
				      });
	return result;
      } catch (std::exception e) {
	return token::create_token("Can only divide numbers");
      }
    }
  }

  std::map<std::string, LibraryFunc> Library = {
    {"+", [](auto args) {
	return add_tokens(std::move(args));
      }},
    {"-", [](auto args) {
	return subtract_tokens(std::move(args));
      }},
    {"*", [](auto args) {
	return multiply_tokens(std::move(args));
      }},
    {"/", [](auto args) {
	return divide_tokens(std::move(args));
	}}
  };

  auto eval_token_list(token::UniqueTokenPointer token) {
    auto resolved_tokens = std::vector<token::UniqueTokenPointer>();
    std::transform(std::begin(token->list), std::end(token->list),
		   std::back_inserter(resolved_tokens),[] (auto& a_token) {
		     return eval(std::move(a_token));
		   });
    if (resolved_tokens[0]->type == token::TokenType::IDENTIFIER) {
      const auto op = std::move(resolved_tokens[0]);
      resolved_tokens.erase(resolved_tokens.begin());
      return Library.find(op->value)->second(std::move(resolved_tokens));
    }
    return token::create_token("BAD LIST");
  }

  auto eval_token_general(token::UniqueTokenPointer token) {
    return token;
  }

  token::UniqueTokenPointer eval(token::UniqueTokenPointer token) {
    switch(token->type) {
    case token::TokenType::LIST:
      return eval_token_list(std::move(token));
    case token::TokenType::INTEGER:
    case token::TokenType::FLOAT:
    case token::TokenType::STRING:
    case token::TokenType::IDENTIFIER:
      return eval_token_general(std::move(token));
    }
  }
}
#endif

