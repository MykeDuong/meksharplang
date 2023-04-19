#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "./include/lexer.h"

int main(int argc, char* argv[]) {
  if ( argc < 2) {
    std::cerr << "Please declare a source file\n";
    return 1;
  }
  std::string filename = argv[1];

  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();

  Lexer* lexer = new Lexer(buffer.str());

  Token* token = lexer->nextToken();

  do {
    std::cout << *token;
    token = lexer->nextToken();
  } while (token->getType() != TOKEN_EOF);

  return 0;
}
