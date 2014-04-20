#ifndef VALUE_H
#define VALUE_H
//-----------------------------------------------------------------------------

#include <iostream>
#include <math.h>

#include "unary.h"
#include "binary.h"
#include "function.h"

#define M_PI_2     1.57079632679489661923

enum ttype{
	END,
	UN_OPERATOR,
	BIN_OPERATOR,
	NUMBER,
	LBRACKET,
	RBRACKET,
	FUNCTION
};


//================================================================================
struct Value
{
	ttype type;
	int index;
	union {
		double number;
		Binary binary;
		Unary unary;
		Function function;
	};
	Value(){}
	
	Value (double val2num) : type(NUMBER), number(val2num){}; 
	
	Value(const Value &val2): type (val2.type) 
	{	
		if (val2.type == NUMBER) number = val2.number;
		else {
			index = val2.index;
			if (val2.type == UN_OPERATOR) unary = val2.unary;
			else if (val2.type == BIN_OPERATOR) binary = val2.binary;	
			else if (val2.type == FUNCTION) function = val2.function;	
		}
	}
};

#endif