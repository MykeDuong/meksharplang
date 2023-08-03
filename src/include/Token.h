#ifndef TOKEN_H
#define TOKEN_H

#include "./TokenType.h"
#include "./LiteralValue.h"
#include<string>
#include <iostream>

class Token {
  public:   
    const TokenType type;
    const std::string lexeme;
    const LiteralValue* literal;
    const int line;

  public:
    Token(TokenType type, std::string lexeme, LiteralValue* literal, int line);
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

#endif
