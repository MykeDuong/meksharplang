#ifndef MEKCLASS_H
#define MEKCLASS_H

#include "Callable.h"

class MekClass final: public Callable { 
  public:
    const std::string name;

    MekClass(std::string name);
    std::string toString();
};

#endif MEKCLASS_H 
