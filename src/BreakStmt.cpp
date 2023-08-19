#include "./include/BreakStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

BreakStmt::BreakStmt(const Token* keyword) : keyword(keyword) {}

void const BreakStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}