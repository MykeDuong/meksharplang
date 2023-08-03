#include "include/main.h"
#include "include/ErrorHandler.h"
#include "include/Interpreter.h"
#include "include/LiteralValue.h"
#include "include/Parser.h"
#include "include/Scanner.h"
#include "include/Binary.h"
#include "include/Token.h"
#include "include/Unary.h"
#include "include/Grouping.h"
#include "include/Literal.h"
#include "include/AstPrinter.h"

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>

Interpreter* interpreter = new Interpreter();

int main(int argc, char *argv[])  {
  if (argc > 2) {
    std::cout << "Usage: meks [script]" << std::endl;
    return 1;
  } else if (argc == 2) {
    std::string s = argv[1];
    runFile(s);
  } else {
    runPrompt();
  }

  return 0;
}

void runFile(std::string const& filename) {
  std::ifstream ifs(filename.c_str(), std::ios::in | std::ios::binary | std::ios::ate);

  std::ifstream::pos_type fileSize = ifs.tellg();
  
  if (fileSize == -1) {
    std::cerr << "ERROR: File not found" << std::endl;
    exit(1);
  }
  
  ifs.seekg(0, std::ios::beg);
  std::vector<char> bytes(fileSize);
  ifs.read(bytes.data(), fileSize);

  std::string source(bytes.data(), fileSize);
  run(source);
  if (ErrorHandler::hadError()) exit(65);
  if (ErrorHandler::hadRuntimeError()) exit(70);
}

void runPrompt() {
  for (;;) {
    std::cout << "> ";
    std::string line;
    std::getline(std::cin, line);
    if (line.empty()) break;
    run(line);
    ErrorHandler::resetErrorCounter();
    ErrorHandler::resetRuntimeErrorCounter();
  }
}

void run(std::string const& source) {
  Scanner* scanner = new Scanner(source);
  std::vector<Token*> tokens = scanner->scanTokens();

  delete scanner;
  /*
  for (Token* token: tokens) {
    std::cout << *token << std::endl;
  }
  */ 

  Parser* parser = new Parser(tokens);
  Expr::Expr* expr = parser->parse();

  if (ErrorHandler::hadError()) return;

  //std::cout << ((new AstPrinter())->print(expr)) << std::endl;

  interpreter->interpret(expr);
}

