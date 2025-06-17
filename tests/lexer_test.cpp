#include "frontend/lexer.hpp"
#include "frontend/token.hpp"
#include <gtest/gtest.h>

using namespace minipyelisp::lexer;

// define a test case
struct TokenizeTestCase {
  std::string input;
  TokenType expected_type;
  std::string expected_value;
  std::string name;
};

// define a test with parameters
class LexerTest : public ::testing::TestWithParam<TokenizeTestCase> {};

// test with param
TEST_P(LexerTest, TokenizeLiterals) {
  const auto &param = GetParam();
  Lexer lexer(param.input);
  auto tokens = lexer.tokenize();
  ASSERT_FALSE(tokens.empty()); // must return non empty array
  EXPECT_EQ(tokens[0].type, param.expected_type);
  EXPECT_EQ(tokens[0].value, param.expected_value);
}

// test suite with param
INSTANTIATE_TEST_SUITE_P(
    LiteralTests, LexerTest,
    ::testing::Values(TokenizeTestCase{"20", TokenType::INT_LITERAL, "20",
                                       "integer_20"},
                      TokenizeTestCase{"20.0", TokenType::FLOAT_LITERAL, "20.0",
                                       "float_20_0"}),
    // Lambda function to generate test names
    [](const ::testing::TestParamInfo<TokenizeTestCase> &info) {
      std::string name = info.param.name;
      std::replace_if(
          name.begin(), name.end(), [](char c) { return !isalnum(c); }, '_');
      return name;
    });

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
