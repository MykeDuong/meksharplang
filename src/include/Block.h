#ifndef BLOCK_H
#define BLOCK_H

#include "./Stmt.h"
#include "./Expr.h"
#include "./Token.h"
#include "./LiteralValue.h"
#include <vector>

namespace Stmt {
  class Stmt;
  class Block: public Stmt {
    public:
      const std::vector<Stmt*> statements;

      Block(const std::vector<Stmt*> statements);
      void const accept(Visitor* visitor) const;
  };
};

#endif
