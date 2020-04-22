#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ccompVisitor.h"

#include "Program.h"
#include "Function.h"
#include "Symbol.h"
#include "ReturnInstr.h"
#include "Declaration.h"
#include "Affectation.h"

class Visitor : public ccompVisitor 
{

public:

	virtual antlrcpp::Any visitAxiom(ccompParser::AxiomContext *ctx) override;

	virtual antlrcpp::Any visitFunction_definition(ccompParser::Function_definitionContext *ctx) override;

	virtual antlrcpp::Any visitReturn(ccompParser::ReturnContext *ctx) override;

    virtual antlrcpp::Any visitDeclaration(ccompParser::DeclarationContext *ctx) override;

    virtual antlrcpp::Any visitAffectation(ccompParser::AffectationContext *ctx) override;

    virtual antlrcpp::Any visitConstant(ccompParser::ConstantContext *ctx) override;

	virtual antlrcpp::Any visitVariable(ccompParser::VariableContext *ctx) override;

private:
	std::map<std::string, Symbol*> symbolTable;
};