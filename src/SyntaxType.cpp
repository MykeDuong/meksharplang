#include "./include/SyntaxType.h"

std::ostream& operator<<(std::ostream& out, const SyntaxType value) {
#define MAPENTRY(p) {p, #p}
  const struct MapEntry{
    SyntaxType value;
    const char* str;
  } entries[] = {
    MAPENTRY(TOKEN_NUMBER),
    MAPENTRY(TOKEN_WHITESPACE),
    MAPENTRY(TOKEN_TEXT),
    MAPENTRY(TOKEN_PLUS),
    MAPENTRY(TOKEN_MINUS),
    MAPENTRY(TOKEN_STAR),
    MAPENTRY(TOKEN_SLASH),
    MAPENTRY(TOKEN_LEFT_PARENTHESIS),
    MAPENTRY(TOKEN_RIGHT_PARENTHESIS),
    MAPENTRY(TOKEN_BAD),
    MAPENTRY(TOKEN_EOF),
    MAPENTRY(EXPRESSION_BINARY_OPERATOR),
    MAPENTRY(EXPRESSION_NUMBER),
    {TOKEN_NUMBER, 0}
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
