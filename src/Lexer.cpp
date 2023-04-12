#include <string>
#include <cctype>
#include <iostream>

#include "./include/Token.h"
#include "./include/Lexer.h"


Lexer::Lexer(std::string contents)
  : text(contents)
{}

Token* Lexer::nextToken() {
  // Number check
  if (this->getCurrent() >= '0' && this->getCurrent() <= '9') {
    int start = position;
    while (this->getCurrent() >= '0' && this->getCurrent() <= '9') { next(); }
    int length = position - start;
    std::string number = text.substr(start, length);
    return new Token(TOKEN_NUMBER, start, number);
  }

  if (isalnum(this->getCurrent())) {
    int start = position;
    while (isalnum(this->getCurrent())) { next(); }
    int length = position - start;
    std::string number = text.substr(start, length);
    return new Token(TOKEN_TEXT, start, number);
  }

  if (std::isspace(this->getCurrent())) {
    Token* token = new Token(TOKEN_WHITESPACE, position, " ");
    next();
    return token;
  }

  if (operators.find(this->getCurrent()) != operators.end()) {
    Token* token = new Token(TOKEN_OPERATOR, position, text.substr(position, 1));
    next();
    return token;
  }

  std::cout << "Error: unrecognizable character " << text[position] <<  std::endl;
  exit(1);
}

char Lexer::getCurrent() {
  if (position >= text.length()) { return '\0'; }
  return text[position];
}

void Lexer::next() {
  position++;
}
