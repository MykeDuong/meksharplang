#include "./include/TokenType.h"

std::ostream& operator<<(std::ostream& out, const TokenType value) {
#define MAPENTRY(p) {p, #p}
  const struct MapEntry{
    TokenType value;
    const char* str;
  } entries[] = {
    MAPENTRY(LEFT_PAREN),
    MAPENTRY(RIGHT_PAREN),
    MAPENTRY(LEFT_BRACE),
    MAPENTRY(RIGHT_BRACE),
    MAPENTRY(COMMA),
    MAPENTRY(DOT),
    MAPENTRY(MINUS),
    MAPENTRY(PLUS),
    MAPENTRY(SEMICOLON),
    MAPENTRY(SLASH),
    MAPENTRY(STAR),
    MAPENTRY(QUESTION),
    MAPENTRY(COLON),

    MAPENTRY(BANG),
    MAPENTRY(BANG_EQUAL),
    MAPENTRY(EQUAL),
    MAPENTRY(EQUAL_EQUAL),
    MAPENTRY(GREATER),
    MAPENTRY(GREATER_EQUAL),
    MAPENTRY(LESS),
    MAPENTRY(LESS_EQUAL),

    MAPENTRY(IDENTIFIER),
    MAPENTRY(STRING),
    MAPENTRY(NUMBER),
    
    MAPENTRY(AND),
    MAPENTRY(CLASS),
    MAPENTRY(ELSE),
    MAPENTRY(FALSE),
    MAPENTRY(FUN),
    MAPENTRY(FOR),
    MAPENTRY(IF),
    MAPENTRY(NAH),
    MAPENTRY(OR),
    MAPENTRY(PRINT),
    MAPENTRY(RETURN),
    MAPENTRY(SUPER),
    MAPENTRY(THIS),
    MAPENTRY(TRUE),
    MAPENTRY(VAR),
    MAPENTRY(WHILE),
    MAPENTRY(END_OF_FILE),


    {LEFT_PAREN, 0}
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
