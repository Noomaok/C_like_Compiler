#pragma once

#include "Core.h"
#include "Expression.h"

class Variable : public Expression
{
public:
	Variable(Type type, TypeVar typeVar, std::string value);
	~Variable();

	std::string buildIR(CFG* cfg) override;

private:
	Type type;
	TypeVar typeVar;
	std::string value;
};