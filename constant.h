#ifndef CONSTANT_H
#define CONSTANT_H

#define _USE_MATH_DEFINES // for C++
#include <math.h>

const char* piNames[] = { "pi", "PI", "Pi", NULL };
const char* eNames[]	= { "e", "E", NULL };

const char** arrConstNames[] = {
	piNames, 
	eNames,
	NULL
};

const double arrConst[] = {
	M_PI,
	M_E,
	NULL
};

#endif