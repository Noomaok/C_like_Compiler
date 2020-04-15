#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>

#include "antlr4-runtime.h"
#include "antlr4-generated/ccompLexer.h"
#include "antlr4-generated/ccompParser.h"
#include "antlr4-generated/ccompBaseVisitor.h"
#include "visitor.h"

int main(int argn, const char **argv) {
	std::stringstream in;
	if (argn==2) {
		std::ifstream lecture(argv[1]);
		in << lecture.rdbuf();
	}
	
	antlr4::ANTLRInputStream input(in.str());
	ccompLexer lexer(&input);
	antlr4::CommonTokenStream tokens(&lexer);

	tokens.fill();

	ccompParser parser(&tokens);
	antlr4::tree::ParseTree* tree = parser.axiom();

	Visitor visitor;
	visitor.visit(tree);

	return 0;
}
