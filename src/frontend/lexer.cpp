
#include "frontend/lexer.hpp"
#include "token.hpp"
#include <cctype>
#include <iostream>
#include <map>

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

static const std::map<std::string, TokenType> keywords = {
    {"if", TokenType::KW_IF},       {"else", TokenType::KW_ELSE},
    {"def", TokenType::KW_DEF},     {"return", TokenType::KW_RETURN},
    {"while", TokenType::KW_WHILE}, {"True", TokenType::KW_TRUE},
    {"False", TokenType::KW_FALSE}, {"None", TokenType::KW_NONE}};

Token Lexer::read_identifier_or_keyword() {
  /*
    - keywords: strings defined in the language
    - indetifiers: strings created by the user (variables, functions)
   */
  std::string id_str;
  // identifiers star always with alpha but can contain digit or _
  while (!is_eof() && (std::isalnum(peek()) || peek() == '_')) {
    id_str += consume();
  }
  // look for id_str in keywords
  // if found it will point to something, else is the end
  auto it = keywords.find(id_str);
  if (it != keywords.end()) {
    return Token(it->second, id_str);
  }
  return Token(TokenType::IDENTIFIER, id_str);
};

Token Lexer::read_string() {
  /*
   * basically we extract text inside ' or ""
   */
  std::string str_val;

  // we are already inside ' or " we need to consume it
  char quote_char = consume();

  while (!is_eof() && peek() != quote_char) {
    str_val += consume();
  }

  // is_eof case
  if (is_eof()) {
    std::cerr << "lexer error: unterminated string (EOF reached)" << std::endl;
    return Token(TokenType::UNKNOWN, str_val);
  }

  // quote_char case
  consume(); // consume the closing quote but get rid of it

  return Token(TokenType::STRING_LITERAL, str_val);
};

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

  if (std::isalpha(c) || c == '_') {
    return read_identifier_or_keyword();
  }

  if (c == '\'' || c == '"') {
    return read_string();
  }

  // TODO: operators
  // = -> ==
  // + and -
  // :
  // ( and )

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
