#ifndef CLASSSTMT_H
#define CLASSSTMT_H

#include "./Stmt.h"
#include "./Function.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class ClassStmt: public Stmt {
    public:
      const Token* name;
      const std::vector<Function*> methods;

      ClassStmt(const Token* name, const std::vector<Function*> methods);
      void const accept(Visitor* visitor) const;
  };
};

#endif
