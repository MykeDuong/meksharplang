#include "./include/ErrorHandler.h"
#include "include/Token.h"

#include <iostream>
#include <string>

bool ErrorHandler::errorHappened = false;
bool ErrorHandler::runtimeErrorHappened = false;

void ErrorHandler::error(int line, std::string const& message) {
  report(line, "", message);
}

void ErrorHandler::error(const Token* const token, std::string const& message) {
  if (token->type == END_OF_FILE) {
    ErrorHandler::report(token->line, " at end", message);
  } else {
    ErrorHandler::report(token->line, " at '" + token->lexeme + "'", message);
  }
}

void ErrorHandler::report(int line, std::string const& where, std::string const& message) {
  std::cout << "[Line " << line << "] Error" << where << ": " << message << std::endl;
  ErrorHandler::errorHappened = true;
}

void ErrorHandler::runtimeError(RuntimeError& error) {
  std::cout << error.what() << "\n[line " << (error.token == nullptr ? "?" : std::to_string(error.token->line)) << "]" << std::endl;
  runtimeErrorHappened = true;   
}

bool ErrorHandler::hadError() {
  return errorHappened;
}

bool ErrorHandler::hadRuntimeError() {
  return runtimeErrorHappened;
}

void ErrorHandler::resetErrorCounter() {
  ErrorHandler::errorHappened = false;
}

void ErrorHandler::resetRuntimeErrorCounter() {
  ErrorHandler::runtimeErrorHappened = false;
}
