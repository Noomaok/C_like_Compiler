#include "Visitor.h"

antlrcpp::Any Visitor::visitAxiom(ccompParser::AxiomContext *ctx) 
{
	Program* program = new Program();

	//global variable handle here

	for(int i = 0; i < ctx->function_definition().size(); i++) {
		Function* function = (Function*) visit(ctx->function_definition().at(i));
		program->addFunction(function);
	}

	return program;
}

antlrcpp::Any Visitor::visitFunction_definition(ccompParser::Function_definitionContext *ctx) 
{
	std::string name = ctx->NAME()->getText();
	Type returnType = getTypeFromString(ctx->TYPE()->getText());

	Function* function = new Function(name, returnType);

	std::string constValue = ctx->CONST()->getText();
	Variable* varConst = new Variable(Type::int32, TypeVar::INTEGER, constValue);
	ReturnInstr* rInstr = new ReturnInstr(varConst);
	function->addInstructions(rInstr);

	return function;
}