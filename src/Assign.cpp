#include "./include/Assign.h"

#include "./include/Visitor.h"
using namespace Expr;

Assign::Assign(const Token* name, const Expr* value) : name(name), value(value) {}

void const Assign::accept(Visitor* visitor) const {
  visitor->visit(this);
}