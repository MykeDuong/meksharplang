#ifndef LITERAL_H
#define LITERAL_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"

namespace Expr {
  class Expr;
  class Literal: public Expr {
    public:
      const LiteralValue* value;

      Literal(const LiteralValue* value);
      void const accept(Visitor* visitor) const;
  };
};

#endif
