
#ifndef UNARY_H
#define UNARY_H
//-----------------------------------------------------------------------------
struct Unary
{
	double (*pFunc) (double);
	//int precedence;
	//int index;
};
//-----------------------------------------------------------------------------
char* negNames[]  = { "-","minus", NULL };
char* posNames[]  = { "+", "plus", NULL };
char* factNames[] = { "!", NULL };

double neg (double op)	{ return -op;	}
double pos (double op)	{ return op;	}
double fact(double op)	{ return tgamma(op+1);	}
//--------------
char** arrPrefixUnaryNames[] = {
	negNames,
	posNames,
	NULL
};
const int prefixUnaryCnt = sizeof(arrPrefixUnaryNames) / sizeof(Unary) - 1;
//--------------
char** arrPostfixUnaryNames[] = {
	factNames,
	NULL

};

const int unaryCnt = prefixUnaryCnt + sizeof(arrPostfixUnaryNames) / sizeof(Unary) - 1;
//-----------------------------------------------------------------
const Unary arrUnary[unaryCnt] = {
	{ neg	},
	{ pos	},
	{ fact	}

};
int unPrecedence[unaryCnt] = {
	2,
	2,
	4
};

bool isPrefix[unaryCnt] = {
	true,
	true,
	false
};
#endif