
#ifndef BINARY_H
#define BINARY_H
//-----------------------------------------------------------------------------
enum binaryIndex{
	ADD,
	SUB,
	MLT,
	DIV,
	POW
};

struct Binary
{
	double (*pFunc) (double, double);
	//bool isLeftAssoc;
	//int precedence;
};

char* addNames[] = { "+", "plus", NULL };
char* subNames[] = { "-", "minus", NULL };
char* mltNames[] = { "*", "mult", NULL };
char* divNames[] = { "/", "divide", NULL };
char* powNames[] = { "^", "**", NULL };

char** arrBinaryNames[] = {
	addNames,
	subNames,
	mltNames,
	divNames,
	powNames,
	NULL
};
bool isLeftAssoc[] = {
	true,
	true,
	true,
	true,
	false
};
int binPrecedence[] = {
	0,
	0,
	1,
	1,
	3
};

double add (double op1, double op2) { return op1 + op2; }
double sub (double op1, double op2) { return op1 - op2; }
double div (double op1, double op2) { return op2 == 0 ? 0 : op1 / op2; }
double mlt (double op1, double op2) { return op1 * op2; }

const Binary arrBinary[] = {
	{ add},
	{ sub },
	{ mlt },
	{ div },
	{ pow }
};
const int binaryCount = sizeof(arrBinary) / sizeof(arrBinary[0]);

#endif