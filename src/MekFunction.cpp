#include "./include/MekFunction.h"
#include "include/Environment.h"
#include "include/Function.h"
#include "include/LiteralValue.h"
#include <memory>


MekFunction::MekFunction(
  const Expr::FunctionExpr* declaration, 
  std::shared_ptr<Environment> closure, 
  const bool isInitializer, 
  const std::string name
) : declaration(declaration), closure(closure), name(name), isInitializer(isInitializer) {}

MekFunction* MekFunction::bind(MekInstance* instance) {
  Environment* environment = new Environment(closure.get());
  environment->define("this", new LiteralValue(instance));
  return new MekFunction(declaration, std::shared_ptr<Environment>(environment), isInitializer);
}

LiteralValue* MekFunction::call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) {
  std::shared_ptr<Environment> environment(new Environment(closure.get()));
  
  for (int i = 0; i < declaration->params.size(); i++) {
    environment->define(declaration->params[i]->lexeme, new LiteralValue(arguments[i]));
  }
  try {
    interpreter->executeBlock(declaration->body, environment.get());
  } catch (Interpreter::ReturnException& e) {
    if (isInitializer) {
      delete e.value;
      return new LiteralValue(closure.get()->getAt(0, "this"));
    }
    delete e.value;
    return new LiteralValue(e.value);
  }
  
  if (isInitializer) return closure->getAt(0, "this");

  return new LiteralValue();
}

int MekFunction::arity() {
  return declaration->params.size();
}

std::string MekFunction::toString() {
  if (name.size() == 0) return "<anonymous function>";
  return "<fn " + name + ">";
}
