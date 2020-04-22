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
	void setSymbolSize(SymbolSize newSSize) { sSize = newSSize; };
	ContentType getContentType() { return cType; };

	void setOffset(int offset) { this->offset = offset; };
	int getOffset() { return offset; };

private:
	std::string ident;
	std::string content;
	SymbolType sType;
	ContentType cType;
	SymbolSize sSize;
	int offset;
};