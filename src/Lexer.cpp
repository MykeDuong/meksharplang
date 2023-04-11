#include <string>

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
}

char Lexer::getCurrent() {
  if (position >= text.length()) { return '\0'; }
  return text[position];
}

void Lexer::next() {
  position++;
}
