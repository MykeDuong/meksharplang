#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <set>
#include <iostream>

#include "./TokenType.h"

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

