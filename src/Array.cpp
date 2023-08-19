#include "./include/Array.h"

#include "./include/Visitor.h"
using namespace Expr;

Array::Array(const std::vector<Expr*> elements, const Token* square) : elements(elements), square(square) {}

void const Array::accept(Visitor* visitor) const {
  visitor->visit(this);
}