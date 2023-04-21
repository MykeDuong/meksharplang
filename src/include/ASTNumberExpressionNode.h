#ifndef AST_NUMBER_EXPRESSION_NODE_H
#define AST_NUMBER_EXPRESSION_NODE_H

#include "Token.h"
#include "ASTExpressionNode.h"

class ASTNumberExpressionNode final: public ASTExpressionNode {
  private:
    Token* token;

  public:
    ASTNumberExpressionNode(Token* token);

  public:
    Token* getToken();
    TokenType getType();
};

#endif