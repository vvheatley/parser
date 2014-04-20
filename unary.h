
#ifndef UNARY_H
#define UNARY_H
//-----------------------------------------------------------------------------
struct Unary
{
	double (*pFunc) (double);
	//int precedence;
	//int index;
};

char* negNames[] = { "-",  NULL };
char* posNames[] = { "+", NULL };

char** arrUnaryNames[] = {
	negNames,
	posNames,
	NULL
};

double neg (double op) { return -op; }
double pos (double op) { return op; }

bool isPrefix[] = {
	true,
	true
};
int unPrecedence[] = {
	0,
	0
};
const Unary arrUnary[] = {
	{ neg },
	{ pos },

};


const int unaryCount = sizeof(arrUnary) / sizeof(arrUnary[0]);

#endif