#include "./include/Block.h"

#include "./include/Visitor.h"
using namespace Stmt;

Block::Block(const std::vector<Stmt*> statements) : statements(statements) {}

void const Block::accept(Visitor* visitor) const {
  visitor->visit(this);
}