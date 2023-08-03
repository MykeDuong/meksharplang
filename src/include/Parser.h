#ifndef PARSER_H
#define PARSER_H

#include "Expr.h"
#include "Token.h"
#include "TokenType.h"
#include <exception>
#include <vector>

class Parser {
  private:
    std::vector<Token*>& tokens;
    int current = 0;
    class ParseError: public std::exception {
    };

  public:
    Parser(std::vector<Token*>& tokens);
    Expr::Expr* parse();

  private:
    Expr::Expr* expression();
    Expr::Expr* comma();
    Expr::Expr* ternary();
    Expr::Expr* equality();
    Expr::Expr* comparison();
    Expr::Expr* term();
    Expr::Expr* factor();
    Expr::Expr* unary();
    Expr::Expr* primary();
    Token* advance();
    Token* peek();
    Token* previous();
    Token* consume(const TokenType& type, const std::string& message);
    bool isAtEnd();
    bool check(const TokenType& type);
    bool match(const std::vector<TokenType>& types);
    bool leftOpMissing();
    ParseError* error(Token* token, const std::string& message);
    void synchronize();
};

#endif 
