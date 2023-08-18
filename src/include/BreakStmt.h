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

      BreakStmt();
      void const accept(Visitor* visitor) const;
  };
};

#endif
