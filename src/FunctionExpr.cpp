#include "./include/FunctionExpr.h"

#include "./include/Visitor.h"
using namespace Expr;

FunctionExpr::FunctionExpr(const std::vector<Token*> params, const std::vector<Stmt::Stmt*> body) : params(params), body(body) {}

void const FunctionExpr::accept(Visitor* visitor) const {
  visitor->visit(this);
}