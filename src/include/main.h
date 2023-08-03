#ifndef MAIN_H
#define MAIN_H

#include "Interpreter.h"
#include<string>


void runFile(std::string const& filename);

void runPrompt();

void run(std::string const& source);

void error(int line,std::string const& message);

#endif

