#ifndef MEKCLASS_H
#define MEKCLASS_H

#include "Callable.h"
#include "LiteralValue.h"
#include <unordered_map>

class MekClass final: public Callable { 
  public:
    const std::string name;
    MekClass* const superclass;
    std::unordered_map<std::string, MekFunction*> methods;

    MekClass(std::string name, std::unordered_map<std::string, MekFunction*> methods, MekClass* const superclass);
    LiteralValue * call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) override;
    MekFunction* findMethod(std::string name);
    int arity() override;
    std::string toString() override;
};

#endif 
