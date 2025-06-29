#include "frontend/parser/parser.hpp"
#include "frontend/lexer.hpp"
#include "frontend/ast/ast.hpp"
#include <gtest/gtest.h>
#include <memory>
#include <functional>

using namespace minipyelisp;

// Define a test case structure
struct ParserTestCase {
  std::string input;
  std::function<std::unique_ptr<ast::ASTNode>()> expected_ast_factory;
  std::string name;
};

class ParserTest : public ::testing::TestWithParam<ParserTestCase> {};

TEST_P(ParserTest, Parse) {
  const auto &param = GetParam();
  lexer::Lexer lexer(param.input);
  auto tokens = lexer.tokenize();
  parser::Parser parser(tokens);
  auto ast = parser.parse();
  auto expected_ast = param.expected_ast_factory();

  ASSERT_NE(ast, nullptr);
  ASSERT_NE(expected_ast, nullptr);
  ASSERT_TRUE(ast->equals(expected_ast.get()));
}

INSTANTIATE_TEST_SUITE_P(
    ParserTests, ParserTest,
    ::testing::Values(
        ParserTestCase{"123", []() { return std::make_unique<ast::NumberExpression>(123); }, "IntegerLiteral"},
        ParserTestCase{"123.45", []() { return std::make_unique<ast::NumberExpression>(123.45); }, "FloatLiteral"},
        ParserTestCase{"my_var", []() { return std::make_unique<ast::VariableExpression>("my_var"); }, "Identifier"},
        ParserTestCase{"x + y", []() { 
            auto x = std::make_unique<ast::VariableExpression>("x");
            auto y = std::make_unique<ast::VariableExpression>("y");
            return std::make_unique<ast::BinaryExpression>('+', std::move(x), std::move(y));
        }, "SimpleBinaryExpression"}
    ),
    [](const ::testing::TestParamInfo<ParserTestCase> &info) {
      return info.param.name;
    }
);

