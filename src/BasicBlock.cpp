#include "BasicBlock.h"

BasicBlock::BasicBlock(std::string label)
: label(label)
{}

BasicBlock::~BasicBlock()
{
	for(IRInstr* irInstrPTR : instrs)
	{
		delete  irInstrPTR;
	}
}

void BasicBlock::addIRInstr(Operation op, std::vector<std::string> params, OpSize opSize)
{
	instrs.push_back(new IRInstr(this, op, params, opSize));
}

void BasicBlock::gen_asm(std::ostream &o)
{
	o << label + ":" << std::endl;
	for(IRInstr* irInstrPTR : instrs)
	{
		irInstrPTR->gen_asm(o);
	}

	//handle jump here
}