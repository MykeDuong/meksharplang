#include "include/MekClass.h"
#include "include/LiteralValue.h"
#include "include/MekInstance.h"

MekClass::MekClass(std::string name, std::unordered_map<std::string, MekFunction*> methods) : 
  name(name), methods(methods) {}

LiteralValue* MekClass::call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) {
  MekInstance* instance = new MekInstance(this);
  return new LiteralValue(instance);
}

MekFunction* MekClass::findMethod(std::string name) {
  if (methods.find(name) != methods.end()) {
    return methods[name];
  }
  return nullptr;
}

int MekClass::arity() {
  return 0;
}

std::string MekClass::toString() {
  return "<class " + name + ">";
}
