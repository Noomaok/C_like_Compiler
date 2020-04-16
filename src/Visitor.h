#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ccompVisitor.h"

#include "Program.h"
#include "Function.h"
#include "Variable.h"
#include "ReturnInstr.h"

class Visitor : public ccompVisitor 
{

public:

	virtual antlrcpp::Any visitAxiom(ccompParser::AxiomContext *ctx) override;

	virtual antlrcpp::Any visitFunction_definition(ccompParser::Function_definitionContext *ctx) override;

};