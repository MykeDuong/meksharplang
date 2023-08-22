#ifndef VISITOR_H
#define VISITOR_H

#include "./FunctionExpr.h"
#include "./Assign.h"
#include "./Binary.h"
#include "./Call.h"
#include "./Get.h"
#include "./Set.h"
#include "./Super.h"
#include "./ThisExpr.h"
#include "./Ternary.h"
#include "./Grouping.h"
#include "./Literal.h"
#include "./Logical.h"
#include "./Unary.h"
#include "./Array.h"
#include "./ArrayElement.h"
#include "./Variable.h"
#include "./Block.h"
#include "./ClassStmt.h"
#include "./Expression.h"
#include "./Function.h"
#include "./IfStmt.h"
#include "./Print.h"
#include "./Var.h"
#include "./WhileStmt.h"
#include "./BreakStmt.h"
#include "./ReturnStmt.h"
namespace Expr {
  class Visitor {
    public:
      virtual void visit(const FunctionExpr* functionexpr) = 0;
      virtual void visit(const Assign* assign) = 0;
      virtual void visit(const Binary* binary) = 0;
      virtual void visit(const Call* call) = 0;
      virtual void visit(const Get* get) = 0;
      virtual void visit(const Set* set) = 0;
      virtual void visit(const Super* super) = 0;
      virtual void visit(const ThisExpr* thisexpr) = 0;
      virtual void visit(const Ternary* ternary) = 0;
      virtual void visit(const Grouping* grouping) = 0;
      virtual void visit(const Literal* literal) = 0;
      virtual void visit(const Logical* logical) = 0;
      virtual void visit(const Unary* unary) = 0;
      virtual void visit(const Array* array) = 0;
      virtual void visit(const ArrayElement* arrayelement) = 0;
      virtual void visit(const Variable* variable) = 0;
    };
};

namespace Stmt {
  class Visitor {
    public:
      virtual void visit(const Block* block) = 0;
      virtual void visit(const ClassStmt* classstmt) = 0;
      virtual void visit(const Expression* expression) = 0;
      virtual void visit(const Function* function) = 0;
      virtual void visit(const IfStmt* ifstmt) = 0;
      virtual void visit(const Print* print) = 0;
      virtual void visit(const Var* var) = 0;
      virtual void visit(const WhileStmt* whilestmt) = 0;
      virtual void visit(const BreakStmt* breakstmt) = 0;
      virtual void visit(const ReturnStmt* returnstmt) = 0;
    };
};


#endif
