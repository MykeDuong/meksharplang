#include "./include/MekFunction.h"
#include "include/Environment.h"
#include "include/Function.h"
#include "include/LiteralValue.h"
#include <memory>


MekFunction::MekFunction(const Expr::FunctionExpr* declaration, std::shared_ptr<Environment> closure, const std::string name) : 
  declaration(declaration), closure(closure), name(name) {}

LiteralValue* MekFunction::call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) {
  std::shared_ptr<Environment> environment(closure);
  
  for (int i = 0; i < declaration->params.size(); i++) {
    environment->define(declaration->params[i]->lexeme, new LiteralValue(arguments[i]));
  }
  try {
    interpreter->executeBlock(declaration->body, environment.get());
  } catch (Interpreter::ReturnException& e) {
    return new LiteralValue(e.value);
  }

  return new LiteralValue();
}

int MekFunction::arity() {
  return declaration->params.size();
}

std::string MekFunction::toString() {
  if (name.size() == 0) return "<anonymous function>";
  return "<fn " + name + ">";
}
