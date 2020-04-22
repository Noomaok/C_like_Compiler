#pragma once

#include "Core.h"
#include "Instruction.h"
#include "Symbol.h"
#include "CFG.h"

class Declaration : public Instruction
{
public:
	Declaration(std::vector<Symbol*> symbolsDeclared, SymbolSize sSize);
	~Declaration();

	std::string buildIR(CFG* cfg);

private:
	SymbolSize sSize;
	std::vector<Symbol*> symbolsDeclared;
};
