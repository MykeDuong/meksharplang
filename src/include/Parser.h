#ifndef PARSER_H
#define PARSER_H

#include "Expr.h"
#include "Function.h"
#include "FunctionExpr.h"
#include "Stmt.h"
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
    std::vector<Stmt::Stmt*> parse();

  private:
    Stmt::Stmt* declaration();
    Stmt::Stmt* varDeclaration();
    Stmt::Stmt* statement();
    Stmt::Stmt* ifStatement();
    Stmt::Stmt* breakStatement();
    std::vector<Stmt::Stmt*> block();
    Stmt::Stmt* printStatement();
    Stmt::Stmt* whileStatement();
    Stmt::Stmt* forStatement();
    Stmt::Stmt* returnStatement();
    Stmt::Stmt* expressionStatement();
    Stmt::Function* function(const std::string& kind);
    Expr::Expr* expression();
    Expr::Expr* comma();
    Expr::Expr* functionExpression(bool funMatched = false);
    Expr::Expr* assignment();
    Expr::Expr* ternary();
    Expr::Expr* orStmt();
    Expr::Expr* andStmt();
    Expr::Expr* equality();
    Expr::Expr* comparison();
    Expr::Expr* term();
    Expr::Expr* factor();
    Expr::Expr* unary();
    Expr::Expr* call();
    Expr::Expr* primary();
    Expr::Expr* finishCall(Expr::Expr* callee);
    Expr::FunctionExpr* finishFunction(const std::string& kind = "function");
    Token* advance();
    Token* peek();
    Token* previous();
    Token* consume(const TokenType& type, const std::string& message);
    bool isAtEnd();
    bool check(const TokenType& type);
    bool match(const std::vector<TokenType>& types);
    bool leftOpMissing();
    ParseError error(Token* token, const std::string& message);
    void synchronize();
};

#endif 
