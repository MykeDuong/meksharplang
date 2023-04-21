#include <string>
#include <cctype>
#include <iostream>

#include "./include/Token.h"
#include "./include/Lexer.h"


Lexer::Lexer(std::string contents)
  : text(contents)
{}

Token* Lexer::nextToken() {
  if (this->position >= this->text.length()) {
    return new Token(TOKEN_EOF, this->position, "\0", nullptr);
  }

  // Number check
  if (this->getCurrent() >= '0' && this->getCurrent() <= '9') {
    int start = position;
    while (this->getCurrent() >= '0' && this->getCurrent() <= '9') { next(); }
    int length = position - start;
    std::string number = text.substr(start, length);
    int* value = new int;
    *value = std::stoi(number);
    return new Token(TOKEN_NUMBER, start, number, value);
  }

  if (isalnum(this->getCurrent())) {
    int start = position;
    while (isalnum(this->getCurrent())) { next(); }
    int length = position - start;
    std::string value = text.substr(start, length);
    return new Token(TOKEN_TEXT, start, value, nullptr);
  }

  if (std::isspace(this->getCurrent())) {
    int start = position;
    while (isspace(this->getCurrent())) { next(); }
    int length = position - start;
    std::string value = " ";
    return new Token(TOKEN_WHITESPACE, start, value, nullptr);
  }

  Token* token;
  switch (this->getCurrent()) {
    case '+':
      token = new Token(TOKEN_PLUS, position, "+", nullptr);
      break;
    case '-':
      token = new Token(TOKEN_MINUS, position, "-", nullptr);
      break;
    case '*':
      token = new Token(TOKEN_STAR, position, "*", nullptr);
      break;
    case '/':
      token = new Token(TOKEN_SLASH, position, "/", nullptr);
      break;
    case '(':
      token = new Token(TOKEN_LEFT_PARENTHESIS, position, "(", nullptr);
      break;
    case ')':
      token = new Token(TOKEN_RIGHT_PARENTHESIS, position, ")", nullptr);
      break;
    default:
      token = new Token(TOKEN_BAD, position, text.substr(position - 1, 1), nullptr);
      break;
  }

  position++;
  return token;
}

char Lexer::getCurrent() {
  if (position >= text.length()) { return '\0'; }
  return text[position];
}

void Lexer::next() {
  position++;
}
