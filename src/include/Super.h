#ifndef SUPER_H
#define SUPER_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Super: public Expr {
    public:
      const Token* keyword;
      const Token* method;

      Super(const Token* keyword, const Token* method);
      void const accept(Visitor* visitor) const;
  };
};

#endif
