#pragma once

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <cstring>


enum SymbolType { VARIABLE, FUNCTION };
enum ContentType { CONST, CARACTER, NAME };

enum SymbolSize { _8, _32, _64 };
enum Type { int32, int64 };
enum JumpType { JE };

enum Operation
{
	copy,
	copy_ret_reg,
	push,
	pop,
	leave,
	load_const
};

static Type getTypeFromString(std::string str) {
	Type t;
	if(strcmp(str.c_str(), "int32_t") == 0) t = int32;
	else t = int64;

	return t;
}