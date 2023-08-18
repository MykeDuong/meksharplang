#ifndef STMT_H
#define STMT_H

namespace Stmt {
  class Visitor;

  class Stmt {
    public:
      virtual const void accept(Visitor* v) const = 0;
  };
};

#endif 
