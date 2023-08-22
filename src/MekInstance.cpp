#include "include/MekInstance.h"
#include "include/LiteralValue.h"
#include "include/MekClass.h"
#include "include/MekFunction.h"
#include "include/RuntimeError.h"
#include <string>

MekInstance::MekInstance(MekClass* klass) : klass(klass) {}

LiteralValue* MekInstance::get(const Token* const name) {
  if (fields.find(name->lexeme) != fields.end()) {
    return new LiteralValue(fields[name->lexeme]); 
  }

  MekFunction* method = klass->findMethod(name->lexeme);
  if (method != nullptr) return new LiteralValue(method->bind(this));

  throw RuntimeError(name, "Undefined property '" + name->lexeme + "'.");
}

void MekInstance::set(const Token* const name, LiteralValue* value) {
  if (fields.find(name->lexeme) != fields.end()) {
    LiteralValue* oldVal = fields[name->lexeme];
    delete oldVal;
  }
  fields[name->lexeme] = new LiteralValue(value);
}

std::string MekInstance::toString() {
  return "<" + klass->name + " instance>";
}
