#include "IRInstr.h"

IRInstr::IRInstr(BasicBlock* bbParent, Operation op, std::vector<std::string> params, OpSize opSize)
: bbParent(bbParent), op(op), params(params)
{
	switch (opSize)
	{
	case OpSize::_8:
		regExt = "";
		cmdExt = "";
		break;
	
	case OpSize::_32:
		regExt = "e";
		cmdExt = "l";
		break;

	case OpSize::_64:
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
	case Operation::move:
		o << "\tmov"+ cmdExt + " " + params.at(0) + ", " + params.at(1) << std::endl;
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

	case Operation::load_const:
		o << "\tmov"+ cmdExt +" $"+ params.at(0) +", %"+regExt+"ax" << std::endl;
		break;
	
	default:
		break;
	}
}