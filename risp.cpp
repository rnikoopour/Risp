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
  token::print_token(risp_eval::eval(std::move(parsed_tokens)));
}

int main(int argc, char* argv[]) {
  std::cout << "Risp v0.0.1\n"
	    << "Press ctrl-c to exit\n\n";

  linenoise::SetMultiLine(true);
  
  while(true) {
    auto input = read();
    if (input.should_exit) break;
    eval(input.input);
    linenoise::AddHistory(input.input.c_str());
  }
}
