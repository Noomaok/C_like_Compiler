#pragma once

#include "Core.h"
#include "Function.h"
#include "BasicBlock.h"
#include "Symbol.h"

class CFG
{
public:
	CFG(Function* ast, std::map<std::string, Symbol*> symboleTable);
	~CFG();

	BasicBlock* genPrologue();
	BasicBlock* genEpilogue();

	std::string newBBName();
	void addBasicBlock(BasicBlock* newBB);

	std::string createNewTempVar(Type type);
	Symbol* getSymbol(std::string varName);

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
	std::map<std::string, Symbol*> symbolTable;
};