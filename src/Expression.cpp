#include "./include/Expression.h"

#include "./include/Visitor.h"
using namespace Stmt;

Expression::Expression(const Expr::Expr* expression) : expression(expression) {}

void const Expression::accept(Visitor* visitor) const {
  visitor->visit(this);
}