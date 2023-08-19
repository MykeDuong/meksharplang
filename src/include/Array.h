#ifndef ARRAY_H
#define ARRAY_H

#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Expr {
  class Expr;
  class Array: public Expr {
    public:
      const std::vector<Expr*> elements;
      const Token* square;

      Array(const std::vector<Expr*> elements, const Token* square);
      void const accept(Visitor* visitor) const;
  };
};

#endif
