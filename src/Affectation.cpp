#include "Affectation.h"

Affectation::Affectation(std::string symbolIdent, Expression* exprAffected)
: symbolIdent(symbolIdent), exprAffected(exprAffected)
{
}

Affectation::~Affectation()
{
	delete exprAffected;
}

std::string Affectation::buildIR(CFG* cfg)
{
	Symbol* varSymbol = cfg->getSymbol(symbolIdent);
	std::string exprIdent = exprAffected->buildIR(cfg);
	Symbol* exprSymbol = cfg->getSymbol(exprIdent);

	std::vector<std::string> params;
	if(exprSymbol->getContentType() == ContentType::CONST) 
	{
		params.push_back(exprSymbol->getContent());
		params.push_back(std::to_string(varSymbol->getOffset()));
		cfg->currentBB->addIRInstr(Operation::copy_const_to_var, params, varSymbol->getSymbolSize());
	}
	else 
	{
		params.push_back(std::to_string(exprSymbol->getOffset()));
		params.push_back(std::to_string(varSymbol->getOffset()));
		cfg->currentBB->addIRInstr(Operation::copy_var_to_var, params, varSymbol->getSymbolSize());
	}

	return symbolIdent;
}