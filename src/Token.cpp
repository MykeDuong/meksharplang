#include <string>

#include "./include/Token.h"

Token::Token(TokenType type, int position, std::string text)
  : type(type), position(position), text(text)
{}

TokenType Token::getType() { return type; }

int Token::getPosition() { return position; }

std::string Token::getText() { return text; }
