#include "Symbol.h"

Symbol::Symbol(std::string ident, std::string content, SymbolType sType, ContentType cType)
: ident(ident), content(content), sType(sType), cType(cType)
{
	if(cType == ContentType::CONST)
	{
		try
		{
			std::stoi(content);
			sSize = SymbolSize::_32;
		}
		catch (std::out_of_range e) 
		{
			sSize = SymbolSize::_64;
		}
	}
}

Symbol::~Symbol()
{}

std::string Symbol::buildIR(CFG* cfg)
{
	return ident;
}