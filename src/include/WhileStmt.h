#ifndef WHILESTMT_H
#define WHILESTMT_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class WhileStmt: public Stmt {
    public:
      const Expr::Expr* condition;
      const Stmt* body;

      WhileStmt(const Expr::Expr* condition, const Stmt* body);
      void const accept(Visitor* visitor) const;
  };
};

#endif
