#include "./include/Grouping.h"

#include "./include/Visitor.h"
using namespace Expr;

Grouping::Grouping(const Expr* expr) : expr(expr) {}

void const Grouping::accept(Visitor* visitor) const {
  visitor->visit(this);
}