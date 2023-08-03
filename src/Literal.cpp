#include "./include/Literal.h"

#include "./include/Visitor.h"
using namespace Expr;

Literal::Literal(const LiteralValue* value) : value(value) {}

void const Literal::accept(Visitor* visitor) const {
  visitor->visit(this);
}