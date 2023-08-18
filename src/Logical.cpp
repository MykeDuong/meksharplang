#include "./include/Logical.h"

#include "./include/Visitor.h"
using namespace Expr;

Logical::Logical(const Expr* left, const Token* op, const Expr* right) : left(left), op(op), right(right) {}

void const Logical::accept(Visitor* visitor) const {
  visitor->visit(this);
}