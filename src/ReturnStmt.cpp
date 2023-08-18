#include "./include/ReturnStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

ReturnStmt::ReturnStmt(const Token* keyword, const Expr::Expr* value) : keyword(keyword), value(value) {}

void const ReturnStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}