#include "./include/ASTBinaryExpressionNode.h"

ASTBinaryExpressionNode::ASTBinaryExpressionNode (
    Token* operatorToken,
    ASTExpressionNode* left, 
    ASTExpressionNode* right
) : operatorToken(operatorToken), left(left), right(right) { }

TokenType ASTBinaryExpressionNode::getType() { return TOKEN_BINARY_OPERATOR; }
    
Token* ASTBinaryExpressionNode::getOperatorToken() { return this->operatorToken; }

ASTExpressionNode* ASTBinaryExpressionNode::getLeft() { return this->left; }

ASTExpressionNode* ASTBinaryExpressionNode::getRight() { return this->right; }
