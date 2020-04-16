#include "CFG.h"

CFG::CFG(Function* ast)
: ast(ast), nextBBNumber(0)
{
	//initTableIRVar
	BasicBlock* prologue = genPrologue();
	addBasicBlock(prologue);
	BasicBlock* base = new BasicBlock(newBBName());
	addBasicBlock(base);
	BasicBlock* epilogue = genEpilogue();
	addBasicBlock(epilogue);

	prologue->exit_true = base;
	base->exit_true = epilogue;

	currentBB = base;
	epilogueBB = epilogue;

	for(Instruction* instrPTR : ast->getInstructions())
	{
		instrPTR->buildIR(this);
	}
}

CFG::~CFG()
{
	delete ast;
}

BasicBlock* CFG::genPrologue() 
{
	BasicBlock* prologue = new BasicBlock(ast->getName());

	std::vector<std::string> params;
	params.push_back("%rbp");
	prologue->addIRInstr(Operation::push, params, OpSize::_64);

	std::vector<std::string> params2;
	params2.push_back("%rsp");
	params2.push_back("%rbp");
	prologue->addIRInstr(Operation::move, params2, OpSize::_64);

	return prologue;
}

BasicBlock* CFG::genEpilogue()
{
	BasicBlock* epilogue = new BasicBlock("end"+ast->getName());

	std::vector<std::string> params;
	params.push_back("%rbp");
	epilogue->addIRInstr(Operation::pop, params, OpSize::_64);

	epilogue->addIRInstr(Operation::leave, params, OpSize::_64);

	return epilogue;
}

std::string CFG::newBBName()
{
	std::string name(ast->getName() + "_BB" + std::to_string(nextBBNumber));
	nextBBNumber++;
	return name;
}

void CFG::addBasicBlock(BasicBlock* newBB)
{
	allBBs.push_back(newBB);
}

std::string CFG::createNewTempVar(Type type)
{

}

IRVariable* CFG::getVariable(std::string varName)
{

}

void CFG::gen_asm(std::ostream &o)
{
	o << "\t.globl " + ast->getName() << std::endl;
	o << "\t.type	" + ast->getName() + ",@function" << std::endl;
	for(BasicBlock* bbPTR : allBBs)
	{
		bbPTR->gen_asm(o);
	}
}