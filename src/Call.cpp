#include "./include/Call.h"

#include "./include/Visitor.h"
using namespace Expr;

Call::Call(const Expr* callee, const Token* paren, const std::vector<Expr*> arguments) : callee(callee), paren(paren), arguments(arguments) {}

void const Call::accept(Visitor* visitor) const {
  visitor->visit(this);
}