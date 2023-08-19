#include "./include/ArrayElement.h"

#include "./include/Visitor.h"
using namespace Expr;

ArrayElement::ArrayElement(const Expr* callee, const Expr* index, const Token* square) : callee(callee), index(index), square(square) {}

void const ArrayElement::accept(Visitor* visitor) const {
  visitor->visit(this);
}