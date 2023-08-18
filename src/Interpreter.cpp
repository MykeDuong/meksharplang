#include "./include/Interpreter.h"
#include "include/Assign.h"
#include "include/BreakStmt.h"
#include "include/Call.h"
#include "include/Environment.h"
#include "include/ErrorHandler.h"
#include "include/Expression.h"
#include "include/FunctionExpr.h"
#include "include/IfStmt.h"
#include "include/LiteralValue.h"
#include "include/MekFunction.h"
#include "include/Print.h"
#include "include/ReturnStmt.h"
#include "include/RuntimeError.h"
#include "include/Stmt.h"
#include "include/TokenType.h"
#include <chrono>
#include <ctime>
#include <exception>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include "include/Callable.h"

Interpreter::Interpreter() : globals(new Environment()), isRepl(false) {
  environment = globals;
  class ClockFunction final: public Callable {
    public:
      int arity() override { return 0; }
      LiteralValue* call(Interpreter* interpreter, std::vector<LiteralValue*>& arguments) override {
        double count = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        return new LiteralValue(count);
      }
      std::string toString() override {
        return "<native clock fn>";
      }
  };
  
  ClockFunction* clockFunction = new ClockFunction();
  globals->define("clock", new LiteralValue(clockFunction));
}

Interpreter::BreakException::BreakException(const std::string& message) : std::runtime_error(message) {}

Interpreter::ReturnException::ReturnException(LiteralValue* const value) : value(value), std::runtime_error("Return") {}

void Interpreter::visit(const Stmt::Print* stmt) {
  evaluate(stmt->expression);
  std::cout << result->toString() << std::endl;
  delete result;
  result = nullptr;
}

void Interpreter::visit(const Stmt::Expression* stmt) {
  evaluate(stmt->expression);
  if (isRepl) std::cout << result->toString() << std::endl;
  delete result;
  result = nullptr;
}

void Interpreter::visit(const Stmt::Function* stmt) {
  std::shared_ptr<Environment> closure(this->environment);
  MekFunction* function = new MekFunction(stmt->function, closure);
  environment->define(stmt->name->lexeme, new LiteralValue(function));
}

void Interpreter::visit(const Stmt::Block* stmt) {
  std::shared_ptr<Environment> newEnvironment(new Environment(environment));
  executeBlock(stmt->statements, newEnvironment.get());
}

void Interpreter::visit(const Stmt::WhileStmt* stmt) {
  evaluate(stmt->condition);

  while (isTruthy(result)) {
    delete result;
    try {
      execute(stmt->body);
    } catch (BreakException e) {
      return;
    }
    evaluate(stmt->condition);
  }

  delete result;
}

void Interpreter::visit(const Stmt::BreakStmt* stmt) {
  throw BreakException("Break encountered");
}

void Interpreter::visit(const Stmt::IfStmt* stmt) {
  evaluate(stmt->condition);
  if (isTruthy(result)) {
    delete result;
    execute(stmt->thenBranch);
  } else if (stmt->elseBranch != nullptr) {
    delete result;
    execute(stmt->elseBranch);
  }
  delete result;
}

void Interpreter::visit(const Stmt::Var* stmt) {
  if (environment->contain(stmt->name->lexeme) && isRepl == false) {
    throw RuntimeError(stmt->name, "Already declared variable '" + stmt->name->lexeme + "'.");
  }
  LiteralValue* value;

  if (stmt->initializer != nullptr) {
    evaluate(stmt->initializer);
    value = result;
  } else {
    value = nullptr;
  }

  environment->define(stmt->name->lexeme, value);
  delete value;
  result = nullptr;
}

void Interpreter::visit(const Stmt::ReturnStmt* stmt) {
  LiteralValue* value;
  if (stmt->value != nullptr) {
    evaluate(stmt->value);
    value = new LiteralValue(result);
    delete result;
  } else {
    value = new LiteralValue();
  }
  throw ReturnException(value);
}

void Interpreter::visit(const Expr::FunctionExpr* expr) {
  std::shared_ptr<Environment> closure(this->environment);
  MekFunction* function = new MekFunction(expr, closure);

  result = new LiteralValue(function);
  std::cout << result->toString() << std::endl;
}

void Interpreter::visit(const Expr::Assign* expr) {
  evaluate(expr->value);
  environment->assign(expr->name, result);
}

