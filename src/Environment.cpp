#include "./include/Environment.h"  
#include "include/LiteralValue.h"
#include "include/RuntimeError.h"

Environment::Environment() : enclosing(nullptr) {}

Environment::Environment(Environment* enclosing) : enclosing(enclosing) {}

Environment::~Environment() {
  for (auto it: this->values) {
    delete it.second; 
  }
  
  values.clear();
}

void Environment::define(const std::string& name, LiteralValue* value) {
  if (values.find(name) != values.end()) {
    LiteralValue* oldVal = values[name];
    delete oldVal;
  }
  if (value == nullptr) values[name] = nullptr;
  else {
    values[name] = new LiteralValue(value);
  }
}

void Environment::assign(const Token* const name, LiteralValue* value) {
  if (values.find(name->lexeme) != values.end()) {
    LiteralValue* oldVal = values[name->lexeme];
    delete oldVal;
    values[name->lexeme] = new LiteralValue(value);
  } else if (enclosing != nullptr) {
    enclosing->assign(name, value);
  } else {
     throw RuntimeError(name, "Undefined variable '" + name->lexeme);
  }
}

void Environment::assignAt(int distance, const Token* const name, LiteralValue* value) {
  ancestor(distance)->values[name->lexeme] = value;
}

LiteralValue* Environment::get(const Token* const name) {
  if (values.find(name->lexeme) != values.end()) {
    if (values[name->lexeme] == nullptr) {
      throw RuntimeError(name, "Unassigned variable '" + name->lexeme + "'.");
    }
    return values[name->lexeme];
  }
  
  if (enclosing != nullptr) return enclosing->get(name);
  
  throw RuntimeError(name, "Undefined variable '" + name->lexeme + "'.");
}

LiteralValue* Environment::get(const std::string& name) {
  if (values.find(name) != values.end()) {
    if (values[name] == nullptr) {
      throw RuntimeError(nullptr, "Unassigned variable '" + name + "'.");
    }
    return values[name];
  }
  
  if (enclosing != nullptr) return enclosing->get(name);
  
  throw RuntimeError(nullptr, "Undefined variable '" + name + "'.");
}

LiteralValue* Environment::getAt(int distance, const std::string name) {
  auto ancestorEnv = ancestor(distance);
  
  if (ancestorEnv->values[name] == nullptr)
      throw RuntimeError(nullptr, "Unassigned variable '" + name + "'.");
  
  return ancestorEnv->values[name];
}

Environment* Environment::ancestor(int distance) {
  Environment* environment = this;
  for (int i = 0; i < distance; i++) {
    environment = environment->enclosing;
  }

  return environment;
}

bool Environment::contain(const std::string& name) {
  return (values.find(name) != values.end());
}
