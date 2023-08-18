#include "./include/Var.h"

#include "./include/Visitor.h"
using namespace Stmt;

Var::Var(const Token* name, const Expr::Expr* initializer) : name(name), initializer(initializer) {}

void const Var::accept(Visitor* visitor) const {
  visitor->visit(this);
}