void Interpreter::visit(const Expr::Binary* expr) {
  evaluate(expr->left);
  LiteralValue* leftVal = result;
  evaluate(expr->right);
  LiteralValue* rightVal = result;

  switch (expr->op->type) {
    case COMMA:
      result = new LiteralValue(rightVal);
      break;
    case GREATER:
      if (leftVal->type == LiteralValue::LITERAL_NUMBER && rightVal->type == LiteralValue::LITERAL_NUMBER) {
        result = new LiteralValue(leftVal->numericValue > rightVal->numericValue);
        break;
      }

      if (leftVal->type == LiteralValue::LITERAL_STRING && rightVal->type == LiteralValue::LITERAL_STRING) {
        result = new LiteralValue(leftVal->stringValue > rightVal->stringValue);
        break;
      }
      delete leftVal;
      delete rightVal;
      throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
      break;
    case GREATER_EQUAL:
      if (leftVal->type == LiteralValue::LITERAL_NUMBER && rightVal->type == LiteralValue::LITERAL_NUMBER) {
        result = new LiteralValue(leftVal->numericValue >= rightVal->numericValue);
        break;
      }

      if (leftVal->type == LiteralValue::LITERAL_STRING && rightVal->type == LiteralValue::LITERAL_STRING) {
        result = new LiteralValue(leftVal->stringValue >= rightVal->stringValue);
        break;
      }
      delete leftVal;
      delete rightVal;
      throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
      break;
    case LESS:
      if (leftVal->type == LiteralValue::LITERAL_NUMBER && rightVal->type == LiteralValue::LITERAL_NUMBER) {
        result = new LiteralValue(leftVal->numericValue < rightVal->numericValue);
        break;
      }

      if (leftVal->type == LiteralValue::LITERAL_STRING && rightVal->type == LiteralValue::LITERAL_STRING) {
        result = new LiteralValue(leftVal->stringValue < rightVal->stringValue);
        break;
      }
      delete leftVal;
      delete rightVal;
      throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
      break;
    case LESS_EQUAL:
      if (leftVal->type == LiteralValue::LITERAL_NUMBER && rightVal->type == LiteralValue::LITERAL_NUMBER) {
        result = new LiteralValue(leftVal->numericValue <= rightVal->numericValue);
        break;
      }

      if (leftVal->type == LiteralValue::LITERAL_STRING && rightVal->type == LiteralValue::LITERAL_STRING) {
        result = new LiteralValue(leftVal->stringValue <= rightVal->stringValue);
        break;
      }
      delete leftVal;
      delete rightVal;
      throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
      break;
    case BANG_EQUAL:
      result = new LiteralValue(leftVal->numericValue != rightVal->numericValue);
      break;
    case EQUAL_EQUAL:
      result = new LiteralValue(leftVal->numericValue == rightVal->numericValue);
      break;
    case MINUS:
      checkNumberOperand(expr->op, leftVal, rightVal);
      result = new LiteralValue(leftVal->numericValue - rightVal->numericValue);
      break;
    case SLASH:
      checkNumberOperand(expr->op, leftVal, rightVal);
      if (rightVal->numericValue == 0) throw RuntimeError(expr->op, "Divided by 0.");
      result = new LiteralValue(leftVal->numericValue / rightVal->numericValue);
      break;
    case STAR:
      checkNumberOperand(expr->op, leftVal, rightVal);
      result = new LiteralValue(leftVal->numericValue * rightVal->numericValue);
      break;
    case PLUS:
      if (leftVal->type == LiteralValue::LITERAL_NUMBER && rightVal->type == LiteralValue::LITERAL_NUMBER) {
        result = new LiteralValue(leftVal->numericValue + rightVal->numericValue);
        break;
      }

      if (leftVal->type == LiteralValue::LITERAL_STRING || rightVal->type == LiteralValue::LITERAL_STRING) {
        result = new LiteralValue(leftVal->toString() + rightVal->toString());
        break;
      }
      delete leftVal;
      delete rightVal;
      throw RuntimeError(expr->op, "Operands must be two numbers or two strings.");
      break;
    default:
      // unreachable
      std::cout << "Unreachable code reach on Binary Interpreter with operation " << expr->op->type << std::endl;

  }

  delete leftVal;
  delete rightVal;
}

void Interpreter::visit(const Expr::Ternary* expr) {
  evaluate(expr->firstExpr);
  LiteralValue* firstVal = result;


  if (expr->firstOp->type != QUESTION && expr->secondOp->type != COMMA) {
    throw RuntimeError(expr->firstOp, "Ternary Conditional Operator expected.");
  }

  if (isTruthy(firstVal)) {
    evaluate(expr->secondExpr);
  } else {
    evaluate(expr->thirdExpr);
  }

  delete firstVal;
}

void Interpreter::visit(const Expr::Logical* expr) {
  evaluate(expr->left);

  if (expr->op->type == TokenType::OR) {
    if (isTruthy(result)) return;
  } else {
    if (!isTruthy(result)) return;
  }

  delete result;
  evaluate(expr->right);
  return;
}

