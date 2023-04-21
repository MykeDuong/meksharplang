#ifndef TOKEN_H
#define TOKEN_H

#include <string>
#include <set>
#include <iostream>

#include "./SyntaxType.h"
#include "ASTNode.h"

class Token: public ASTNode {
  private:
    SyntaxType type;
    int position = position;
    std::string text;
    void* value;

  public:
    std::vector<ASTNode*> getChildren();
    Token(SyntaxType type, int position, std::string text, void* value);
    SyntaxType getType();
    int getPosition();
    std::string getText();
    void* getValue();
    friend std::ostream& operator<<(std::ostream& os, const Token& token);
};

std::ostream& operator<<(std::ostream& os, const Token& token);
#endif 

