#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <stdexcept>
#include <unordered_map>
#include <vector>
#include "Array.h"
#include "ArrayElement.h"
#include "Assign.h"
#include "Block.h"
#include "Call.h"
#include "ClassStmt.h"
#include "Environment.h"
#include "Expression.h"
#include "Function.h"
#include "FunctionExpr.h"
#include "Get.h"
#include "IfStmt.h"
#include "LiteralValue.h"
#include "Logical.h"
#include "Print.h"
#include "ReturnStmt.h"
#include "Stmt.h"
#include "ThisExpr.h"
#include "Var.h"
#include "Variable.h"
#include "Visitor.h"
#include "WhileStmt.h"

class Callable;

class Interpreter final: public Expr::Visitor, Stmt::Visitor {
  public:
    class BreakException: public std::runtime_error {
      public:
        BreakException(const std::string& message);
    };

    class ReturnException: public std::runtime_error {
      public:
        ReturnException(LiteralValue* const value);
        LiteralValue* const value;
    };

  private:
    LiteralValue* result;
    Environment* environment;
    bool isRepl;
    std::unordered_map<const Expr::Expr*, int> locals;
   
  public:
    Environment* const globals;

  public:
    Interpreter();
    void visit(const Stmt::Expression* stmt);
    void visit(const Stmt::Function* stmt);
    void visit(const Stmt::ClassStmt* stmt);
    void visit(const Stmt::Block* stmt);
    void visit(const Stmt::Print* stmt);
    void visit(const Stmt::WhileStmt* stmt);
    void visit(const Stmt::BreakStmt* stmt);
    void visit(const Stmt::Var* stmt);
    void visit(const Stmt::IfStmt* stmt);
    void visit(const Stmt::ReturnStmt* stmt);
    void visit(const Expr::FunctionExpr* expr);
    void visit(const Expr::Assign* expr);
    void visit(const Expr::Binary* expr);
    void visit(const Expr::Ternary* expr);
    void visit(const Expr::Logical* expr);
    void visit(const Expr::Grouping* expr);
    void visit(const Expr::Literal* expr);
    void visit(const Expr::Unary* expr);
    void visit(const Expr::Call* expr);
    void visit(const Expr::Get* expr);
    void visit(const Expr::Set* expr);
    void visit(const Expr::ThisExpr* expr);
    void visit(const Expr::Array* expr);
    void visit(const Expr::ArrayElement* expr);
    void visit(const Expr::Variable* expr);
    void interpret(const std::vector<Stmt::Stmt*>& statements, bool isRepl = false);
    void executeBlock(const std::vector<Stmt::Stmt*>& statements, Environment* environment);
    void resolve(const Expr::Expr* expr, int depth);

  private:
    void evaluate(const Expr::Expr* expr);
    void execute(const Stmt::Stmt* stmt);
    bool isTruthy(LiteralValue* value);
    void checkNumberOperand(const Token* op, const LiteralValue* operand, std::vector<LiteralValue*> deleted = {});
    void checkNumberOperand(const Token* op, const LiteralValue* leftVal, const LiteralValue* rightVal, std::vector<LiteralValue*> deleted = {});
    void checkNumberOrStringOperand(const Token* op, const LiteralValue* leftVal, const LiteralValue* rightVal, std::vector<LiteralValue*> deleted = {});
    LiteralValue* lookUpVariable(const Token* const name, const Expr::Expr* expr);
};

#endif 
