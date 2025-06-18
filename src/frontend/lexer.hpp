// src/frontend/Lexer.hpp
#ifndef MINIPYELISP_LEXER_HPP
#define MINIPYELISP_LEXER_HPP

#include "frontend/token.hpp"
#include <vector>

namespace minipyelisp::lexer {

// class Lexer
class Lexer {
public:
  explicit Lexer(const std::string &source_code);
  std::vector<Token> tokenize();

private:
  const std::string &source;
  size_t current_pos = 0;
  [[nodiscard]] char peek(size_t offset = 0) const;
  char consume();
  [[nodiscard]] bool is_eof() const;
  void skip_whitespace();
  Token get_next_token();

  // read helpers
  Token read_number();
  Token read_identifier_or_keyword();
  Token read_string();
};

} // namespace minipyelisp::lexer

#endif // minipyelisp lexer hpp
