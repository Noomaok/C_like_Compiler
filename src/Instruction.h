#pragma once

#include "Core.h"

class CFG;

class Instruction
{
public:
	Instruction();
	virtual ~Instruction();

	virtual std::string buildIR(CFG* cfg) = 0;
};