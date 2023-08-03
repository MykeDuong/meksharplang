#include "./include/LiteralValue.h"
#include <cmath>
#include <string>
#include <sstream>
#include <iomanip>

LiteralValue::LiteralValue() : type(LITERAL_NULL) {}

LiteralValue::LiteralValue(double value) : numericValue(value), type(LITERAL_NUMBER) {}

LiteralValue::LiteralValue(std::string value) : stringValue(value), type(LITERAL_STRING) {}

LiteralValue::LiteralValue(bool value) : boolValue(value), type(LITERAL_BOOL) {}

LiteralValue::LiteralValue(const LiteralValue& value) : 
  numericValue(value.numericValue), 
  stringValue(value.stringValue), 
  boolValue(value.boolValue),
  type(value.type)
{}

LiteralValue::LiteralValue(const LiteralValue* value) :
  numericValue(value->numericValue),
  stringValue(value->stringValue),
  boolValue(value->boolValue),
  type(value->type)
{}

std::string LiteralValue::toString() const {
  switch (this->type) {
    case LiteralValue::LITERAL_NULL:
      return "nah";
      break;
    case LiteralValue::LITERAL_NUMBER: 
      {
        double intpart;
        std::stringstream stream;
        stream << std::fixed << std::setprecision(std::modf(this->numericValue, &intpart) == 0 ? 0 : 2) << this->numericValue;
        return stream.str();
      }
      break;
    case LiteralValue::LITERAL_STRING:
      return this->stringValue; 
      break;
    case LiteralValue::LITERAL_BOOL:
      return this->boolValue ? "true" : "false";
  }

}

std::ostream& operator<<(std::ostream& os, const LiteralValue& literalValue) {
  return os << literalValue.toString();
}

bool LiteralValue::operator==(const LiteralValue& v) {
  if (type != v.type) return false;

  switch (type) {
    case LITERAL_STRING:
      return stringValue == v.stringValue;
    case LITERAL_NUMBER:
      return numericValue == v.numericValue;
    case LITERAL_BOOL:
      return boolValue == v.boolValue;
    case LITERAL_NULL:
      return true;
  }
}

bool LiteralValue::operator!=(const LiteralValue& v) {
  if (type != v.type) return true;

  switch (type) {
    case LITERAL_STRING:
      return stringValue != v.stringValue;
    case LITERAL_NUMBER:
      return numericValue != v.numericValue;
    case LITERAL_BOOL:
      return boolValue != v.boolValue;
    case LITERAL_NULL:
      return false;
  }
}

std::ostream& operator<<(std::ostream& out, const LiteralValue::Type value) {

#define MAPENTRY(p) {p, #p}
  const struct MapEntry{
    LiteralValue::Type value;
    const char* str;
  } entries[] = {
    MAPENTRY(LiteralValue::LITERAL_BOOL),
    MAPENTRY(LiteralValue::LITERAL_NULL),
    MAPENTRY(LiteralValue::LITERAL_STRING),
    MAPENTRY(LiteralValue::LITERAL_NUMBER),

    {LiteralValue::LITERAL_STRING, 0}
  };
#undef MAPENTRY
  const char* s = 0;
  for (const MapEntry* i = entries; i->str; i++){
    if (i->value == value){
      s = i->str;
      break;
    }
  }

  return out << s;
}
