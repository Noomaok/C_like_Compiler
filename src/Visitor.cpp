#include "Visitor.h"

antlrcpp::Any Visitor::visitAxiom(ccompParser::AxiomContext *ctx) 
{
	Program* program = new Program();

	//global variable handle here

	for(int i = 0; i < ctx->function_definition().size(); i++) {
		Function* function = (Function*) visit(ctx->function_definition().at(i));
		program->addFunction(function);
	}

	program->symbolTable = symbolTable;

	return program;
}

antlrcpp::Any Visitor::visitFunction_definition(ccompParser::Function_definitionContext *ctx) 
{
	std::string name = ctx->NAME()->getText();
	Type returnType = getTypeFromString(ctx->TYPE()->getText());

	Function* function = new Function(name, returnType);

	for(int i = 0; i < ctx->instruction().size(); i++) {
		Instruction* instr = (Instruction*) visit(ctx->instruction().at(i));
		function->addInstructions(instr);
	}
	
	return function;
}

antlrcpp::Any Visitor::visitReturn(ccompParser::ReturnContext *ctx)
{
	Expression* returnExpresion = (Expression*) visit(ctx->expr());
	ReturnInstr* rInstr = new ReturnInstr(returnExpresion);
	return (Instruction*) rInstr;
}

antlrcpp::Any Visitor::visitConstant(ccompParser::ConstantContext *ctx)
{
	std::string constValue = ctx->CONST()->getText();
	Symbol* symbolConst = new Symbol("const_"+ constValue, constValue, SymbolType::VARIABLE, ContentType::CONST);
	symbolTable.insert(std::make_pair("const_"+ constValue, symbolConst));
	return (Expression*) symbolConst;
}

antlrcpp::Any Visitor::visitDeclaration(ccompParser::DeclarationContext *ctx)
{

}

antlrcpp::Any Visitor::visitAffectation(ccompParser::AffectationContext *ctx)
{

}