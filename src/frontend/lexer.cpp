
#include "frontend/lexer.hpp"
#include "token.hpp"
#include <cctype>

namespace minipyelisp::lexer {

Lexer::Lexer(const std::string &source_code) : source(source_code) {}

// look ahead without consuming
char Lexer::peek(size_t offset) const {
  if (current_pos + offset >= source.length()) {
    return '\0';
  }
  return source[current_pos + offset];
}

// cosume updates lexer state
char Lexer::consume() {
  if (is_eof()) {
    return '\0';
  }
  char c = source[current_pos++];
  return c;
}

void Lexer::skip_whitespace() {
  // increment if space within same line and not eof
  while (!is_eof() && (std::isspace(peek()) != 0) && peek() != '\n') {
    consume();
  }
}

// check the end of file
bool Lexer::is_eof() const { return current_pos >= source.length(); }

// tokenize number
Token Lexer::read_number() {

  // as starter INT_LITERAL or FLOAT_LITERAL
  std::string nbr_str;
  TokenType type = TokenType::INT_LITERAL;

  // int
  while (!is_eof() && std::isdigit(peek())) {
    nbr_str += consume();
  }

  // float
  if (!is_eof() && peek() == '.' && std::isdigit(peek(1))) {
    type = TokenType::FLOAT_LITERAL;
    nbr_str += consume(); // take the point
    while (!is_eof() && std::isdigit(peek())) {
      nbr_str += consume();
    }
  }

  Token result(type, nbr_str);
  return result;
}

// state machine
Token Lexer::get_next_token() {

  // skip all white spaces
  skip_whitespace();

  if (is_eof()) {
    return Token(TokenType::END_OF_FILE, "");
  }

  char c = peek();

  if (std::isdigit(c)) {
    return read_number();
  }

  /*
  if (std::isalpha(c) || c == '_'){
    return read_identifier_or_keyword();
  }

  if (c == '\'' || c == '"') {
    return read_string();
  }
  */

  // the rest ...

  Token token(TokenType::END_OF_FILE, "end of file");

  return token;
};

std::vector<Token> Lexer::tokenize() {

  std::vector<Token> tokens;
  Token token = get_next_token();

  while (token.type != TokenType::END_OF_FILE) {
    tokens.push_back(token);
    token = get_next_token();
  }

  tokens.push_back(token); // Add EOF token

  return tokens;
};

} // namespace minipyelisp::lexer
