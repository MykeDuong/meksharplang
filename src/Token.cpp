#include "./include/Token.h"
#include "include/TokenType.h"
#include <string>

Token::Token(TokenType type, std::string lexeme, LiteralValue* literal, int line) : 
  type(type), lexeme(lexeme), literal(literal), line(line)
{}

std::ostream& operator<<(std::ostream& os, const Token& token) {
  os 
    << "{ Type: " 
    << token.type 
    << ", LEXEME: " << token.lexeme 
    << ", Literal Value: " << *(token.literal) 
    << ", Literal Type: " << token.literal->type
    << " }";
  return os;
}
