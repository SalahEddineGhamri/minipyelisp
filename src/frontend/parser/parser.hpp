#ifndef MINIPYELISP_PARSER_HPP
#define MINIPYELISP_PARSER_HPP

#include "frontend/ast/ast.hpp"
#include "frontend/token.hpp"
#include <memory>
#include <vector>

namespace minipyelisp::parser {

class Parser {
public:
  Parser(const std::vector<lexer::Token> &tokens);
  std::unique_ptr<ast::ASTNode> parse();

private:
  const std::vector<lexer::Token> &tokens;
  size_t current_pos = 0;

  std::unique_ptr<ast::Expression> parse_expression();
  std::unique_ptr<ast::Expression> parse_primary();
};

} // namespace minipyelisp::parser

#endif // MINIPYELISP_PARSER_HPP
