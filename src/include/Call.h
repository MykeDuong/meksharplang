#ifndef CALL_H
#define CALL_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Call: public Expr {
    public:
      const Expr* callee;
      const Token* paren;
      const std::vector<Expr*> arguments;

      Call(const Expr* callee, const Token* paren, const std::vector<Expr*> arguments);
      void const accept(Visitor* visitor) const;
  };
};

#endif
