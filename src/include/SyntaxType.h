#ifndef SYNTAX_TYPE_H
#define SYNTAX_TYPE_H

#include <iostream>

enum SyntaxType {
  // TOKENs
  TOKEN_NUMBER = 0,
  TOKEN_WHITESPACE,
  TOKEN_TEXT,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_LEFT_PARENTHESIS,
  TOKEN_RIGHT_PARENTHESIS,
  TOKEN_BAD,
  TOKEN_EOF,
  
  // Expressions
  EXPRESSION_BINARY_OPERATOR,
  EXPRESSION_NUMBER
};

std::ostream& operator<<(std::ostream& out, const SyntaxType value);

#endif
