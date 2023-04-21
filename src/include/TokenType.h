#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

enum TokenType { 
  TOKEN_NUMBER,
  TOKEN_WHITESPACE,
  TOKEN_TEXT,
  TOKEN_BINARY_OPERATOR,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_LEFT_PARENTHESIS,
  TOKEN_RIGHT_PARENTHESIS,
  TOKEN_BAD,
  TOKEN_EOF
};

#endif