#include "./include/Ternary.h"

#include "./include/Visitor.h"
using namespace Expr;

Ternary::Ternary(const Expr* firstExpr, const Token* firstOp, const Expr* secondExpr, const Token* secondOp, const Expr* thirdExpr) : firstExpr(firstExpr), firstOp(firstOp), secondExpr(secondExpr), secondOp(secondOp), thirdExpr(thirdExpr) {}

void const Ternary::accept(Visitor* visitor) const {
  visitor->visit(this);
}