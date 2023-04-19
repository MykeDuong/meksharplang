#include "./include/ASTNumberExpressionNode.h"

ASTNumberExpressionNode::ASTNumberExpressionNode(Token* token)
  : token(token)
{}

TokenType ASTNumberExpressionNode::getType() { return TOKEN_NUMBER; }

Token* ASTNumberExpressionNode::getToken() { return this->token; }
