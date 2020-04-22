#include "Declaration.h"

Declaration::Declaration(std::vector<Symbol*> symbolsDeclared, SymbolSize sSize)
: symbolsDeclared(symbolsDeclared), sSize(sSize)
{
}

Declaration::~Declaration()
{
}

std::string Declaration::buildIR(CFG* cfg) {
	return "";
}