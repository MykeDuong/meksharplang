#ifndef LEXER_H
#define LEXER_H

#include <string>

#include "Token.h"

class Lexer {
  private:
    const std::string text;
    int position;

  public:
    Lexer(std::string contents);
    Token* nextToken();

  private:
    char getCurrent();
    void next();
};

#endif
