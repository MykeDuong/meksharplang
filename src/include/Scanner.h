#ifndef SCANNER_H
#define SCANNER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "./Token.h"
#include "TokenType.h"

class Scanner {
  private:
    static std::unordered_map<std::string, TokenType> keywords;
    const std::string source;
    std::vector<Token*> tokens;
    int start = 0;
    int current = 0;
    int line = 1;

  public:
    Scanner(std::string source);
    std::vector<Token*> scanTokens();
  
  private:
    void string();
    void number();
    void identifier();
    void blockComment();
    bool isAtEnd();
    void scanToken();
    char advance();
    void addToken(TokenType type);
    void addToken(TokenType type, LiteralValue* literal);
    bool match(char expected);
    char peek();
    char peekNext();
};

#endif
