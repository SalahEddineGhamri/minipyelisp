#include "frontend/ast/ast.hpp"

namespace minipyelisp::ast {

bool NumberExpression::equals(const ASTNode *other) const {
  if (auto other_node = dynamic_cast<const NumberExpression *>(other)) {
    return value == other_node->value;
  }
  return false;
}

bool VariableExpression::equals(const ASTNode *other) const {
  if (auto other_node = dynamic_cast<const VariableExpression *>(other)) {
    return name == other_node->name;
  }
  return false;
}

bool BinaryExpression::equals(const ASTNode *other) const {
  if (auto other_node = dynamic_cast<const BinaryExpression *>(other)) {
    return op == other_node->op && lhs->equals(other_node->lhs.get()) &&
           rhs->equals(other_node->rhs.get());
  }
  return false;
}

bool ExpressionStatement::equals(const ASTNode *other) const {
  if (auto other_node = dynamic_cast<const ExpressionStatement *>(other)) {
    return expression->equals(other_node->expression.get());
  }
  return false;
}

} // namespace minipyelisp::ast
