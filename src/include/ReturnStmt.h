#ifndef RETURNSTMT_H
#define RETURNSTMT_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class ReturnStmt: public Stmt {
    public:
      const Token* keyword;
      const Expr::Expr* value;

      ReturnStmt(const Token* keyword, const Expr::Expr* value);
      void const accept(Visitor* visitor) const;
  };
};

#endif
