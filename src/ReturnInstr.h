#pragma once

#include "Core.h"
#include "Instruction.h"
#include "Expression.h"

class ReturnInstr : public Instruction
{
public:
	ReturnInstr(Expression* exprReturned);
	~ReturnInstr();

	std::string buildIR(CFG* cfg);

private:
	Expression* exprReturned;
};