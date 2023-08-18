#ifndef VAR_H
#define VAR_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class Var: public Stmt {
    public:
      const Token* name;
      const Expr::Expr* initializer;

      Var(const Token* name, const Expr::Expr* initializer);
      void const accept(Visitor* visitor) const;
  };
};

#endif
