#ifndef VARIABLE_H
#define VARIABLE_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Variable: public Expr {
    public:
      const Token* name;

      Variable(const Token* name);
      void const accept(Visitor* visitor) const;
  };
};

#endif
