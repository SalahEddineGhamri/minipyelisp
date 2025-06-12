/*
 * minipyelisp
 */

#include "frontend/lexer.hpp"
#include "token.hpp"
#include <iostream>

int main() {

  /*
  std::string source = "x = 10 + 20\n"
                       "if x == 30:\n"
                       "    print(\"Hello\")\n"
                       "else:\n"
                       "    y = 'world'\n"
                       "    # This is a comment\n"
                       "def foo(a, b):\n"
                       "    return a + b\n";
  */

  std::string source = " 20.0 \n";

  minipyelisp::lexer::Lexer lexer(source);

  std::vector<minipyelisp::lexer::Token> tokens = lexer.tokenize();

  // to debug
  for (const auto &token : tokens) {
    std::cout << token.to_string() << std::endl;
  }
}
