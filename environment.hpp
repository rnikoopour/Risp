#include <sstream>
#include <string>
#include "token.hpp"

#define Library std::map<std::string, std::function<token::Token(std::vector<token::Token>&)>>
#define UserValue std::map<std::string, token::Token>
#define DEFINE_START "__RISP_DEFINE_START__"

#define NewDefinition(key, value) std::pair<std::string, token::Token>(key, value)
#define StreamToString(stream) std::string(stream.str())

auto user_value = new UserValue{};

auto library = new Library({
  {"+", [](auto& token_list) {
      const auto total = std::accumulate(std::begin(token_list), std::end(token_list), 0, 
					 [](auto acc, auto token) { return acc + stoi(token.value); });
      std::stringstream total_str;
      total_str << total;
      return token::Token(StreamToString(total_str));
    }},
  {"*", [](auto& token_list) {
      const auto total = std::accumulate(std::begin(token_list), std::end(token_list), 1, 
					 [](auto acc, auto token) { return acc * stoi(token.value); });
      std::stringstream total_str;
      total_str << total;
      return token::Token(StreamToString(total_str));
    }},
  {"-", [](auto& token_list) {
      auto iterator = std::begin(token_list);
      const auto start_value = stoi(iterator->value);
      iterator++;
      const auto total = std::accumulate(iterator, std::end(token_list), start_value, 
					 [](auto acc, auto token) { return acc - stoi(token.value); });
      std::stringstream total_str;
      total_str << total;
      return token::Token(StreamToString(total_str));
    }},
  {"/", [](auto& token_list) {
      auto iterator = std::begin(token_list);
      const auto start_value = stod(iterator->value);
      iterator++;
      try {
	const auto total = std::accumulate(iterator, std::end(token_list), start_value, 
					   [](auto acc, auto token) { return acc / stod(token.value); });
	std::stringstream total_str;
	total_str << total;
	return token::Token(StreamToString(total_str));
      } catch (std::exception& e) {
	return token::Token(std::string("Bad Division"));
      }
    }},
  {"define", [](auto& token_list) {
      auto define_state = DEFINE_START;
      std::accumulate(std::begin(token_list), std::end(token_list), std::string(define_state),
		      [](auto acc, auto token) {
			if (acc == DEFINE_START) {
			  return token.value;
			} else {
			  std::cout << "Adding key: " << acc << std::endl;
			  user_value->insert(NewDefinition(acc, token));
			  return std::string(DEFINE_START);
			}
		      });
      if (define_state == DEFINE_START) {
	return token_list.back();
      } else {
	return token::Token(std::string("Bad Define"));
      }
    }}
});

namespace env {
  struct Environment {
  };
}
