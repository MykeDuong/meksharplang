#include "./include/Super.h"

#include "./include/Visitor.h"
using namespace Expr;

Super::Super(const Token* keyword, const Token* method) : keyword(keyword), method(method) {}

void const Super::accept(Visitor* visitor) const {
  visitor->visit(this);
}