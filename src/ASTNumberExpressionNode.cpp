#include "./include/ASTNumberExpressionNode.h"

ASTNumberExpressionNode::ASTNumberExpressionNode(Token* token)
  : token(token)
{}

SyntaxType ASTNumberExpressionNode::getType() { return EXPRESSION_NUMBER; }

std::vector<ASTNode*> ASTNumberExpressionNode::getChildren() { return { this->getToken() }; }

Token* ASTNumberExpressionNode::getToken() { return this->token; }
