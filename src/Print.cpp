#include "./include/Print.h"

#include "./include/Visitor.h"
using namespace Stmt;

Print::Print(const Expr::Expr* expression) : expression(expression) {}

void const Print::accept(Visitor* visitor) const {
  visitor->visit(this);
}