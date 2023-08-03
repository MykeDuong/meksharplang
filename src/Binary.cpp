#include "./include/Binary.h"

#include "./include/Visitor.h"
using namespace Expr;

Binary::Binary(const Expr* left, const Token* op, const Expr* right) : left(left), op(op), right(right) {}

void const Binary::accept(Visitor* visitor) const {
  visitor->visit(this);
}