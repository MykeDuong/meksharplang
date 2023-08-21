#include "./include/Get.h"

#include "./include/Visitor.h"
using namespace Expr;

Get::Get(const Expr* obj, const Token* name) : obj(obj), name(name) {}

void const Get::accept(Visitor* visitor) const {
  visitor->visit(this);
}