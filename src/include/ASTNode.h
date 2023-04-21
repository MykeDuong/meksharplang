#ifndef AST_NODE_H
#define AST_NODE_H

#include "./TokenType.h"

class ASTNode {
  public:
    virtual TokenType getType() = 0;
};

#endif
