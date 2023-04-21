#include <string>

#include "./include/Parser.h"
#include "./include/Lexer.h"
#include "./include/ASTBinaryExpressionNode.h"

Parser::Parser(std::string text) {
  Lexer* lexer = new Lexer(text);
  this->tokens = {};

  Token* token;

  do {
    token = lexer->nextToken();

    if (token->getType() == TOKEN_WHITESPACE || token->getType() == TOKEN_BAD) {
    } else {
      this->tokens.push_back(token);
    }
  } while (token->getType() != TOKEN_EOF);
  delete(lexer);
}

Token* Parser::peek(int offset) {
  int index = this->position + offset;
  if (index >= this->tokens.size()) {
    return this->tokens[tokens.size() - 1];
  }
  return this->tokens[index];
}

Token* Parser::current() {
  return this->peek(0); 
}

ASTExpressionNode* Parser::parse() {
  ASTExpressionNode* left = this->parsePrimaryExpression();

  while (this->current()->getType() == TOKEN_PLUS ||
         this->current()->getType() == TOKEN_MINUS) {
    Token* operatorToken = nextToken();
    ASTExpressionNode* right = this->parsePrimaryExpression();
    left = new ASTBinaryExpressionNode(left, operatorToken, right);
  }

  return left;
}

Token* Parser::nextToken() {
  Token* current = this->current();
  this->position++;
  return current;
}

Token* Parser::match(SyntaxType type) {
  if (this->current()->getType() == type) {
    return this->nextToken();
  }
  return new Token(type, this->current()->getPosition(), nullptr, nullptr);
}

ASTExpressionNode* Parser::parsePrimaryExpression() {
  Token* numberToken = this->match(TOKEN_NUMBER);
  return new ASTNumberExpressionNode(numberToken);
}
