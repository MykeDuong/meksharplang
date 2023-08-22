#ifndef RESOLVER_H
#define RESOLVER_H

#include "Array.h"
#include "ArrayElement.h"
#include "ClassStmt.h"
#include "Get.h"
#include "Set.h"
#include "ThisExpr.h"
#include "Visitor.h"
#include "Interpreter.h"
#include <unordered_map>
#include <vector>

class Resolver final: public Expr::Visitor, Stmt::Visitor {
  private:
    enum FunctionType { NONE_FUNCTION, FUNCTION, METHOD, INITIALIZER };
    enum ClassType { NONE_CLASS, CLASS, SUBCLASS };
  private:
    Interpreter* interpreter;
    std::vector<std::unordered_map<std::string, bool>> scopes;
    FunctionType currentFunction = NONE_FUNCTION;
    ClassType currentClass = NONE_CLASS;
    bool currentLoop = false;

  public:
    Resolver(Interpreter* interpreter);
    void visit(const Stmt::Block* block) override;
    void visit(const Stmt::Expression* expression) override;
    void visit(const Stmt::Function* function) override;
    void visit(const Stmt::IfStmt* ifstmt) override;
    void visit(const Stmt::ClassStmt* stmt) override;
    void visit(const Stmt::Print* print) override;
    void visit(const Stmt::Var* var) override;
    void visit(const Stmt::WhileStmt* whilestmt) override;
    void visit(const Stmt::BreakStmt* breakstmt) override;
    void visit(const Stmt::ReturnStmt* returnstmt) override;
    void visit(const Expr::FunctionExpr* functionexpr) override;
    void visit(const Expr::Assign* assign) override;
    void visit(const Expr::Binary* binary) override;
    void visit(const Expr::Call* call) override;
    void visit(const Expr::Ternary* ternary) override;
    void visit(const Expr::Grouping* grouping) override;
    void visit(const Expr::Literal* literal) override;
    void visit(const Expr::Logical* logical) override;
    void visit(const Expr::Set* set) override;
    void visit(const Expr::Get* get) override;
    void visit(const Expr::Super* expr) override;
    void visit(const Expr::ThisExpr* expr) override;
    void visit(const Expr::Unary* unary) override;
    void visit(const Expr::Array* array) override;
    void visit(const Expr::ArrayElement* arrayElement) override;
    void visit(const Expr::Variable* variable) override;
    void resolve(const std::vector<Stmt::Stmt*> statements);
    void resolve(const Stmt::Stmt* statement);
    void resolve(const Expr::Expr* expr);

  private:
    void resolveLocal(const Expr::Expr* expr, const Token* const name);
    void resolveFunction(const Expr::FunctionExpr* function, FunctionType type);
    void beginScope();
    void endScope();
    void declare(const Token* const name);
    void define(const Token* const name);
};


#endif 
