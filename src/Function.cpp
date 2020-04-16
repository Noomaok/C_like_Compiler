#include "Function.h"

Function::Function(std::string name, Type returnType)
: name(name), returnType(returnType)
{}

Function::~Function()
{
	for(Instruction* instructionPTR : allInstructions) 
	{
		delete instructionPTR;
	}
}

void Function::addInstructions(Instruction* newInstruction)
{
	allInstructions.push_back(newInstruction);
}