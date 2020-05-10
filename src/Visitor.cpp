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
		if(instr != nullptr) function->addInstructions(instr);
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
	std::string type = ctx->TYPE()->getText();
	SymbolSize sSize;
	if(strcmp(type.c_str(), "int32_t") == 0) sSize = SymbolSize::_32;
	else if(strcmp(type.c_str(), "int64_t") == 0) sSize = SymbolSize::_64;

	std::vector<Symbol*> symbolsDeclared;
	for(int i = 0; i < ctx->NAME().size(); i++)
	{
		std::string varName = ctx->NAME().at(i)->getText();
		Symbol* symbolVar = new Symbol(varName, varName, SymbolType::VARIABLE, ContentType::NAME);
		symbolVar->setSymbolSize(sSize);
		symbolTable.insert(std::make_pair(varName, symbolVar));
		symbolsDeclared.push_back(symbolVar);
	}

	return (Instruction*) new Declaration(symbolsDeclared, sSize);
}

antlrcpp::Any Visitor::visitAffectation(ccompParser::AffectationContext *ctx)
{
	std::string varIdent = ctx->NAME()->getText();
	Expression* expr = (Expression*) visit(ctx->expr());
	return (Instruction*) new Affectation(varIdent, expr);
}

antlrcpp::Any Visitor::visitVariable(ccompParser::VariableContext *ctx)
{
	std::string varIdent = ctx->NAME()->getText();
	Symbol* varSymbol = symbolTable.at(varIdent);
	return (Expression*) varSymbol;
}

antlrcpp::Any Visitor::visitDeclareAndAffec(ccompParser::DeclareAndAffecContext *ctx)
{
	std::string type = ctx->TYPE()->getText();
	SymbolSize sSize;
	if(strcmp(type.c_str(), "int32_t") == 0) sSize = SymbolSize::_32;
	else if(strcmp(type.c_str(), "int64_t") == 0) sSize = SymbolSize::_64;

	std::string varName = ctx->NAME()->getText();
	Symbol* symbolVar = new Symbol(varName, varName, SymbolType::VARIABLE, ContentType::NAME);
	symbolVar->setSymbolSize(sSize);
	symbolTable.insert(std::make_pair(varName, symbolVar));
	Expression* varExpr = (Expression*) visit(ctx->expr());

	return (Instruction*) new Affectation(varName, varExpr);
}