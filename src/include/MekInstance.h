#ifndef MEK_INSTANCE_H
#define MEK_INSTANCE_H

#include "LiteralValue.h"
#include "Token.h"
#include <unordered_map>

class MekClass;
class MekInstance {
  private:
    MekClass* klass;
    std::unordered_map<std::string, LiteralValue*> fields;

  public:
    MekInstance(MekClass* klass);
    LiteralValue* get(const Token* const name);
    void set(const Token* const name, LiteralValue* value);

    std::string toString();
};

#endif
