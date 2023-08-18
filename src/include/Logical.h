#ifndef LOGICAL_H
#define LOGICAL_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Logical: public Expr {
    public:
      const Expr* left;
      const Token* op;
      const Expr* right;

      Logical(const Expr* left, const Token* op, const Expr* right);
      void const accept(Visitor* visitor) const;
  };
};

#endif
