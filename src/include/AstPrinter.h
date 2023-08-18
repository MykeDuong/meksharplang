#ifndef AST_PRINTER_H
#define AST_PRINTER_H

#include "./Visitor.h"
#include "Binary.h"
#include "Ternary.h"
#include <string>
#include <vector>

class AstPrinter final: public Expr::Visitor {
  private:
    std::string result;

  public:
    void visit(const Expr::Binary* expr);
    void visit(const Expr::Ternary* expr);
    void visit(const Expr::Grouping* expr);
    void visit(const Expr::Literal* expr);
    void visit(const Expr::Unary* expr);
    void visit(const Expr::Variable* expr); 
    std::string print( Expr::Expr* expr);
  
  private:
    void const parenthesize(std::string name, std::vector<const Expr::Expr*> exprs);
};

#endif
