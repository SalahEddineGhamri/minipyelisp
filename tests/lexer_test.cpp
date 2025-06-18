#include "frontend/lexer.hpp"
#include "frontend/token.hpp"
#include <gtest/gtest.h>

using namespace minipyelisp::lexer;

// define a test case
struct TokenizeTestCase {
  std::string input;
  std::vector<Token> expected_tokens;
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
  // size - 1 due the presence of EOF Token
  for (size_t i = 0; i < tokens.size() - 1; ++i) {
    EXPECT_EQ(tokens[i].type, param.expected_tokens[i].type);
    EXPECT_EQ(tokens[i].value, param.expected_tokens[i].value);
  }
}

// test suite with param
INSTANTIATE_TEST_SUITE_P(
    LiteralTests, LexerTest,
    ::testing::Values(
        TokenizeTestCase{
            "20", {Token(TokenType::INT_LITERAL, "20")}, "integer_20"},
        TokenizeTestCase{
            "20.0", {Token(TokenType::FLOAT_LITERAL, "20.0")}, "float_20_0"},
        TokenizeTestCase{" this ",
                         {Token(TokenType::IDENTIFIER, "this")},
                         "identifier_this"},
        TokenizeTestCase{
            "th0_", {Token(TokenType::IDENTIFIER, "th0_")}, "identifier_th0_"},
        TokenizeTestCase{"if", {Token(TokenType::KW_IF, "if")}, "keyword_if"},
        TokenizeTestCase{
            "def", {Token(TokenType::KW_DEF, "def")}, "keyword_def"},
        TokenizeTestCase{"\"Hello\"",
                         {Token(TokenType::STRING_LITERAL, "Hello")},
                         "string_single_quote"}),
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
