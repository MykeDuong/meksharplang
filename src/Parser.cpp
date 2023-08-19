#include "./include/Parser.h"
#include "include/Array.h"
#include "include/ArrayElement.h"
#include "include/Assign.h"
#include "include/Binary.h"
#include "include/BreakStmt.h"
#include "include/Call.h"
#include "include/ClassStmt.h"
#include "include/DefinitionChecker.h"
#include "include/ErrorHandler.h"
#include "include/Expr.h"
#include "include/Expression.h"
#include "include/Function.h"
#include "include/FunctionExpr.h"
#include "include/Grouping.h"
#include "include/IfStmt.h"
#include "include/Literal.h"
#include "include/LiteralValue.h"
#include "include/Logical.h"
#include "include/Print.h"
#include "include/ReturnStmt.h"
#include "include/Stmt.h"
#include "include/Ternary.h"
#include "include/TokenType.h"
#include "include/Unary.h"
#include "include/Var.h"
#include "include/Block.h"
#include "include/Variable.h"
#include "include/WhileStmt.h"

Parser::Parser(std::vector<Token*>& tokens): tokens(tokens) {}

std::vector<Stmt::Stmt*> Parser::parse() {
  std::vector<Stmt::Stmt*> statements;
  while (!isAtEnd()) {
    statements.push_back(declaration());
  }

  return statements;
}

Stmt::Stmt* Parser::declaration() {
  try {
    if (match(std::vector<TokenType> { IF })) return classDeclaration();
    if (match(std::vector<TokenType> { FUN })) {
      if (peek()->type == IDENTIFIER)
        return function("function");
      Expr::Expr* expr = functionExpression(true);
      consume(SEMICOLON, "Expected ';' after expression.");
      return new Stmt::Expression(expr);
    }
    if (match(std::vector<TokenType> { VAR })) return varDeclaration();
    return statement();
  } catch (ParseError& error) {
    synchronize();
    return nullptr;
  }
}

Stmt::Stmt* Parser::varDeclaration() {
  Token* name = consume(IDENTIFIER, "Expect variable name.");

  Expr::Expr* initializer = nullptr;
  if (match(std::vector<TokenType> { EQUAL })) {
    initializer = expression();
  }

  consume(SEMICOLON, "Expect ';' after variable declaration.");
  return new Stmt::Var(name, initializer);
}

Stmt::Stmt* Parser::classDeclaration() {
  Token* name = consume(IDENTIFIER, "Expect class name.");
  consume(LEFT_BRACE, "Expect '{' before class body.");

  std::vector<Stmt::Function*> methods;
  while (!check(RIGHT_BRACE) && !isAtEnd()) {
    methods.push_back(function("method"));
  }

  consume(RIGHT_BRACE, "Expect '}' after class body.");

  return new Stmt::ClassStmt(name, methods);
}

Stmt::Stmt* Parser::statement() {
  if (match(std::vector<TokenType>{ IF })) return ifStatement();
  if (match(std::vector<TokenType>{ PRINT })) return printStatement();
  if (match(std::vector<TokenType>{ RETURN })) return returnStatement();
  if (match(std::vector<TokenType>{ WHILE })) return whileStatement();
  if (match(std::vector<TokenType>{ FOR })) return forStatement();
  if (match(std::vector<TokenType>{ LEFT_BRACE })) return new Stmt::Block(block());
  if (match(std::vector<TokenType>{ BREAK })) return breakStatement();

  return expressionStatement();
}

Stmt::Stmt* Parser::ifStatement() {
  consume(LEFT_PAREN, "Expect '(' after 'if'.");
  Expr::Expr* condition = expression();
  consume(RIGHT_PAREN, "Expect ')' after if condition.");

  Stmt::Stmt* thenBranch = statement();
  Stmt::Stmt* elseBranch = nullptr;
  if (match(std::vector<TokenType> {ELSE})) {
    elseBranch = statement(); 
  }

  return new Stmt::IfStmt(condition, thenBranch, elseBranch);
}

