#ifndef ARRAYELEMENT_H
#define ARRAYELEMENT_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class ArrayElement: public Expr {
    public:
      const Expr* callee;
      const Expr* index;
      const Token* square;

      ArrayElement(const Expr* callee, const Expr* index, const Token* square);
      void const accept(Visitor* visitor) const;
  };
};

#endif
