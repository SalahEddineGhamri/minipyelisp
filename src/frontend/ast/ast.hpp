#ifndef MINIPYELISP_AST_HPP
#define MINIPYELISP_AST_HPP

#include <memory>
#include <string>
#include <vector>

namespace minipyelisp::ast {

// Base class for all AST nodes
class ASTNode {
public:
  virtual ~ASTNode() = default;
  virtual bool equals(const ASTNode *other) const = 0;
};

// Expressions
class Expression : public ASTNode {};

class NumberExpression : public Expression {
public:
  NumberExpression(double value) : value(value) {}
  double getValue() const { return value; }
  bool equals(const ASTNode *other) const override;

private:
  double value;
};

class VariableExpression : public Expression {
public:
  VariableExpression(const std::string &name) : name(name) {}
  const std::string &getName() const { return name; }
  bool equals(const ASTNode *other) const override;

private:
  std::string name;
};

class BinaryExpression : public Expression {
public:
  BinaryExpression(char op, std::unique_ptr<Expression> lhs,
                   std::unique_ptr<Expression> rhs)
      : op(op), lhs(std::move(lhs)), rhs(std::move(rhs)) {}
  bool equals(const ASTNode *other) const override;

private:
  char op;
  std::unique_ptr<Expression> lhs, rhs;
};

// Statements
class Statement : public ASTNode {};

class ExpressionStatement : public Statement {
public:
  ExpressionStatement(std::unique_ptr<Expression> expression)
      : expression(std::move(expression)) {}
  bool equals(const ASTNode *other) const override;

private:
  std::unique_ptr<Expression> expression;
};

} // namespace minipyelisp::ast

#endif // MINIPYELISP_AST_HPP
