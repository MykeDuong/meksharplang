#include "./include/AstPrinter.h"
#include "include/Expr.h"
#include "include/Grouping.h"
#include "include/Literal.h"
#include "include/Unary.h"
#include <cstdarg>
#include <vector>

#define VE std::vector<const Expr::Expr*>
std::string AstPrinter::print(Expr::Expr *expr) {
  expr->accept(this);
  return this->result;
}

void AstPrinter::visit(const Expr::Binary* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  parenthesize(expr->op->lexeme, VE{expr->left, expr->right});
}

void AstPrinter::visit(const Expr::Ternary* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  parenthesize(expr->firstOp->lexeme + expr->secondOp->lexeme, VE{expr->firstExpr, expr->secondExpr, expr->thirdExpr});
}

void AstPrinter::visit(const Expr::Grouping* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  parenthesize("group", VE{expr->expr});
}

void AstPrinter::visit(const Expr::Literal* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  if (expr->value->type == LiteralValue::LITERAL_NULL) {
    parenthesize("nah", VE{nullptr});
  }
  parenthesize(expr->value->toString(), VE{nullptr});
}

void AstPrinter::visit(const Expr::Unary* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  parenthesize(expr->op->lexeme, VE{expr->right});
}

void AstPrinter::visit(const Expr::Variable* expr) {
  if (expr == nullptr) {
    result += "null";
    return;
  }
  parenthesize(expr->name->lexeme, VE{nullptr});
}

void const AstPrinter::parenthesize(std::string name, std::vector<const Expr::Expr*> exprs) {
  result.push_back('(');
  result += name;

  for (const Expr::Expr* expr: exprs) {
    if (expr == nullptr) continue;
    result.push_back(' ');
    expr->accept(this);
  }
  result.push_back(')');

  exprs.clear();
}

#undef VE
