#pragma once

#include "Core.h"
#include "CFG.h"

class Expression
{
public:
	Expression();
	virtual ~Expression();

	virtual std::string buildIR(CFG* cfg) = 0;
};