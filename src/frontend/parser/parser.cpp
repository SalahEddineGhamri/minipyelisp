#include "frontend/parser/parser.hpp"
#include "frontend/ast/ast.hpp"
#include <memory>

namespace minipyelisp::parser {

Parser::Parser(const std::vector<lexer::Token> &tokens) : tokens(tokens) {}

std::unique_ptr<ast::ASTNode> Parser::parse() { return parse_expression(); }

std::unique_ptr<ast::Expression> Parser::parse_expression() {
  auto lhs = parse_primary();
  if (!lhs) {
    return nullptr;
  }

  while (true) {
    const auto &op_token = tokens[current_pos];
    if (op_token.type != lexer::TokenType::OP_PLUS &&
        op_token.type != lexer::TokenType::OP_MINUS) {
      break;
    }
    current_pos++;
    auto rhs = parse_primary();
    if (!rhs) {
      return nullptr;
    }
    lhs = std::make_unique<ast::BinaryExpression>(op_token.value[0], std::move(lhs),
                                                 std::move(rhs));
  }

  return lhs;
}

std::unique_ptr<ast::Expression> Parser::parse_primary() {
  const auto &token = tokens[current_pos++];
  if (token.type == lexer::TokenType::INT_LITERAL ||
      token.type == lexer::TokenType::FLOAT_LITERAL) {
    return std::make_unique<ast::NumberExpression>(
        std::stod(token.value));
  } else if (token.type == lexer::TokenType::IDENTIFIER) {
    return std::make_unique<ast::VariableExpression>(token.value);
  }
  return nullptr;
}

} // namespace minipyelisp::parser
