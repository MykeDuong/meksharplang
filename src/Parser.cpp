#include "./include/Parser.h"
#include "include/Binary.h"
#include "include/ErrorHandler.h"
#include "include/Expr.h"
#include "include/Grouping.h"
#include "include/Literal.h"
#include "include/LiteralValue.h"
#include "include/Ternary.h"
#include "include/TokenType.h"
#include "include/Unary.h"

Parser::Parser(std::vector<Token*>& tokens): tokens(tokens) {}

Expr::Expr* Parser::parse() {
  try {
    return expression();
  } catch (ParseError* error) {
    return nullptr;
  }
}

Expr::Expr* Parser::expression() {
  return comma();
}

Expr::Expr* Parser::comma() {
  Expr::Expr* expr = ternary();

  while (match(std::vector<TokenType> { COMMA })) {
    Token* op = previous();
    Expr::Expr* right = ternary();
    expr = new Expr::Binary(expr, op, right);
  }

  return expr;
}

Expr::Expr* Parser::ternary() {
  Expr::Expr* equal = equality();

  if (match(std::vector<TokenType> { QUESTION })) {
    Token* firstOp = previous();
    Expr::Expr* expr = expression();
    if (!match(std::vector<TokenType> { COLON })) {
      throw error(previous(), "Colon ':' expected for a ternary conditional operator");
    }
    Token* secondOp = previous();
    Expr::Expr* ter = ternary();
    return new Expr::Ternary(equal, firstOp, expr, secondOp, ter);
  }

  return equal;
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
  return primary();
}

Expr::Expr* Parser::primary() {
  if (match(std::vector<TokenType> {FALSE})) return new Expr::Literal(new LiteralValue(false));
  if (match(std::vector<TokenType> {TRUE})) return new Expr::Literal(new LiteralValue(true));
  if (match(std::vector<TokenType> {NAH})) return new Expr::Literal(new LiteralValue());

  if (match(std::vector<TokenType> { NUMBER, STRING })) return new Expr::Literal(previous()->literal);

  if (match(std::vector<TokenType> { LEFT_PAREN })) {
    Expr::Expr* expr = expression();
    consume(RIGHT_PAREN, "Expect ')' after expression.");
    return new Expr::Grouping(expr);
  }

  throw error(peek(), "Expect expression.");
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

Parser::ParseError* Parser::error(Token* token, const std::string& message) {
  ErrorHandler::error(token, message);
  return new ParseError();
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
