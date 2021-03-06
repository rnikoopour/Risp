#include <iostream>
#include <string>
#include <utility>

#include "external/linenoise.hpp"

#include "token.hpp"
#include "parser.hpp"
#include "eval.hpp"

struct Input {
  std::string input;
  bool should_exit;
};

auto read() {
  std::string input;
  auto should_exit = linenoise::Readline("risp> ", input);
  return Input{input, should_exit};
}


auto eval(const std::string& input) {
  auto parsed_tokens = parser::parse(input);
  auto result = std::accumulate(std::begin(parsed_tokens->list), std::end(parsed_tokens->list),
				token::create_token("EMPTY PARSED TOKENS"),
				[](auto& acc, auto& token) {
				  auto result = risp_eval::eval(std::move(token));
				  token::print_token(result);
				  return result;
				});
  return result;
}

int main(int argc, char* argv[]) {
  std::cout << "Risp v0.0.1\n"
	    << "Press ctrl-c to exit\n\n";

  linenoise::SetMultiLine(true);
  
  while(true) {
    auto input = read();
    if (input.should_exit) break;
    auto result = eval(input.input);
    linenoise::AddHistory(input.input.c_str());
  }
}
