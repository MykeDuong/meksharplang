#ifndef IFSTMT_H
#define IFSTMT_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class IfStmt: public Stmt {
    public:
      const Expr::Expr* condition;
      const Stmt* thenBranch;
      const Stmt* elseBranch;

      IfStmt(const Expr::Expr* condition, const Stmt* thenBranch, const Stmt* elseBranch);
      void const accept(Visitor* visitor) const;
  };
};

#endif
