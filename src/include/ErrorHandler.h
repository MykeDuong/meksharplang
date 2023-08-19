#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H

#include "RuntimeError.h"
#include "Token.h"
#include <string>

class ErrorHandler{
  private:
    static bool errorHappened;
    static bool runtimeErrorHappened;
  public:
    static void error(int line, std::string const& message);
    static void error(const Token* const token, std::string const& message);
    static void runtimeError(RuntimeError& error);
    static void report(int line, std::string const& where, std::string const& message);
    static bool hadError();
    static bool hadRuntimeError();
    static void resetErrorCounter();
    static void resetRuntimeErrorCounter();
};

#endif 
