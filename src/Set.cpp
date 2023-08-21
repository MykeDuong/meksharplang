#include "./include/Set.h"

#include "./include/Visitor.h"
using namespace Expr;

Set::Set(const Expr* obj, const Token* name, const Expr* value) : obj(obj), name(name), value(value) {}

void const Set::accept(Visitor* visitor) const {
  visitor->visit(this);
}
