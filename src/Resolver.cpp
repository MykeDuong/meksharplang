#include "./include/Resolver.h"
#include "./include/ErrorHandler.h"
#include "include/ClassStmt.h"
#include "include/Function.h"
#include <string>
#include <unordered_map>


Resolver::Resolver(Interpreter* interpreter): interpreter(interpreter) {}

void Resolver::visit(const Stmt::Block* block) {
  beginScope();
  resolve(block->statements);
  endScope();
}

void Resolver::visit(const Stmt::Expression* expression) {
  resolve(expression->expression);
}

void Resolver::visit(const Stmt::Function* function) {
  declare(function->name);
  define(function->name);

  resolveFunction(function->function, FUNCTION);
}

void Resolver::visit(const Stmt::IfStmt* ifstmt) {
  resolve(ifstmt->condition);
  resolve(ifstmt->thenBranch);
  if (ifstmt->elseBranch != nullptr) resolve(ifstmt->elseBranch);
}

void Resolver::visit(const Stmt::ClassStmt* stmt) {
  declare(stmt->name);
  define(stmt->name);

  for (Stmt::Function* method: stmt->methods) {
    FunctionType declaration = FunctionType::METHOD;
    declare(method->name);
    define(method->name);
    resolveFunction(method->function, declaration);
  }
}

void Resolver::visit(const Stmt::Print* print) {
  resolve(print->expression);
}

void Resolver::visit(const Stmt::Var* var) {
  declare(var->name);
  if (var->initializer != nullptr) {
    resolve(var->initializer);
    define(var->name);
  }
}

void Resolver::visit(const Stmt::WhileStmt* whilestmt) {
  bool enclosingLoop = currentLoop;
  currentLoop = true;
  resolve(whilestmt->condition);
  resolve(whilestmt->body);
  currentLoop = enclosingLoop;
}

void Resolver::visit(const Stmt::BreakStmt* breakstmt) {
  if (currentLoop == false) ErrorHandler::error(breakstmt->keyword, "Cannot break without being inside a for- or while-loop.");
}

void Resolver::visit(const Stmt::ReturnStmt* returnstmt) {
  if (currentFunction == NONE) ErrorHandler::error(returnstmt->keyword, "Cannot return from top-level code.");
  if (returnstmt->value != nullptr) resolve(returnstmt->value);
}


void Resolver::visit(const Expr::FunctionExpr* functionexpr) {
  resolveFunction(functionexpr, FunctionType::FUNCTION);
}

void Resolver::visit(const Expr::Assign* assign) {
  resolve(assign->value);
  resolveLocal(assign, assign->name);
}

void Resolver::visit(const Expr::Binary* binary) {
  resolve(binary->left);
  resolve(binary->right);
}

void Resolver::visit(const Expr::Call* call) {
  resolve(call->callee);

  for (Expr::Expr* argument: call->arguments) {
    resolve(argument);
  }
}

void Resolver::visit(const Expr::Ternary* ternary) {
  resolve(ternary->firstExpr);
  resolve(ternary->secondExpr);
  resolve(ternary->thirdExpr);
}

void Resolver::visit(const Expr::Grouping* grouping) {
  resolve(grouping->expr);
}

void Resolver::visit(const Expr::Literal* literal) {}

void Resolver::visit(const Expr::Logical* logical) {
  resolve(logical->left);
  resolve(logical->right);
}

void Resolver::visit(const Expr::Set* set) {
  resolve(set->value);
  resolve(set->obj);
}

void Resolver::visit(const Expr::Get* get) {
  resolve(get->obj);
}

void Resolver::visit(const Expr::Unary* unary) {
  resolve(unary->right);
}

void Resolver::visit(const Expr::Array* array) {
  for (auto expr: array->elements) {
    resolve(expr);
  }
}

void Resolver::visit(const Expr::ArrayElement* arrayElement)  {
  resolve(arrayElement->callee);
  resolve(arrayElement->index);
}

void Resolver::visit(const Expr::Variable* variable) {
  if (
    !scopes.empty() &&
    scopes.back().find(variable->name->lexeme) != scopes.back().end() &&
    scopes.back()[variable->name->lexeme] == false 
  ) {
    ErrorHandler::error(variable->name, "Can't read local variable in its own initializer.");
  }

  resolveLocal(variable, variable->name);
}

void Resolver::resolve(const std::vector<Stmt::Stmt*> statements) {
  for (auto statement: statements) {
    resolve(statement);
  }
}

void Resolver::resolve(const Stmt::Stmt* statement) {
  statement->accept(this);
}

void Resolver::resolve(const Expr::Expr* expr) {
  expr->accept(this);
}

void Resolver::resolveLocal(const Expr::Expr* expr, const Token* const name) {
  if (scopes.empty()) return;
  for (int i = scopes.size() - 1; i >= 0; i--) {
    if (scopes[i].find(name->lexeme) != scopes[i].end()) {
      interpreter->resolve(expr, scopes.size() - 1 - i);
      return;
    }
  }
}


void Resolver::resolveFunction(const Expr::FunctionExpr* function, FunctionType type) {
  FunctionType enclosingFunction = currentFunction;
  currentFunction = type;
  beginScope();
  for (Token* param: function->params) {
    declare(param);
    define(param);
  }
  resolve(function->body);
  endScope();
  currentFunction = enclosingFunction;
}

void Resolver::beginScope() {
  scopes.push_back(std::unordered_map<std::string, bool>());
}

void Resolver::endScope() {
  scopes.pop_back();
}

void Resolver::declare(const Token* const name) {
  if (scopes.empty()) return;

  std::unordered_map<std::string, bool> scope = scopes.back();
  if (scope.find(name->lexeme) != scope.end()) {
    ErrorHandler::error(name, "There is already a variable with this name in this scope.");
  }

  scope[name->lexeme] = false;
}

void Resolver::define(const Token* const name) {
  if (scopes.empty()) return;
  scopes.back()[name->lexeme] = true;
}

