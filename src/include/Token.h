#include <string>
#include <set>
#include <iostream>

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType { 
  TOKEN_NUMBER,
  TOKEN_WHITESPACE,
  TOKEN_TEXT,
  TOKEN_PLUS,
  TOKEN_MINUS,
  TOKEN_STAR,
  TOKEN_SLASH,
  TOKEN_LEFT_PARENTHESIS,
  TOKEN_RIGHT_PARENTHESIS,
  TOKEN_BAD,
  TOKEN_EOF
};

class Token {
  private:
    TokenType type;
    int position = position;
    std::string text;
    void* value;

  public:
    Token(TokenType type, int position, std::string text, void* value);
    TokenType getType();
    int getPosition();
    std::string getText();
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

std::ostream& operator<<(std::ostream& os, const Token& token);
#endif 

