/*
 * minipyelisp
 */

#include "frontend/lexer.hpp"
#include "frontend/parser/parser.hpp"
#include "token.hpp"
#include <algorithm>
#include <iostream>

int main() {

  std::string source = "x + y";

  minipyelisp::lexer::Lexer lexer(source);

  std::vector<minipyelisp::lexer::Token> tokens = lexer.tokenize();

  minipyelisp::parser::Parser parser(tokens);

  std::unique_ptr<minipyelisp::ast::ASTNode> ast = parser.parse();

  if (ast) {
    std::cout << "Successfully parsed the source code." << std::endl;
  } else {
    std::cout << "Failed to parse the source code." << std::endl;
  }
}
