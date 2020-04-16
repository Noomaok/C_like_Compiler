#include "ReturnInstr.h"

ReturnInstr::ReturnInstr(Expression* exprReturned)
: exprReturned(exprReturned)
{}

ReturnInstr::~ReturnInstr()
{
	delete exprReturned;
}

std::string ReturnInstr::buildIR(CFG* cfg)
{
	exprReturned->buildIR(cfg);
	return "";
}