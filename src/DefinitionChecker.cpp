#include "./include/DefinitionChecker.h"
#include "include/Assign.h"
#include "include/BreakStmt.h"
#include "include/Expr.h"
#include "include/IfStmt.h"
#include "include/Stmt.h"
#include "include/WhileStmt.h"

DefinitionChecker* DefinitionChecker::obj = nullptr;

DefinitionChecker::NodeDefinition DefinitionChecker::check(const Stmt::Stmt* stmt) {
  stmt->accept(this);
  return result;  
}

DefinitionChecker::NodeDefinition DefinitionChecker::check(const Expr::Expr* expr) {
  expr->accept(this);
  return result;  
}

DefinitionChecker::DefinitionChecker() {}

DefinitionChecker* DefinitionChecker::getChecker() {
  if (obj == nullptr) {
      obj = new DefinitionChecker();
  }  
  return obj;
}

void DefinitionChecker::visit(const Stmt::Block* stmt) { 
  result = DefinitionChecker::NodeDefinition::STMT_BLOCK;
}

void DefinitionChecker::visit(const Stmt::Expression* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_EXPR;
}

void DefinitionChecker::visit(const Stmt::ClassStmt* stmt) {
  result = DefinitionChecker::STMT_CLASS;
}

void DefinitionChecker::visit(const Stmt::IfStmt* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_IF;
}

void DefinitionChecker::visit(const Stmt::Print* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_PRINT;
}

void DefinitionChecker::visit(const Stmt::WhileStmt* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_WHILE;
}

void DefinitionChecker::visit(const Stmt::BreakStmt* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_BREAK;
}

void DefinitionChecker::visit(const Stmt::Function* stmt) {
  result = DefinitionChecker::STMT_FUN; 
}

void DefinitionChecker::visit(const Stmt::ReturnStmt* stmt) {
  result = DefinitionChecker::STMT_RETURN;
}

void DefinitionChecker::visit(const Stmt::Var* stmt) {
  result = DefinitionChecker::NodeDefinition::STMT_VAR;
}

void DefinitionChecker::visit(const Expr::FunctionExpr* expr) {
  result = DefinitionChecker::EXPR_FUN;
}

void DefinitionChecker::visit(const Expr::Assign* expr) {
  result = DefinitionChecker::EXPR_ASSIGN; 
}

void DefinitionChecker::visit(const Expr::Binary* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_BINARY;
}

void DefinitionChecker::visit(const Expr::Ternary* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_TERNARY;
}

void DefinitionChecker::visit(const Expr::Logical* expr) {
  result = DefinitionChecker::EXPR_LOGICAL;
}

void DefinitionChecker::visit(const Expr::Grouping* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_GROUPING;
}

void DefinitionChecker::visit(const Expr::Literal* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_LITERAL;
}

void DefinitionChecker::visit(const Expr::Unary* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_UNARY;
}

void DefinitionChecker::visit(const Expr::Call* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_CALL;
}

void DefinitionChecker::visit(const Expr::Get* expr) {
  result = DefinitionChecker::EXPR_GET;
}

void DefinitionChecker::visit(const Expr::Set* expr) {
  result = DefinitionChecker::EXPR_SET;
}

void DefinitionChecker::visit(const Expr::Array* expr) {
  result = DefinitionChecker::EXPR_ARR;
}
void DefinitionChecker::visit(const Expr::ArrayElement* expr) {
  result = DefinitionChecker::EXPR_ARR_ELEMENT;
}

void DefinitionChecker::visit(const Expr::Variable* expr) {
  result = DefinitionChecker::NodeDefinition::EXPR_VARIABLE;
}
