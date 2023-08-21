#ifndef LITERAL_VALUE_H
#define LITERAL_VALUE_H

#include <memory>
#include <string>
#include <iostream>
#include <vector>

class Callable;
class MekClass;
class MekFunction;
class MekInstance;

class LiteralValue {
  public:
    enum Type {
      LITERAL_STRING = 0,
      LITERAL_NUMBER,
      LITERAL_NULL,
      LITERAL_BOOL,
      LITERAL_FUNCTION,
      LITERAL_CLASS,
      LITERAL_INSTANCE,
      LITERAL_ARRAY
    };

    LiteralValue();
    ~LiteralValue();
    LiteralValue(double value);
    LiteralValue(std::string value);
    LiteralValue(bool value);
    LiteralValue(MekFunction* value);
    LiteralValue(MekClass* value);
    LiteralValue(MekInstance* value);
    LiteralValue(std::vector<LiteralValue*> array);
    LiteralValue(const LiteralValue& value);
    LiteralValue(const LiteralValue* value);
    friend std::ostream& operator<<(std::ostream& os, const LiteralValue& literalValue);
    bool operator==(const LiteralValue& v);
    bool operator!=(const LiteralValue& v);
    std::string toString() const; 
    
    const Type type;
    double numericValue;
    std::string stringValue;
    bool boolValue;
    std::vector<LiteralValue*> arrayValue;
    MekClass* classValue;
    MekFunction* functionValue;
    MekInstance* instanceValue;
};

std::ostream& operator<<(std::ostream& out, const LiteralValue::Type value);

#endif 
