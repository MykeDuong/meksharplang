#ifndef EXPR_H
#define EXPR_H

#include <string>

namespace Expr {
  class Visitor;

  class Expr {
    public:
      virtual const void accept(Visitor* v) const = 0;
  };
}

#endif  
