#pragma once

#include "Core.h"
#include "Function.h"

class Program
{

public:
	Program();
	~Program();

	std::vector<Function*> getAllFunctions() { return allFunctions; };

	void addFunction(Function* newFunction);

private:
	std::vector<Function*> allFunctions;
};