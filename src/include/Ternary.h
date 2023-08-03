#ifndef TERNARY_H
#define TERNARY_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"

namespace Expr {
  class Expr;
  class Ternary: public Expr {
    public:
      const Expr* firstExpr;
      const Token* firstOp;
      const Expr* secondExpr;
      const Token* secondOp;
      const Expr* thirdExpr;

      Ternary(const Expr* firstExpr, const Token* firstOp, const Expr* secondExpr, const Token* secondOp, const Expr* thirdExpr);
      void const accept(Visitor* visitor) const;
  };
};

#endif
