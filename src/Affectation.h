#pragma once

#include "Core.h"
#include "Instruction.h"
#include "CFG.h"
#include "Expression.h"

class Affectation : public Instruction
{
public:
	Affectation(std::string symbolIdent, Expression* exprAffected);
	~Affectation();

	std::string buildIR(CFG* cfg);

private:
	std::string symbolIdent;
	Expression* exprAffected;
};