Stmt::Stmt* Parser::breakStatement() {
  Stmt::BreakStmt* stmt = new Stmt::BreakStmt(previous());
  consume(SEMICOLON, "Expect ';' after 'break'.");
  return stmt;
}

std::vector<Stmt::Stmt*> Parser::block() {
  std::vector<Stmt::Stmt*> statements;

  while (!check(RIGHT_BRACE) && !isAtEnd()) {
    statements.push_back(declaration());
  }

  consume(RIGHT_BRACE, "Expected '}' after block.");
  return statements;
}

Stmt::Stmt* Parser::printStatement() {
  Expr::Expr* value = expression();
  consume(SEMICOLON, "Expect ';' after value.");
  return new Stmt::Print(value);
}

Stmt::Stmt* Parser::whileStatement() {
  consume(LEFT_PAREN, "Expect '(' after 'while'."); 
  Expr::Expr* condition = expression();
  consume(RIGHT_PAREN, "Expect ')' after 'while'.");
  Stmt::Stmt* body = statement();

  return new Stmt::WhileStmt(condition, body);
}

Stmt::Stmt* Parser::forStatement() {
  consume(LEFT_PAREN, "Expect '(' after 'for'.");
  Stmt::Stmt* initializer;
  if (match(std::vector<TokenType>{ SEMICOLON })) {
    initializer = nullptr;
  } else if (match(std::vector<TokenType>{ VAR })){
    initializer = varDeclaration();
  } else {
    initializer = expressionStatement();
  }

  Expr::Expr* condition = nullptr;
  if (!check(SEMICOLON)) {
    condition = expression(); 
  }
  consume(SEMICOLON, "Expect ';' after loop condition.");

  Expr::Expr* increment = nullptr;
  if (!check(RIGHT_PAREN)) {
    increment = expression();
  }
  consume(RIGHT_PAREN, "Expect ')' after for clauses.");

  Stmt::Stmt* body = statement();
  
  if (increment != nullptr) {
    body = new Stmt::Block(std::vector<Stmt::Stmt*> { body, new Stmt::Expression(increment) });
  }

  if (condition == nullptr) condition = new Expr::Literal(new LiteralValue(true));
  body = new Stmt::WhileStmt(condition, body);

  if (initializer != nullptr) {
    body = new Stmt::Block(std::vector<Stmt::Stmt*> { initializer, body });
  }

  return body;
}

Stmt::Stmt* Parser::returnStatement() {
  Token* keyword = previous();
  Expr::Expr* value = nullptr;
  if (!check(SEMICOLON)) {
    value = expression();
  } 
  
  consume(SEMICOLON, "Expect ';' after return value.");
  return new Stmt::ReturnStmt(keyword, value);
}

Stmt::Function* Parser::function(const std::string& kind) {
  Token* name = consume(IDENTIFIER, "Expect " + kind + " name.");
  return new Stmt::Function(name, finishFunction());
}

Stmt::Stmt* Parser::expressionStatement() {
  Expr::Expr* expr = expression();
  consume(SEMICOLON, "Expected ';' after expression.");
  return new Stmt::Expression(expr);
}

Expr::Expr* Parser::expression() {
  return comma();
}

Expr::Expr* Parser::comma() {
  Expr::Expr* expr = assignment();

  while (match(std::vector<TokenType> { COMMA })) {
    Token* op = previous();
    Expr::Expr* right = ternary();
    expr = new Expr::Binary(expr, op, right);
  }

  return expr;
}


Expr::Expr* Parser::assignment() {
  Expr::Expr* expr = ternary();

  if (match(std::vector<TokenType> { EQUAL })) {
    Token* equals = previous();
    Expr::Expr* value = assignment();

    if (DefinitionChecker::getChecker()->check(expr) == DefinitionChecker::EXPR_VARIABLE) {
      const Token* name = dynamic_cast<Expr::Variable*>(expr)->name;
      return new Expr::Assign(name, value);
    }

    error(equals, "Invalid assignment target.");
  }
  return expr;
}

