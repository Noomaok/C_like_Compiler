#pragma once

#include "Core.h"
#include "Expression.h"

class Symbol : public Expression
{
public:
	Symbol(std::string ident, std::string content, SymbolType sType, ContentType cType);
	~Symbol();

	std::string buildIR(CFG* cfg);

	std::string getContent() { return content; };
	SymbolType getSymbolType() { return sType; };
	SymbolSize getSymbolSize() { return sSize; };
	ContentType getContentType() { return cType; };

private:
	std::string ident;
	std::string content;
	SymbolType sType;
	ContentType cType;
	SymbolSize sSize;
};