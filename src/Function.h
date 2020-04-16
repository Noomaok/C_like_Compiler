#pragma once

#include "Core.h"
#include "Instruction.h"

class Function
{
public:
	Function(std::string name, Type returnType);
	~Function();

	std::string getName() { return name; };
	std::vector<Instruction*> getInstructions() { return allInstructions; };

	void addInstructions(Instruction* newInstruction);

private:
	std::string name;
	Type returnType;
	std::vector<Instruction*> allInstructions;
};