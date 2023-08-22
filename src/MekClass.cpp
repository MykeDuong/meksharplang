#include "include/MekClass.h"
#include "include/MekFunction.h"
#include "include/LiteralValue.h"
#include "include/MekInstance.h"

MekClass::MekClass(std::string name, std::unordered_map<std::string, MekFunction*> methods) : 
  name(name), methods(methods) {}

LiteralValue* MekClass::call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) {
  MekInstance* instance = new MekInstance(this);

  MekFunction* initializer = findMethod("init");
  if (initializer != nullptr) {
    initializer->bind(instance)->call(interpreter, arguments);
  }

  return new LiteralValue(instance);
}

MekFunction* MekClass::findMethod(std::string name) {
  if (methods.find(name) != methods.end()) {
    return methods[name];
  }
  return nullptr;
}

int MekClass::arity() {
  MekFunction* initializer = findMethod("init");
  if (initializer == nullptr) return 0;
  return initializer->arity();
}

std::string MekClass::toString() {
  return "<class " + name + ">";
}
