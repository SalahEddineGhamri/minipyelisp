#ifndef MINIPYELISP_TOKEN_HPP
#define MINIPYELISP_TOKEN_HPP

#include <string>

namespace minipyelisp {
namespace lexer {

// TODO: add more types based on the scope of minipython
// token types
enum class TokenType {
  // Keywords
  KW_IF,
  KW_ELSE,
  KW_DEF,
  KW_RETURN,
  KW_WHILE,
  KW_TRUE,
  KW_FALSE,
  KW_NONE,

  // Operators
  OP_PLUS,
  OP_MINUS,
  OP_STAR,
  OP_SLASH,
  OP_EQ,
  OP_NE,
  OP_LT,
  OP_LE,
  OP_GT,
  OP_GE,
  OP_ASSIGN,
  OP_DOT,
  OP_COMMA,
  OP_COLON,
  OP_SEMICOLON,

  // Delimiters
  PAREN_OPEN,
  PAREN_CLOSE,
  BRACE_OPEN,
  BRACE_CLOSE,
  BRACKET_OPEN,
  BRACKET_CLOSE,

  // Literals
  IDENTIFIER,
  INT_LITERAL,
  FLOAT_LITERAL,
  STRING_LITERAL,

  NEWLINE,
  INDENT,
  DEDENT,
  END_OF_FILE,
  UNKNOWN
};

// plain old data Token
struct Token {

  TokenType type;
  std::string value;

  // TODO: for debug reasons we can add line and character numbers
  Token(TokenType type, std::string value)
      : type(type), value(std::move(value)) {}

  std::string to_string() const;
};

} // namespace lexer
} // namespace minipyelisp

#endif // MINIPYELISP_TOKEN_HPP
