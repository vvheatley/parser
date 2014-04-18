
#ifndef UNARY_H
#define UNARY_H
//-----------------------------------------------------------------------------


struct Unary
{
	double (*pFunc) (double);
	bool isPrefix;
	int precedence;
	int index;
};

char* negNames[] = { "-",  NULL };
char* posNames[] = { "+", NULL };

char** arrUnaryNames[] = {
	negNames,
	posNames,
	NULL
};

double neg (double op) { return -op; }
double pos (double op) { return -op; }

const Unary arrUnary[] = {
	{ neg, true, 1, 0},
	{ pos, true, 1, 1 },

};
const int unaryCount = sizeof(arrUnary) / sizeof(arrUnary[0]);

#endif