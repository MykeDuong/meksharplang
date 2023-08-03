#ifndef GROUPING_H
#define GROUPING_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"

namespace Expr {
  class Expr;
  class Grouping: public Expr {
    public:
      const Expr* expr;

      Grouping(const Expr* expr);
      void const accept(Visitor* visitor) const;
  };
};

#endif
