#include <string>
#include <vector>

#include "Token.h"
#include "ASTExpressionNode.h"

#ifndef PARSER_H
#define PARSER_H

class Parser {
  private:
    std::vector<Token*> tokens;
    int position;

  public:
    Parser(std::string text);
    ASTExpressionNode* parse();

  private:
    Token* peek(int offset);
    Token* current();
    Token* nextToken();
};


#endif 
