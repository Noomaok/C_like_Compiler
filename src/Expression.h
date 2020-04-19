#pragma once

#include "Core.h"

class CFG;

class Expression
{
public:
	Expression();
	virtual ~Expression();

	virtual std::string buildIR(CFG* cfg) = 0;
};