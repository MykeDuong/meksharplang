#ifndef BREAKSTMT_H
#define BREAKSTMT_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class BreakStmt: public Stmt {
    public:
      const Token* keyword;

      BreakStmt(const Token* keyword);
      void const accept(Visitor* visitor) const;
  };
};

#endif
