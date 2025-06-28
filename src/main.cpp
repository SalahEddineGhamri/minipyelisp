/*
 * minipyelisp
 */

#include "frontend/lexer.hpp"
#include "token.hpp"
#include <algorithm>
#include <iostream>

int main() {

  std::string source = "x = 10 + 20\n"
                       "if x == 30:\n"
                       "    print(\"Hello\")\n"
                       "else:\n"
                       "    y = 'world'\n"
                       "    # This is a comment\n"
                       "def foo(a, b):\n"
                       "    return a + b\n";

  minipyelisp::lexer::Lexer lexer(source);

  std::vector<minipyelisp::lexer::Token> tokens = lexer.tokenize();

  std::for_each(tokens.begin(), tokens.end(),
                [](minipyelisp::lexer::Token &token) {
                  std::cout << token.to_string() << std::endl;
                });
}
