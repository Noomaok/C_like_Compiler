#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ccompLexer.h"
#include "antlr4-generated/ccompParser.h"
#include "antlr4-generated/ccompBaseVisitor.h"
#include "Visitor.h"
#include "Program.h"
#include "ParserErrorListener.h"

int main(int argn, const char **argv) 
{
	std::stringstream in;
	if (argn==2) 
	{
		std::ifstream lecture(argv[1]);
		in << lecture.rdbuf();
	}
	
	antlr4::ANTLRInputStream input(in.str());
	ccompLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);
	ccompParser parser(&tokens);

	//Add listener for error detection
	parser.removeErrorListeners();
	ParserErrorListener errorListener;
	parser.addErrorListener(&errorListener);
	
	try 
	{
		antlr4::tree::ParseTree* tree = parser.axiom();

		Visitor visitor;
		Program* program = (Program*) visitor.visit(tree);

		std::vector<CFG*> listeCFG;

		for(auto pFunction : program->getAllFunctions()) {
			CFG *newCfg = new CFG(pFunction, program->symbolTable);
			listeCFG.push_back(newCfg);
		}

		//Generate asembly in the correct output stream
		for(auto pCFG : listeCFG) {
			pCFG->gen_asm(std::cout);
		}
	}
	catch (std::invalid_argument e) 
	{
		std::cout << "Error during file parsing" << std::endl;
		std::cout << e.what() << std::endl;
		return -1;
    }

	return 0;
}
