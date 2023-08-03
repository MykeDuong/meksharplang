#ifndef RUNTIME_ERROR_H
#define RUNTIME_ERROR_H

#include <exception>
#include <string>
#include "./Token.h"

class RuntimeError: public std::runtime_error {
  public:
    const Token* token;
    RuntimeError(const Token* token, const std::string& message);
};

#endif 
