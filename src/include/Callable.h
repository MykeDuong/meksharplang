#ifndef CALLABLE_H
#define CALLABLE_H

#include "Interpreter.h"
#include "LiteralValue.h"
#include <string>
#include <vector>

class Callable {
  public:
    virtual LiteralValue* call(Interpreter* interpreter, std::vector<LiteralValue*>& arguments) = 0;
    virtual int arity() = 0;
    virtual std::string toString() = 0;
};

#endif 
