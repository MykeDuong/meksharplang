#include <string>
#include <iostream>

#include "./include/Token.h"

Token::Token(TokenType type, int position, std::string text, void* value)
  : type(type), position(position), text(text)
{}

TokenType Token::getType() { return type; }

int Token::getPosition() { return position; }

std::string Token::getText() { return text; }

std::ostream& operator<<(std::ostream& os, const Token& token) {
  return os << 
         " { Type: " << token.type << 
         ", position: " << token.position << 
         ", value: " << token.text << "}" << 
         std::endl;
}
