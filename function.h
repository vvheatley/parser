#ifndef FUNCTION_H
#define FUNCTION_H
//-----------------------------------------------------------------------------

char* sinNames[] = { "sin", NULL };
char* cosNames[] = { "cos", NULL };
char* tanNames[] = { "tg", "tan", NULL };
char* cotNames[] = { "ctg", "cot", NULL };

char** arrFunctionNames[] = {
	sinNames,
	cosNames,
	tanNames,
	cotNames,
	NULL
};
const int functionCount = sizeof(arrFunctionNames) / sizeof(arrFunctionNames[0]);

struct Function
{
	int argsCnt;
	double(*foo) (double);
	int index;

};

double cot(double x) { return tan(3.1415 / 2 - x); }

Function arrFunction[] = {
	{ 1, sin, 0 },
	{ 1, cos, 1 },
	{ 1, tan, 2 },
	{ 1, cot, 3 }
};

#endif