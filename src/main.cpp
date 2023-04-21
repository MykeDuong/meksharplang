#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

#include "./include/Parser.h"

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


  return 0;
}
