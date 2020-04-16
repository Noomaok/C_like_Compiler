#include "Variable.h"

Variable::Variable(Type type, TypeVar typeVar, std::string value)
: type(type), typeVar(typeVar), value(value)
{}

Variable::~Variable()
{}

std::string Variable::buildIR(CFG* cfg) 
{
	if(typeVar == TypeVar::INTEGER) {
		std::vector<std::string> params;
		params.push_back(value);
		cfg->currentBB->addIRInstr(Operation::load_const, params, OpSize::_32);
	}
	return value;
}