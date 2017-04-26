#ifndef EVAL
#define EVAL

#include "eval.hpp"
#include "scope.hpp"

namespace risp_eval {
  typedef std::function<token::UniqueTokenPointer(token::UniqueTokenPointer)> LibraryFunc;
  typedef std::map<std::string, LibraryFunc> StandardLibrary;

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

  template <class T>
  auto resolve_token_list_then_apply(token::UniqueTokenPointer token_list, T function) {
    auto resolved_tokens = std::vector<token::UniqueTokenPointer>();
    std::transform(std::begin(token_list->list), std::end(token_list->list),
		   std::back_inserter(resolved_tokens),[] (auto& a_token) {
		     return eval(std::move(a_token));
		   });
    return function(std::move(resolved_tokens));
  }
  
  StandardLibrary Library = {
    {"+", [](auto args) {
	return resolve_token_list_then_apply(std::move(args), add_tokens);
      }},

    {"-", [](auto args) {
	return resolve_token_list_then_apply(std::move(args), subtract_tokens);
      }},
    {"*", [](auto args) {
	return resolve_token_list_then_apply(std::move(args), multiply_tokens);
      }},
    {"/", [](auto args) {
	return resolve_token_list_then_apply(std::move(args), divide_tokens);
      }},
    {"let", [](auto args) {
	token::print_token(args->list[0]);
	return token::create_token("let");
	}}
  };

  auto eval_token_list(token::UniqueTokenPointer token_list, scope::UniqueScopePointer scope) {
    auto first_token = std::move(token_list->list[0]);
    token_list->list.erase(token_list->list.begin());
    if (first_token->type == token::TokenType::IDENTIFIER) {
      const auto library_function = Library.find(first_token->value);
      if (library_function != Library.end()) {
	return library_function->second(std::move(token_list));
      }
      auto scope_variable = scope::search_scope(scope, first_token->value);
      std::cout << scope_variable->value << std::endl;
      return scope_variable;
    }
    return first_token;
  }

  auto eval_token_general(token::UniqueTokenPointer token,  scope::UniqueScopePointer scope) {
    return token;
  }

  token::UniqueTokenPointer eval(token::UniqueTokenPointer token) {
    switch(token->type) {
    case token::TokenType::LIST:
      return eval_token_list(std::move(token), scope::create_scope());
    case token::TokenType::INTEGER:
    case token::TokenType::FLOAT:
    case token::TokenType::STRING:
    case token::TokenType::IDENTIFIER:
      return eval_token_general(std::move(token), scope::create_scope());
    }
  }
}
#endif

