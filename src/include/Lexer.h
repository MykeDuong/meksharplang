#include <string>

#include "Token.h"

#ifndef LEXER_H
#define LEXER_H

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
