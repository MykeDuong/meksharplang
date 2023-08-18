#ifndef BINARY_H
#define BINARY_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Binary: public Expr {
    public:
      const Expr* left;
      const Token* op;
      const Expr* right;

      Binary(const Expr* left, const Token* op, const Expr* right);
      void const accept(Visitor* visitor) const;
  };
};

#endif
