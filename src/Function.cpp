#include "./include/Function.h"

#include "./include/Visitor.h"
using namespace Stmt;

Function::Function(const Token* name, const Expr::FunctionExpr* function) : name(name), function(function) {}

void const Function::accept(Visitor* visitor) const {
  visitor->visit(this);
}