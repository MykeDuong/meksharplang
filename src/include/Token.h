#include <string>
#include <set>
#include <iostream>

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType { 
  TOKEN_NUMBER,
  TOKEN_WHITESPACE,
  TOKEN_OPERATOR,
  TOKEN_TEXT
};

const std::set<char> operators = { '+', '-', '*', '/' };

class Token {
  private:
    TokenType type;
    int position = position;
    std::string text;

  public:
    Token(TokenType type, int position, std::string text);
    TokenType getType();
    int getPosition();
    std::string getText();
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};
#endif 