void Interpreter::visit(const Expr::Grouping* expr) {
  evaluate(expr->expr);
}

void Interpreter::visit(const Expr::Literal* expr) {
  result = new LiteralValue(expr->value);
}

void Interpreter::visit(const Expr::Unary* expr) {
  evaluate(expr->right);
  LiteralValue* rightVal = result;

  switch(expr->op->type) {
    case MINUS:
      checkNumberOperand(expr->op, rightVal);
      result = new LiteralValue(-rightVal->numericValue);
      break;
    case BANG:
      result = new LiteralValue(!isTruthy(rightVal));
      break;
    default:
      // unreachable
      std::cout << "Unreachable code reached" << std::endl;
      break;
  }

  delete rightVal;
}

void Interpreter::visit(const Expr::Call* expr) {
  evaluate(expr->callee);

  LiteralValue* callee = result;

  std::vector<LiteralValue*> arguments;

  for (Expr::Expr* argument: expr->arguments) {
    evaluate(argument);
    arguments.push_back(result);
  }
  if (callee->type != LiteralValue::LITERAL_CALLABLE) {
    throw RuntimeError(expr->paren, "Can only call functions and classes");
  }

  Callable* function = callee->callableValue.get();
  if (arguments.size() != function->arity()) {
    throw RuntimeError(
      expr->paren, 
      "Expected " + std::to_string(function->arity()) + " arguments but got "  + 
      std::to_string(arguments.size()) + "."
    );
  }

  result = function->call(this, arguments);
}

void Interpreter::visit(const Expr::Variable* expr) {
  result = new LiteralValue(environment->get(expr->name));
}

void Interpreter::interpret(const std::vector<Stmt::Stmt*>& statements, bool isRepl) {
  this->isRepl = isRepl; 
  try {
    for (Stmt::Stmt* statement: statements) {
      execute(statement);
    }
  } catch (RuntimeError& error) {
    ErrorHandler::runtimeError(error);
  }
}

void Interpreter::evaluate(const Expr::Expr* expr) {
  expr->accept(this);
}

void Interpreter::execute(const Stmt::Stmt* stmt) {
  stmt->accept(this);
}

bool Interpreter::isTruthy(LiteralValue* value) {
  switch (value->type) {
    case LiteralValue::LITERAL_NULL:
      return false;
      break;
    case LiteralValue::LITERAL_BOOL:
      return value->boolValue;
      break;
    case LiteralValue::LITERAL_NUMBER:
      return value->numericValue == 0 ? false : true;
      break;
    default:
      return true;
  }
}

void Interpreter::checkNumberOperand(
  const Token* op, 
  const LiteralValue* operand, 
  std::vector<LiteralValue*> deleted
) {
  if (operand->type == LiteralValue::LITERAL_NUMBER) return;
  delete operand;
  for (auto l: deleted) {
    delete l;
  }
  
  deleted.clear();
  throw RuntimeError(op, "Operand must be a number.");
}

void Interpreter::checkNumberOperand(
  const Token* op, 
  const LiteralValue* leftVal, 
  const LiteralValue* rightVal, 
  std::vector<LiteralValue*> deleted
) {
  if (
    leftVal->type == LiteralValue::LITERAL_NUMBER &&
    rightVal->type == LiteralValue::LITERAL_NUMBER
  ) return;
  delete leftVal;
  delete rightVal;

  for (auto l: deleted) {
    delete l;
  }
  deleted.clear();
  throw RuntimeError(op, "Operands must be two numbers.");
}

void Interpreter::checkNumberOrStringOperand(
  const Token* op, 
  const LiteralValue* leftVal, 
  const LiteralValue* rightVal, 
  std::vector<LiteralValue*> deleted
) {
  if (
    leftVal->type == LiteralValue::LITERAL_NUMBER &&
    rightVal->type == LiteralValue::LITERAL_NUMBER
  ) return;

  if (
    leftVal->type == LiteralValue::LITERAL_STRING &&
    rightVal->type == LiteralValue::LITERAL_STRING
  ) return;
  
  delete leftVal;
  delete rightVal;

  for (auto l: deleted) {
    delete l;
  }
  deleted.clear();
  throw RuntimeError(op, "Operands must be two numbers or two strings.");
}

void Interpreter::executeBlock(const std::vector<Stmt::Stmt*>& statements, Environment* environment) {
  Environment* previous = this->environment;
  try {
    this->environment = environment;
    for (Stmt::Stmt* stmt: statements) {
      execute(stmt);
    }
    this->environment = previous;
  } catch(BreakException& e) {
    this->environment = previous;
    throw e;
  } catch(ReturnException& e) {
    this->environment = previous;
    throw e;
  }catch (RuntimeError& e) {
    this->environment = previous;
    throw e;
  }
}
