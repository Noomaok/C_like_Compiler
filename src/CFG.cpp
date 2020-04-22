#include "CFG.h"

CFG::CFG(Function* ast, std::map<std::string, Symbol*> symbolTable)
: ast(ast), nextBBNumber(0), symbolTable(symbolTable)
{
	setSymbolsOffsets();
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
	prologue->addIRInstr(Operation::push, params, SymbolSize::_64);

	std::vector<std::string> params2;
	params2.push_back("%rsp");
	params2.push_back("%rbp");
	prologue->addIRInstr(Operation::copy, params2, SymbolSize::_64);

	return prologue;
}

BasicBlock* CFG::genEpilogue()
{
	BasicBlock* epilogue = new BasicBlock("end"+ast->getName());

	std::vector<std::string> params;
	params.push_back("%rbp");
	epilogue->addIRInstr(Operation::pop, params, SymbolSize::_64);

	epilogue->addIRInstr(Operation::leave, params, SymbolSize::_64);

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

Symbol* CFG::getSymbol(std::string varName)
{
	return symbolTable.at(varName);
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

void CFG::setSymbolsOffsets()
{
	sizeAllocated = 0;
	std::map<std::string, Symbol*>::iterator it;

	for(it = symbolTable.begin(); it != symbolTable.end(); it++) {
		if(it->second->getContentType() != ContentType::CONST) {
			sizeAllocated += getOffsetBaseOnSymbolSize(it->second->getSymbolSize());
			it->second->setOffset(sizeAllocated);
		}
	}
}

int CFG::getOffsetBaseOnSymbolSize(SymbolSize sSize)
{
	int offset;
	switch (sSize)
	{
	case SymbolSize::_8:
		offset = 1;
		break;

	case SymbolSize::_32:
		offset = 4;
		break;

	case SymbolSize::_64:
		offset = 8;
		break;
	
	default:
		break;
	}
	return offset;
}