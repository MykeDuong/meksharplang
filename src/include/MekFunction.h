#ifndef MEK_FUNCTION_H
#define MEK_FUNCTION_H

#include "Callable.h"
#include "Environment.h"
#include "Function.h"
#include "FunctionExpr.h"
#include "Interpreter.h"
#include <vector>


class MekFunction final: public Callable {
  private:
    const Expr::FunctionExpr* declaration;
    const std::string name;
    std::shared_ptr<Environment> closure;

  public:
    MekFunction(const Expr::FunctionExpr* declaration, std::shared_ptr<Environment> closure, const std::string name = "");
    LiteralValue * call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) override;
    int arity() override;
    std::string toString() override;
};

#endif 
