#ifndef SET_H
#define SET_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Set: public Expr {
    public:
      const Expr* obj;
      const Token* name;
      const Expr* value;

      Set(const Expr* obj, const Token* name, const Expr* value);
      void const accept(Visitor* visitor) const;
  };
};

#endif
