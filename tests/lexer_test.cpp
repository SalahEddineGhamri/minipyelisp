#include "frontend/lexer.hpp"
#include "frontend/token.hpp"
#include <gtest/gtest.h>

using namespace minipyelisp::lexer;

TEST(LexerTest, TokenizeIntegerLiteral) {
  std::string input = "20";
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();

  EXPECT_EQ(tokens[0].type, TokenType::INT_LITERAL);
  EXPECT_EQ(tokens[0].value, "20");
}

TEST(LexerTest, TokenizeFloatLiteral) {
  std::string input = "20.0";
  Lexer lexer(input);
  std::vector<Token> tokens = lexer.tokenize();

  EXPECT_EQ(tokens[0].type, TokenType::FLOAT_LITERAL);
  EXPECT_EQ(tokens[0].value, "20.0");
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
