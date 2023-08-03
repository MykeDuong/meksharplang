#ifndef UNARY_H
#define UNARY_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"

namespace Expr {
  class Expr;
  class Unary: public Expr {
    public:
      const Token* op;
      const Expr* right;

      Unary(const Token* op, const Expr* right);
      void const accept(Visitor* visitor) const;
  };
};

#endif
