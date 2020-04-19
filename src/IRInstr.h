#pragma once

#include "Core.h"

class BasicBlock;

class IRInstr
{
public:
	IRInstr(BasicBlock* bbParent, Operation op, std::vector<std::string> params, SymbolSize opSize);
	~IRInstr();

	void gen_asm(std::ostream &o);

private:
	BasicBlock* bbParent;
	Operation op;
	std::string regExt;
	std::string cmdExt;
	std::vector<std::string> params;
};