Expr::Expr* Parser::ternary() {
  Expr::Expr* orStatement = orStmt();

  if (match(std::vector<TokenType> { QUESTION })) {
    Token* firstOp = previous();
    Expr::Expr* expr = expression();
    if (!match(std::vector<TokenType> { COLON })) {
      throw error(previous(), "Colon ':' expected for a ternary conditional operator");
    }
    Token* secondOp = previous();
    Expr::Expr* ter = ternary();
    return new Expr::Ternary(orStatement, firstOp, expr, secondOp, ter);
  }

  return orStatement;
}

Expr::Expr* Parser::orStmt() {
  Expr::Expr* expr = andStmt();

  while (match(std::vector<TokenType>{ OR })) {
    Token* op = previous();
    Expr::Expr* right = andStmt();
    expr = new Expr::Logical(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::andStmt() {
  Expr::Expr* expr = equality();

  while (match(std::vector<TokenType> { AND })) {
    Token* op = previous();
    Expr::Expr* right = equality();
    expr = new Expr::Logical(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::equality() {
  if (leftOpMissing()) {
    Token* op = advance();
    error(op, "Expected an expression before the operation " + op->lexeme);
    Expr::Expr* expr = comparison();
    return nullptr;
  }
  Expr::Expr* expr = comparison();

  while (match(std::vector<TokenType>{BANG_EQUAL, EQUAL_EQUAL})) {
    Token* op = previous();
    Expr::Expr* right = comparison();
    expr = new Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::comparison() {
  if (leftOpMissing()) {
    Token* op = advance();
    error(op, "Expected an expression before the operation " + op->lexeme);
    Expr::Expr* expr = term();
    return nullptr;
  }
  Expr::Expr* expr = term();
  while(match(std::vector<TokenType> { GREATER, GREATER_EQUAL, LESS, LESS_EQUAL })) {
    Token* op = previous();
    Expr::Expr* right = term();
    expr = new Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::term() {
  if (leftOpMissing()) {
    Token* op = advance();
    error(op, "Expected an expression before the operation " + op->lexeme);
    Expr::Expr* expr = factor();
    return nullptr;
  }
  Expr::Expr* expr = factor();

  while (match(std::vector<TokenType> { MINUS, PLUS })) {
    Token* op = previous();
    Expr::Expr* right = factor();
    expr = new Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::factor() {
  if (leftOpMissing()) {
    Token* op = advance();
    error(op, "Expected an expression before the operation " + op->lexeme);
    Expr::Expr* expr = unary();
    return nullptr;
  }
  Expr::Expr* expr = unary();

  while (match(std::vector<TokenType> { STAR, SLASH })) {
    Token* op = previous();
    Expr::Expr* right = unary();
    expr = new Expr::Binary(expr, op, right);
  }
  
  return expr;
}

Expr::Expr* Parser::unary() {
  if (match(std::vector<TokenType> { BANG, MINUS })) {
    Token* op = previous();
    Expr::Expr* right = unary();
    return new Expr::Unary(op, right);
  }
  return call();
}

Expr::Expr* Parser::call() {
  Expr::Expr* expr = functionExpression();

  while (true) {
    if (match(std::vector<TokenType> { LEFT_PAREN })) {
      expr = finishCall(expr);
    } else {
      break;
    }
  }
  return expr;
}

Expr::Expr* Parser::functionExpression(bool funMatched) {
  if (!funMatched) {
    if (match(std::vector<TokenType>{ FUN })) {
      return finishFunction();
    }
    return array();
  }
  return finishFunction();
}


Expr::Expr* Parser::array() {
  //std::cout << peek()->type << std::endl;
  if (!match(std::vector<TokenType> { LEFT_SQUARE })) return arrayElement();

  std::vector<Expr::Expr*> elements;
  if (!check(RIGHT_SQUARE)) {
    do {
      elements.push_back(assignment());
    } while (match(std::vector<TokenType>{ COMMA }));
  }
  Token* paren = consume(RIGHT_SQUARE, "Expected ']' after array elements.");
  return new Expr::Array(elements, paren);
}

Expr::Expr* Parser::arrayElement() {
  Expr::Expr* expr = primary();

  if (match(std::vector<TokenType>{ LEFT_SQUARE })) {
    Expr::Expr* index = assignment();
    Token* square = consume(RIGHT_SQUARE, "Expect ']' after array index.");
    return new Expr::ArrayElement(expr, index, square);
  }
  
  return expr;
}

Expr::Expr* Parser::primary() {
  if (match(std::vector<TokenType> {FALSE})) return new Expr::Literal(new LiteralValue(false));
  if (match(std::vector<TokenType> {TRUE})) return new Expr::Literal(new LiteralValue(true));
  if (match(std::vector<TokenType> {NAH})) return new Expr::Literal(new LiteralValue());

  if (match(std::vector<TokenType> { NUMBER, STRING })) return new Expr::Literal(previous()->literal);

  if (match(std::vector<TokenType> { IDENTIFIER } )) return new Expr::Variable(previous());

  if (match(std::vector<TokenType> { LEFT_PAREN })) {
    Expr::Expr* expr = expression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return new Expr::Grouping(expr);
  }
  throw error(peek(), "Expect expression.");
}

Expr::Expr* Parser::finishCall(Expr::Expr* callee) {
  std::vector<Expr::Expr*> arguments;

  if (!check(RIGHT_PAREN)) {
    do {
      if (arguments.size() >= 255) {
        error(peek(), "Cannot have more than 255 arguments.");
      }
      arguments.push_back(assignment());
    } while (match(std::vector<TokenType> { COMMA }));
  }
  
  Token* paren = consume(RIGHT_PAREN, "Expect ')' after arguments.");

  return new Expr::Call(callee, paren, arguments);
}

Expr::FunctionExpr* Parser::finishFunction(const std::string& kind) {
  consume(LEFT_PAREN, "Expect '(' after 'fun' keyword or " + kind + " name.");
  std::vector<Token*> parameters;

  if (!check(RIGHT_PAREN)) {
    do {
      if (parameters.size() >= 255) {
        error(peek(), "Cannot have more than 255 parameters.");
      }
      parameters.push_back(consume(IDENTIFIER, "Expect paramter name."));
    } while (match(std::vector<TokenType> { COMMA }));
  }
  consume(RIGHT_PAREN, "Expect ')' after parameters.");
  consume(LEFT_BRACE, "Expect '{' before " + kind + " body.");
  std::vector<Stmt::Stmt*> body = block();
  return new Expr::FunctionExpr(parameters, body);
}

Token* Parser::advance() {
  if (!isAtEnd()) current++;
  return previous();
}

Token* Parser::peek() { return tokens[current]; }

Token* Parser::previous() { return tokens[current - 1]; }

Token* Parser::consume(const TokenType& type, const std::string& message) {
  if (check(type)) return advance();

  throw error(peek(), message);
}

bool Parser::match(const std::vector<TokenType>& types) {
  for (TokenType type: types) {
    if (check(type)) {
      advance();
      return true;
    }
  }
  return false;
}

bool Parser::check(const TokenType& type) {
  if (isAtEnd()) return false;
  return peek()->type == type;
}

bool Parser::isAtEnd() { return peek()->type == END_OF_FILE; }

bool Parser::leftOpMissing() {
  std::vector<TokenType> ops = { 
    PLUS, SLASH, STAR, BANG_EQUAL, EQUAL_EQUAL, GREATER, 
    GREATER_EQUAL, LESS, LESS_EQUAL
  };

  if (std::count(ops.begin(), ops.end(), peek()->type)) {
    return true;
  }

  return false;
}

Parser::ParseError Parser::error(Token* token, const std::string& message) {
  ErrorHandler::error(token, message);
  return ParseError();
}

void Parser::synchronize() {
  advance();

  while (!isAtEnd()) {
    if (previous()->type == SEMICOLON) return;

    switch (peek()->type) {
      case CLASS:
      case FUN:
      case VAR:
      case FOR:
      case IF:
      case WHILE:
      case PRINT:
      case RETURN:
        return;
      default:
        break;
    }

    advance();
  }
}
