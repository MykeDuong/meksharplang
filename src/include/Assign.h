#ifndef ASSIGN_H
#define ASSIGN_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Assign: public Expr {
    public:
      const Token* name;
      const Expr* value;

      Assign(const Token* name, const Expr* value);
      void const accept(Visitor* visitor) const;
  };
};

#endif
