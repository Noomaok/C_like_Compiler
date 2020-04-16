#pragma once

#include "Core.h"
#include "Function.h"
#include "BasicBlock.h"
#include "IRVariable.h"

class CFG
{
public:
	CFG(Function* ast);
	~CFG();

	BasicBlock* genPrologue();
	BasicBlock* genEpilogue();

	std::string newBBName();
	void addBasicBlock(BasicBlock* newBB);

	std::string createNewTempVar(Type type);
	IRVariable* getVariable(std::string varName);

	void gen_asm(std::ostream &o);

	BasicBlock* currentBB;
	BasicBlock* epilogueBB;
private:
	int getOffsetBaseOnType(Type type);

	Function* ast;
	std::vector<BasicBlock*> allBBs;
	int sizeAllocated;

	int nextFreeSymbolIndex;
	int nextBBNumber;
	int nextTempVarNumber;
	std::map<std::string, IRVariable*> symbolTable;
};