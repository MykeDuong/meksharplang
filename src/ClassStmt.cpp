#include "./include/ClassStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

ClassStmt::ClassStmt(const Token* name, const std::vector<Function*> methods, const Expr::Variable* superclass) : name(name), methods(methods), superclass(superclass) {}

void const ClassStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}