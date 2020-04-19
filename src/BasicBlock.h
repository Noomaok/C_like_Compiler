#pragma once

#include "Core.h"
#include "IRInstr.h"


class BasicBlock
{
public:
	BasicBlock(std::string label);
	~BasicBlock();

	void gen_asm(std::ostream &o);

	void addIRInstr(Operation op, std::vector<std::string> params, SymbolSize opSize);

	BasicBlock* exit_true;
	BasicBlock* exit_false;

private:
	std::string label;
	JumpType jumpType;
	std::vector<IRInstr*> instrs;
};