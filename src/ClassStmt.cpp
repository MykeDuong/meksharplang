#include "./include/ClassStmt.h"

#include "./include/Visitor.h"
using namespace Stmt;

ClassStmt::ClassStmt(const Token* name, const std::vector<Function*> methods) : name(name), methods(methods) {}

void const ClassStmt::accept(Visitor* visitor) const {
  visitor->visit(this);
}