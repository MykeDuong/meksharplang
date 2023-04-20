#include <string>

#include "./include/Parser.h"
#include "./include/Lexer.h"

Parser::Parser(std::string text) {
  Lexer* lexer = new Lexer(text);

  Token* token;

  do {
    token = lexer->nextToken();

    if (token->getType() == TOKEN_WHITESPACE || token->getType() == TOKEN_BAD) {
      delete(token); 
    } else {
      this->tokens.push_back(token);
    }
  } while (token->getType() != TOKEN_EOF);
}


Token* Parser::peek(int offset) {
  int index = position + offset;
  if (index >= this->tokens.size()) {
    return this->tokens[tokens.size() - 1];
  }
  return this->tokens[index];
}

Token* Parser::current() {
  return this->peek(0);
}

ASTExpressionNode* Parser::parse() {
}

Token* Parser::nextToken() {
  Token* current = this->current();
  this->position++;
  return current;
}
