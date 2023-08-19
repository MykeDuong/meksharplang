#ifndef TOKEN_TYPE_H
#define TOKEN_TYPE_H

#include <iostream>

enum TokenType{
  // Single-character tokens
  LEFT_PAREN = 0, RIGHT_PAREN, LEFT_SQUARE, RIGHT_SQUARE, 
  LEFT_BRACE, RIGHT_BRACE, COMMA, DOT, MINUS, PLUS, 
  SEMICOLON, SLASH, STAR, QUESTION, COLON,

  // One or two character tokens
  BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL,
  GREATER, GREATER_EQUAL, LESS, LESS_EQUAL,

  // Literals
  IDENTIFIER, STRING, NUMBER,

  // Keywords
  AND, BREAK, CLASS, ELSE, FALSE, FUN, FOR, IF, NAH, OR,
  PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE,

  END_OF_FILE
};

std::ostream& operator<<(std::ostream& out, const TokenType value);

#endif
