#include "Token.h"
#include "ASTExpressionNode.h"

class ASTBinaryExpressionNode final: public ASTExpressionNode {
  private:
    ASTExpressionNode* left;
    ASTExpressionNode* right;
    Token* operatorToken;

  public:
    ASTBinaryExpressionNode(Token* operatorToken, ASTExpressionNode* left, ASTExpressionNode* right);
    TokenType getType() override;
    Token* getOperatorToken();
    ASTExpressionNode* getLeft();
    ASTExpressionNode* getRight();
};
