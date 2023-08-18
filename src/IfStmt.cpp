#include "./include/IfStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

IfStmt::IfStmt(const Expr::Expr* condition, const Stmt* thenBranch, const Stmt* elseBranch) : condition(condition), thenBranch(thenBranch), elseBranch(elseBranch) {}

void const IfStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}