#ifndef THISEXPR_H
#define THISEXPR_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class ThisExpr: public Expr {
    public:
      const Token* keyword;

      ThisExpr(const Token* keyword);
      void const accept(Visitor* visitor) const;
  };
};

#endif
