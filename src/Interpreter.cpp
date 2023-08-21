#include "./include/Interpreter.h"
#include "include/Assign.h"
#include "include/BreakStmt.h"
#include "include/Call.h"
#include "include/ClassStmt.h"
#include "include/DefinitionChecker.h"
#include "include/Environment.h"
#include "include/ErrorHandler.h"
#include "include/Expression.h"
#include "include/Function.h"
#include "include/FunctionExpr.h"
#include "include/Get.h"
#include "include/IfStmt.h"
#include "include/LiteralValue.h"
#include "include/MekFunction.h"
#include "include/MekClass.h"
#include "include/MekInstance.h"
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
#include <unordered_map>
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

void Interpreter::visit(const Stmt::ClassStmt* stmt) {
  environment->define(stmt->name->lexeme, nullptr);
  std::unordered_map<std::string, MekFunction*> methods;

  for (Stmt::Function* method: stmt->methods) {
    MekFunction* function = new MekFunction(method->function, std::shared_ptr<Environment>(environment));
    if (methods.find(method->name->lexeme) != methods.end()) {
      throw RuntimeError(method->name, "Overloading not supported.");
    }
    methods[method->name->lexeme] = function;
  }

  MekClass* klass = new MekClass(stmt->name->lexeme, methods);
  LiteralValue* classValue = new LiteralValue(klass);
  environment->assign(stmt->name, classValue);
  delete classValue;
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
}

void Interpreter::visit(const Expr::Assign* expr) {
  evaluate(expr->value);

  if (locals.find(expr) != locals.end()) {
    environment->assignAt(locals[expr], expr->name, result);
  } else {
    environment->assign(expr->name, result);
  }
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
      result = new LiteralValue(*leftVal != *rightVal); 
      break;
    case EQUAL_EQUAL:
      result = new LiteralValue(*leftVal == *rightVal); 
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
  if (callee->type != LiteralValue::LITERAL_CLASS && callee->type != LiteralValue::LITERAL_FUNCTION) {
    throw RuntimeError(expr->paren, "Can only call functions and classes");
  }

  Callable* function;
  
  if (callee->type == LiteralValue::LITERAL_FUNCTION) {
    function = callee->functionValue;
  }
  if (callee->type == LiteralValue::LITERAL_CLASS) {
    function = callee->classValue;
  }

  if (arguments.size() != function->arity()) {
    throw RuntimeError(
      expr->paren, 
      "Expected " + std::to_string(function->arity()) + " arguments but got "  + 
      std::to_string(arguments.size()) + "."
    );
  }

  result = function->call(this, arguments);
}

void Interpreter::visit(const Expr::Get* expr) {
  evaluate(expr->obj);
  LiteralValue* obj = result;
  
  if (obj->type == LiteralValue::LITERAL_INSTANCE) {
    result = obj->instanceValue->get(expr->name);
    delete obj;
  } else {
    delete obj;
    throw RuntimeError(expr->name, "Only instances have properties");
  }

}

void Interpreter::visit(const Expr::Set* expr) {
  evaluate(expr->obj);

  LiteralValue* obj = result;
  if (obj->type != LiteralValue::LITERAL_INSTANCE) {
    throw RuntimeError(expr->name, "Only instances have fields");
  }

  evaluate(expr->value);
  obj->instanceValue->set(expr->name, result);
  delete obj;
}

void Interpreter::visit(const Expr::Array* expr) {
  std::vector<LiteralValue*> elements;

  for (Expr::Expr* expression: expr->elements) {
    evaluate(expression);
    elements.push_back(result);
  }
  result = new LiteralValue(elements);
}

void Interpreter::visit(const Expr::ArrayElement* expr) {
  evaluate(expr->callee);
  LiteralValue* callee = result;
  
  if (callee->type != LiteralValue::LITERAL_ARRAY) {
    throw RuntimeError(expr->square, "The identifier is not an array.");
  }

  evaluate(expr->index);
  LiteralValue* indexValue = result;
  if (indexValue->type != LiteralValue::LITERAL_NUMBER) {
    throw RuntimeError(expr->square, "The given index is not a number.");
  }
  double intpart;
  if (modf(indexValue->numericValue, &intpart) != 0.0) {
    throw RuntimeError(expr->square, "The given index is not an integer.");
  }


  std::vector<LiteralValue*> array = callee->arrayValue;
  if (indexValue->numericValue < 0 || indexValue->numericValue >= array.size()) {
    throw RuntimeError(expr->square, "Index out of range.");
  } 
  result = array[indexValue->numericValue]; 
}

void Interpreter::visit(const Expr::Variable* expr) {
  result = new LiteralValue(lookUpVariable(expr->name, expr));
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

void Interpreter::resolve(const Expr::Expr* expr, int depth) {
  locals[expr] = depth;
}


LiteralValue* Interpreter::lookUpVariable(const Token* const name, const Expr::Variable* expr) {
  if (locals.find(expr) == locals.end()) {
    return globals->get(name);
  } else {
    int distance = locals[expr];
    return environment->getAt(distance, name->lexeme);
  }
}
