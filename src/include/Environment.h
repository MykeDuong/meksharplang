#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "LiteralValue.h"
#include "Token.h"
#include <string>
#include <unordered_map>

class Environment {
  private:
    Environment* const enclosing;
    std::unordered_map<std::string, LiteralValue*> values;

  public:
    Environment();
    Environment(Environment* enclosing);
    void define(const std::string& name, LiteralValue* value);
    void assign(const Token* const name, LiteralValue* value);
    LiteralValue* get(const Token* const name);
    LiteralValue* get(const std::string& name);
    bool contain(const std::string& name);
    ~Environment();
};

#endif 
