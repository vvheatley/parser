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
	union{
		double number;
		Binary binary;
		Unary unary;
		Function function;
	};
	Value(){}
	Value(const Value &val2): type (val2.type) {
		if (val2.type == NUMBER) number = val2.number;
		else if (val2.type == BIN_OPERATOR) binary = val2.binary;
		else if (val2.type == FUNCTION) function = val2.function;
	}
};


#endif