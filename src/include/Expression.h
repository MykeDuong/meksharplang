#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class Expression: public Stmt {
    public:
      const Expr::Expr* expression;

      Expression(const Expr::Expr* expression);
      void const accept(Visitor* visitor) const;
  };
};

#endif
