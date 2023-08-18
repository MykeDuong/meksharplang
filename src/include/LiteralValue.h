#ifndef LITERAL_VALUE_H
#define LITERAL_VALUE_H

#include <memory>
#include <string>
#include <iostream>

class Callable;

class LiteralValue {
  public:
    enum Type {
      LITERAL_STRING = 0,
      LITERAL_NUMBER,
      LITERAL_NULL,
      LITERAL_BOOL,
      LITERAL_CALLABLE
    };

    LiteralValue();
    LiteralValue(double value);
    LiteralValue(std::string value);
    LiteralValue(bool value);
    LiteralValue(Callable* callable);
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
    std::shared_ptr<Callable> callableValue;
};

std::ostream& operator<<(std::ostream& out, const LiteralValue::Type value);

#endif 
