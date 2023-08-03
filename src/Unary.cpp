#include "./include/Unary.h"

#include "./include/Visitor.h"
using namespace Expr;

Unary::Unary(const Token* op, const Expr* right) : op(op), right(right) {}

void const Unary::accept(Visitor* visitor) const {
  visitor->visit(this);
}