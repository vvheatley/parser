#ifndef VALUE_H
#define VALUE_H
//-----------------------------------------------------------------------------

#include <iostream>
#include <math.h>

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
		Function function;
	};
};
#endif