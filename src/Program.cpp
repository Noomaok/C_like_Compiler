#include "Program.h"

Program::Program()
{}

Program::~Program()
{
	for(Function* functionPTR : allFunctions) 
	{
		delete functionPTR;
	}
}

void Program::addFunction(Function* newFunction) 
{
	allFunctions.push_back(newFunction);
}