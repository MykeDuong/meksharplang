#ifndef AST_BINARY_EXPRESSION_NODE_H
#define AST_BINARY_EXPRESSION_NODE_H

#include "Token.h"
#include "ASTExpressionNode.h"

class ASTBinaryExpressionNode final: public ASTExpressionNode {
  private:
    ASTExpressionNode* left;
    Token* operatorToken;
    ASTExpressionNode* right;

  public:
    ASTBinaryExpressionNode(ASTExpressionNode* left, Token* operatorToken, ASTExpressionNode* right);
    SyntaxType getType();
    std::vector<ASTNode*> getChildren();
    Token* getOperatorToken();
    ASTExpressionNode* getLeft();
    ASTExpressionNode* getRight();
};

#endif
