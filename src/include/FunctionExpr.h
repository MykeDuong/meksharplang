#ifndef FUNCTIONEXPR_H
#define FUNCTIONEXPR_H

#include "./Expr.h"
#include "./Stmt.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class FunctionExpr: public Expr {
    public:
      const std::vector<Token*> params;
      const std::vector<Stmt::Stmt*> body;

      FunctionExpr(const std::vector<Token*> params, const std::vector<Stmt::Stmt*> body);
      void const accept(Visitor* visitor) const;
  };
};

#endif
