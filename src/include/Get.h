#ifndef GET_H
#define GET_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Get: public Expr {
    public:
      const Expr* obj;
      const Token* name;

      Get(const Expr* obj, const Token* name);
      void const accept(Visitor* visitor) const;
  };
};

#endif
