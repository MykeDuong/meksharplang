#ifndef DEFINITION_CHECKER_H
#define DEFINITION_CHECKER_H

#include "Assign.h"
#include "Block.h"
#include "BreakStmt.h"
#include "Call.h"
#include "Function.h"
#include "FunctionExpr.h"
#include "Logical.h"
#include "ReturnStmt.h"
#include "Visitor.h"

#include "Stmt.h"
#include "WhileStmt.h"
class DefinitionChecker: public Expr::Visitor, Stmt::Visitor {
  public:
    enum NodeDefinition {
      STMT_EXPR,
      STMT_IF,
      STMT_PRINT,
      STMT_WHILE,
      STMT_BLOCK,
      STMT_BREAK,
      STMT_FUN,
      STMT_RETURN,
      STMT_VAR,
      EXPR_FUN,
      EXPR_ASSIGN,
      EXPR_BINARY,
      EXPR_TERNARY,
      EXPR_LOGICAL,
      EXPR_GROUPING,
      EXPR_LITERAL,
      EXPR_UNARY,
      EXPR_CALL,
      EXPR_VARIABLE
    };
  
  private:
    NodeDefinition result;
    DefinitionChecker();
    static DefinitionChecker* obj;

  public:
    static DefinitionChecker* getChecker();
    void visit(const Stmt::Block* stmt);
    void visit(const Stmt::Expression* stmt);
    void visit(const Stmt::IfStmt* stmt);
    void visit(const Stmt::Print* stmt);
    void visit(const Stmt::WhileStmt* stmt);
    void visit(const Stmt::BreakStmt* stmt);
    void visit(const Stmt::Function* stmt);
    void visit(const Stmt::ReturnStmt* stmt);
    void visit(const Stmt::Var* stmt);
    void visit(const Expr::FunctionExpr* expr);
    void visit(const Expr::Assign* expr);
    void visit(const Expr::Binary* expr);
    void visit(const Expr::Ternary* expr);
    void visit(const Expr::Logical* expr);
    void visit(const Expr::Grouping* expr);
    void visit(const Expr::Literal* expr);
    void visit(const Expr::Unary* expr);
    void visit(const Expr::Call* expr);
    void visit(const Expr::Variable* expr);
    NodeDefinition check(const Stmt::Stmt* stmt);
    NodeDefinition check(const Expr::Expr* expr);

};

#endif 
