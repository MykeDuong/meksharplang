#include <string>

#ifndef TOKEN_H
#define TOKEN_H

enum TokenType { 
  TOKEN_NUMBER
};

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
};

#endif 

