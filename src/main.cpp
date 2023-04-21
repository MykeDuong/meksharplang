#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "./include/Parser.h"
#include "include/SyntaxType.h"

void printTree(ASTNode* node, std::string indent = "") {
  std::cout << indent;
  std::cout << node->getType();

  if (node->getChildren().size() == 0) {
    Token* token = (Token*) node;
    if (token->getValue() != nullptr) {
      std::cout << " ";
      if (token->getType() == TOKEN_NUMBER) {
        std::cout << *((int*) token->getValue());
      } else {
        std::cout << token->getValue();
      }
    }
  }
  
  std::cout << "\n";

  indent += "    ";

  for (int i = 0; i < node->getChildren().size(); i++) {
    printTree(node->getChildren()[i], indent);
  }
}

int main(int argc, char* argv[]) {
  if ( argc < 2) {
    std::cerr << "Please declare a source file\n";
    return 1;
  }
  std::string filename = argv[1];

  std::ifstream t(filename);
  std::stringstream buffer;
  buffer << t.rdbuf();

  Parser* parser = new Parser(buffer.str());

  ASTNode* root = parser->parse();

  printTree(root);

  return 0;
}
