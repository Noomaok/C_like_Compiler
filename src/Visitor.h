#pragma once

#include "antlr4-runtime.h"
#include "antlr4-generated/ccompVisitor.h"

class Visitor : public ccompVisitor {

public:

	virtual antlrcpp::Any visitAxiom(ccompParser::AxiomContext *ctx) override {
		return visitChildren(ctx);
	}

	virtual antlrcpp::Any visitProg(ccompParser::ProgContext *ctx) override {

		int retval = stoi(ctx->CONST()->getText());
		std::cout<<".globl	main\n"
			" main: \n"
			" 	movl	$"<<retval<<", %eax\n"
			" 	ret\n";

		return 0;
	}

};