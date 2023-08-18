#ifndef FUNCTION_H
#define FUNCTION_H

#include "./Stmt.h"
#include "./FunctionExpr.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class Function: public Stmt {
    public:
      const Token* name;
      const Expr::FunctionExpr* function;

      Function(const Token* name, const Expr::FunctionExpr* function);
      void const accept(Visitor* visitor) const;
  };
};

#endif
