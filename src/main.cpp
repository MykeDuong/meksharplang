#include <iostream>
#include "./include/lexer.h"

int main(int argc, char* argv[]) {
  Lexer* lexer = new Lexer("2 + 3 - 5");

  Token* token = lexer->nextToken();

  while (token->getType() != TOKEN_EOF) {
    std::cout << *token;
    token = lexer->nextToken();
  }


  return 0;
}
