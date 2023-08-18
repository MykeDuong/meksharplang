#include "./include/Variable.h"

#include "./include/Visitor.h"
using namespace Expr;

Variable::Variable(const Token* name) : name(name) {}

void const Variable::accept(Visitor* visitor) const {
  visitor->visit(this);
}