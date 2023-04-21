#ifndef AST_BINARY_EXPRESSION_NODE_H
#define AST_BINARY_EXPRESSION_NODE_H

#include "Token.h"
#include "ASTExpressionNode.h"

class ASTBinaryExpressionNode final: public ASTExpressionNode {
  private:
    ASTExpressionNode* left;
    ASTExpressionNode* right;
    Token* operatorToken;

  public:
    ASTBinaryExpressionNode(Token* operatorToken, ASTExpressionNode* left, ASTExpressionNode* right);
    TokenType getType();
    Token* getOperatorToken();
    ASTExpressionNode* getLeft();
    ASTExpressionNode* getRight();
};

#endif
