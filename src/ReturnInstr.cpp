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
	std::string identExpr = exprReturned->buildIR(cfg);
	Symbol* symbolExpr = cfg->getSymbol(identExpr);
	std::vector<std::string> params;

	if(symbolExpr->getContentType() == ContentType::CONST) {
		params.push_back("$" + symbolExpr->getContent());
		cfg->currentBB->addIRInstr(Operation::copy_ret_reg, params, symbolExpr->getSymbolSize());
	}

	return "";
}