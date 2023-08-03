#ifndef INTERPRETER_H
#define INTERPRETER_H

#include "LiteralValue.h"
#include "Visitor.h"
#include <vector>

class Interpreter: public Expr::Visitor {
  private:
    LiteralValue* result;

  public:
    Interpreter();
    void visit(const Expr::Binary* expr);
    void visit(const Expr::Ternary* expr);
    void visit(const Expr::Grouping* expr);
    void visit(const Expr::Literal* expr);
    void visit(const Expr::Unary* expr);
    void interpret(const Expr::Expr* expr);

  private:
    void evaluate(const Expr::Expr* expr);
    bool isTruthy(LiteralValue* value);
    void checkNumberOperand(const Token* op, const LiteralValue* operand, std::vector<LiteralValue*> deleted = {});
    void checkNumberOperand(const Token* op, const LiteralValue* leftVal, const LiteralValue* rightVal, std::vector<LiteralValue*> deleted = {});
    void checkNumberOrStringOperand(const Token* op, const LiteralValue* leftVal, const LiteralValue* rightVal, std::vector<LiteralValue*> deleted = {});
};

#endif 
