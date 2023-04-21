#ifndef AST_NODE_H
#define AST_NODE_H

#include <vector>

#include "./SyntaxType.h"

class ASTNode {
  public:
    virtual SyntaxType getType() = 0;
    virtual std::vector<ASTNode*> getChildren() = 0;
};

#endif
