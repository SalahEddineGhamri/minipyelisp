
#include "token.hpp"
#include "frontend/lexer.hpp"
#include <map>

namespace minipyelisp::lexer {

// helper: map token types to string
static const std::map<TokenType, std::string> tokenTypeStrings = {
    /* we define strings for all the tokens we use */
    {TokenType::END_OF_FILE, "EOF token"},
    {TokenType::INT_LITERAL, "INT token"},
    {TokenType::FLOAT_LITERAL, "FLOAT token"},
    {TokenType::IDENTIFIER, "IDENTIFIER token"},
    {TokenType::KW_ELSE, "ELSE token"},
    {TokenType::KW_DEF, "DEF token"},
    {TokenType::KW_IF, "IF token"},
    {TokenType::STRING_LITERAL, "STRING token"},
    {TokenType::OP_PLUS, "PLUS token"},
    {TokenType::OP_MINUS, "MINUS token"},
    {TokenType::OP_EQ, "EQUAL token"},
    {TokenType::OP_ASSIGN, "ASSIGN token"},
    {TokenType::OP_COLON, "COLON token"},
    {TokenType::NEWLINE, "NEWLINE token"},
    {TokenType::PAREN_OPEN, "PAREN OPEN token"},
    {TokenType::PAREN_CLOSE, "PAREN CLOSE token"},
    {TokenType::OP_COMMA, "COMMA token"},
    {TokenType::KW_RETURN, "RETURN token"},
};

std::string Token::to_string() const {

  std::string str_token = "UNKNOWN";

  auto it = tokenTypeStrings.find(type);
  if (it != tokenTypeStrings.end()) {
    return it->second + " " + value;
  }

  return str_token;
};

} // namespace minipyelisp::lexer
