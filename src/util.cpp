#include "./include/util.h"
#include <cctype>

bool util::isAlpha(char c) {
  return std::isalpha(c) || c == '_';
}

bool util::isDigit(char c) {
  return std::isdigit(c);
}

bool util::isAlphaNumeric(char c) {
  return isAlpha(c) || isDigit(c);
}
