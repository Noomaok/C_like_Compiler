#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock* bbParent, Operation op, std::vector<std::string> params, SymbolSize opSize)
: bbParent(bbParent), op(op), params(params)
{
	switch (opSize)
	{
	case SymbolSize::_8:
		regExt = "";
		cmdExt = "";
		break;
	
	case SymbolSize::_32:
		regExt = "e";
		cmdExt = "l";
		break;

	case SymbolSize::_64:
		regExt = "r";
		cmdExt = "q";
		break;
	
	default:
		break;
	}
}

IRInstr::~IRInstr()
{}

void IRInstr::gen_asm(std::ostream &o)
{
	switch (op)
	{
	case Operation::copy:
		o << "\tmov"+ cmdExt + " " + params.at(0) + ", " + params.at(1) << std::endl;
		break;

	case Operation::copy_ret_reg:
		o << "\tmov"+ cmdExt + " " + params.at(0) + ", %" + regExt + "ax" << std::endl;
		break;

	case Operation::push:
		o << "\tpush"+ cmdExt + " " + params.at(0) << std::endl;
		break;

	case Operation::pop:
		o << "\tpop"+ cmdExt + " " + params.at(0) << std::endl;
		break;

	case Operation::leave:
		o << "\tret" << std::endl;
		break;
	
	default:
		break;
	}
}