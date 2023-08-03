#include "./include/Interpreter.h"
#include "include/ErrorHandler.h"
#include "include/LiteralValue.h"
#include "include/RuntimeError.h"
#include "include/TokenType.h"
#include <iostream>
#include <vector>

Interpreter::Interpreter() {}

void Interpreter::visit(const Expr::Binary* expr) {
  evaluate(expr->left);
  LiteralValue* leftVal = result;
  evaluate(expr->right);
  LiteralValue* rightVal = result;

  switch (expr->op->type) {
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
      throw new RuntimeError(expr->op, "Operands must be two numbers or two strings.");
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
      throw new RuntimeError(expr->op, "Operands must be two numbers or two strings.");
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
      throw new RuntimeError(expr->op, "Operands must be two numbers or two strings.");
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
      throw new RuntimeError(expr->op, "Operands must be two numbers or two strings.");
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
      if (rightVal->numericValue == 0) throw new RuntimeError(expr->op, "Divided by 0.");
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
      throw new RuntimeError(expr->op, "Operands must be two numbers or two strings.");
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
  evaluate(expr->secondExpr);
  LiteralValue* secondVal = result;
  evaluate(expr->thirdExpr);
  LiteralValue* thirdVal = result;

  if (expr->firstOp->type != QUESTION && expr->secondOp->type != COMMA) {
    throw new RuntimeError(expr->firstOp, "Ternary Conditional Operator expected.");
  }

  result = isTruthy(firstVal) ? new LiteralValue(secondVal) : new LiteralValue(thirdVal);
  delete firstVal;
  delete secondVal;
  delete thirdVal;
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
  
void Interpreter::interpret(const Expr::Expr* expr) {
  try {
    evaluate(expr);
    std::cout << *result << std::endl;
  } catch (RuntimeError* error) {
    ErrorHandler::runtimeError(error);
  }
}

void Interpreter::evaluate(const Expr::Expr* expr) {
  expr->accept(this);
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
  std::cout << operand->type << std::endl; 
  delete operand;
  for (auto l: deleted) {
    delete l;
  }
  
  deleted.clear();
  throw new RuntimeError(op, "Operand must be a number.");
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
  throw new RuntimeError(op, "Operands must be two numbers.");
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
  throw new RuntimeError(op, "Operands must be two numbers or two strings.");
}
