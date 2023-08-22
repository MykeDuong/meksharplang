#include "./include/ThisExpr.h"

#include "./include/Visitor.h"
using namespace Expr;

ThisExpr::ThisExpr(const Token* keyword) : keyword(keyword) {}

void const ThisExpr::accept(Visitor* visitor) const {
  visitor->visit(this);
}