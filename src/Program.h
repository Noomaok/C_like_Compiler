#pragma once

#include "Core.h"
#include "Function.h"
#include "Symbol.h"

class Program
{

public:
	Program();
	~Program();

	std::vector<Function*> getAllFunctions() { return allFunctions; };

	void addFunction(Function* newFunction);

	std::map<std::string, Symbol*> symbolTable;

private:
	std::vector<Function*> allFunctions;
};