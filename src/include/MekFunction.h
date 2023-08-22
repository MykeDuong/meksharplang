#ifndef MEK_FUNCTION_H
#define MEK_FUNCTION_H

#include "Callable.h"
#include "Environment.h"
#include "Function.h"
#include "FunctionExpr.h"
#include "Interpreter.h"
#include "LiteralValue.h"
#include <vector>


class MekFunction final: public Callable {
  private:
    const Expr::FunctionExpr* declaration;
    const std::string name;
    std::shared_ptr<Environment> closure;
    const bool isInitializer;

  public:
    MekFunction(
      const Expr::FunctionExpr* declaration, 
      std::shared_ptr<Environment> closure, 
      const bool isInitializer = false, 
      const std::string name = ""
    );
    MekFunction* bind(MekInstance* instance);
    LiteralValue * call(Interpreter *interpreter, std::vector<LiteralValue *> &arguments) override;
    int arity() override;
    std::string toString() override;
};

#endif 
