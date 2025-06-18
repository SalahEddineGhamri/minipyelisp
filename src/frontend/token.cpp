
#include "token.hpp"
#include "frontend/lexer.hpp"
#include <map>

namespace minipyelisp::lexer {

// helper: map token types to string
static const std::map<TokenType, std::string> tokenTypeStrings = {
    /* we define strings for all the tokens we use
     */
};

std::string Token::to_string() const {

  std::string str_token = "UNKNOWN";

  if (type == TokenType::END_OF_FILE) {
    str_token = "EOF token";
  }

  if (type == TokenType::INT_LITERAL) {
    str_token = "INT token " + value;
  }

  if (type == TokenType::FLOAT_LITERAL) {
    str_token = "FLOAT token " + value;
  }

  return str_token;
};

} // namespace minipyelisp::lexer
