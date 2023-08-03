#ifndef VISITOR_H
#define VISITOR_H

#include "./Binary.h"
#include "./Ternary.h"
#include "./Grouping.h"
#include "./Literal.h"
#include "./Unary.h"
namespace Expr {
  class Visitor {
    public:
      virtual void visit(const Binary* binary) = 0;
      virtual void visit(const Ternary* ternary) = 0;
      virtual void visit(const Grouping* grouping) = 0;
      virtual void visit(const Literal* literal) = 0;
      virtual void visit(const Unary* unary) = 0;
    };
};

#endif
