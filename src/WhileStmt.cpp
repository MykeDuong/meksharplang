#include "./include/WhileStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

WhileStmt::WhileStmt(const Expr::Expr* condition, const Stmt* body) : condition(condition), body(body) {}

void const WhileStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}