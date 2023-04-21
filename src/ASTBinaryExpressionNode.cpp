#include "./include/ASTBinaryExpressionNode.h"
#include "include/SyntaxType.h"

ASTBinaryExpressionNode::ASTBinaryExpressionNode (
    ASTExpressionNode* left, 
    Token* operatorToken,
    ASTExpressionNode* right
) : operatorToken(operatorToken), left(left), right(right) { }

SyntaxType ASTBinaryExpressionNode::getType() { return EXPRESSION_BINARY_OPERATOR; }

std::vector<ASTNode*> ASTBinaryExpressionNode::getChildren() { return { this->left, this->operatorToken, this->right };}

Token* ASTBinaryExpressionNode::getOperatorToken() { return this->operatorToken; }

ASTExpressionNode* ASTBinaryExpressionNode::getLeft() { return this->left; }

ASTExpressionNode* ASTBinaryExpressionNode::getRight() { return this->right; }
