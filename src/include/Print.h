#ifndef PRINT_H
#define PRINT_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class Print: public Stmt {
    public:
      const Expr::Expr* expression;

      Print(const Expr::Expr* expression);
      void const accept(Visitor* visitor) const;
  };
};

#endif
