#include <iostream>
#include <math.h>

#define M_PI_2     1.57079632679489661923

using namespace std;

enum ttype{
	END,
	UN_OPERATOR,
	BIN_OPERATOR,
	NUMBER,
	LBRACKET,
	RBRACKET,
	FUNCTION
};

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
	 bool isLeftAssoc;
	 int precedence;
};

char* addNames[] = { "+", "plus",	NULL };
char* subNames[] = { "-", "minus",	NULL };
char* mltNames[] = { "*", "mult",	NULL };
char* divNames[] = { "/", "divide", NULL };
char* powNames[] = { "^", "**",		NULL };

char** arrBinaryNames[] = {
	addNames,
	subNames,
	mltNames,
	divNames,
	powNames,
	NULL
};

double add (double op1, double op2) { return op1 + op2; } 
double sub (double op1, double op2) { return op1 - op2; }
double div (double op1, double op2) { return op2==0 ? 0 : op1 / op2; }
double mlt (double op1, double op2) { return op1 * op2; }

const Binary arrBinary[] = {
	{ add,	true,	1 },
	{ sub,	true,	1 },
	{ mlt,	true,	2 },
	{ div,	true,	2 },
	{ pow,	false,	3 }
};
const int binaryCount = sizeof(arrBinary) / sizeof(arrBinary[0]);
//================================================================================
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
	double (*foo) (double);

};

double cot (double x) { return tan(3.1415/2 - x);}

Function arrFunction[] = {
	{1, sin },
	{1, cos },
	{1, tan },
	{1, cot }
};
//====================================================================================
struct Value
{
	ttype type;
	union{
		double number;
		Binary binary;
		Function function;
	};
};

const char delim[] = "+-*/^()";
const char garantedDelim[] = " ()\0";

inline int isGarantedDelim (char *chFirst)
{
	for (int i = 0; garantedDelim[i] != '\0'; ++i){
		if (*chFirst == garantedDelim[i]) return i;
	}
	return -1;
}
//------------------------------------------------------------------------------------
inline bool isDelim (char *chFirst)
{
	for (int i = 0; delim[i] != '\0'; ++i){
		if (*chFirst == delim[i]) return true;
	}
	return false;
}
//------------------------------------------------------------------------------------
/*inline int isBinary(char* chFirst, char* chLast)
{
	int binIndex = 0;

	for (; binIndex < binaryCount; ++binIndex){
		char** nameArr = arrBinaryNames[binIndex];
		char* chExample, *chToken;

		while (nameArr){					//����� ����
			chExample = *nameArr; //������ ������ ������
			chToken = chFirst;

			while (chExample && chToken < chLast){
				if (*chExample != *chToken) break; 
				++chExample; ++chToken;
			}
			if (chExample && chToken == chLast) return binIndex;

			++nameArr;
		}
	} //end for
	return -1;
}
*/
//------------------------------------------------------------------------------
inline int findName(char* chFirst, char* chLast, char*** arrExampleNames)
{
	int index = 0;

	char* chExample;
	char* chToken;
	char** arrNames;

	while (arrExampleNames[index]){
		arrNames = arrExampleNames [index];

		while (*arrNames){					//����� ����
			chExample = *arrNames; //������ ������ ������
			chToken = chFirst;

			while (chExample && chToken < chLast){
				if (*chExample != *chToken) break;
				++chExample; ++chToken;
			}
			if (chExample && chToken == chLast) return index;

			++arrNames;
		}
		++index;
	} //end while
	return -1;
}
//---------------------------------------------------------------------------------
inline bool isDouble (char* chFirst, char* chLast){
	int dots = 0;
	//int i = 0;
	chLast--;
	char* ch = chFirst;

	if (*chFirst == '+' || *chFirst == '-')	++ch;
	//int check = i;
	char* check = ch;

	for (; ch < chLast; ++ch){
		if (*ch == 'e' || *ch == 'E') break;
		if (*ch == '.' || *ch == ',') ++dots;
		else if (!isdigit(*ch)) return false;
	}

	if (dots > 1 || ch - check < 2) return false;

	if (ch == chLast)       return true;
	//++i;
	++ch;
	if (*ch == '-' || *ch == '+') ++ch;

	for (; ch < chLast; ++ch){
		if (!isdigit(*ch)) return false;
	}
	return true;
}
//------------------------------------------------------------------------------
Value ntokenizer(char *&token, char *expr, int &pos)
{
	Value retValue;
	//delete token;
	char *chFirst = expr + pos;

	while (*chFirst == ' '){ //spaces
		chFirst++;
		pos++;
	}
	if (*chFirst == '\0') {
		token = NULL;
		retValue.type = END;
		return retValue;
	}

	if (*chFirst == '(')	retValue.type = LBRACKET;
	else if (*chFirst == ')')	retValue.type = RBRACKET;

	char* chLast = chFirst;

	while (isGarantedDelim(chLast) == -1) ++chLast;

	while (chLast > chFirst){
		int index;

		//if isBinary {retValue.ttype = bin; retValue.Binary = Binary[i] }	
		if (index = findName(chFirst, chLast, arrBinaryNames) >= 0) {
			retValue.type = BIN_OPERATOR;
			retValue.binary = arrBinary[index];
		}

		//if is Function { retValue.ttype = FUNCTION; retValue.Function = function[i]}
		if (index = findName(chFirst, chLast, arrFunctionNames) >= 0){
			retValue.type = FUNCTION;
			retValue.function = arrFunction[index];
		}

		//if is double { retValue.ttype = NUMBER; retValue.number = atoi (token); }
		if (isDouble(chFirst, chLast)) {
			retValue.type = NUMBER;
			retValue.number = atoi(token);
		}
		--chLast;
	}

	return retValue;
}
	/*
	if (int firstSymbType = isGarantedDelim(chFirst) >= 0) {
		char * chLast = chFirst;
		for (; *chLast != '\0'; ++chLast) if ('0' <= *chLast <= '9' || 'a' <= *chLast <= 'z' || 'A' <= *chLast <= 'Z') break;
		if (chLast - chFirst == 1){

			token = new char[2];
			token[0] = *chFirst;
			token[1] = '\0';
			++pos;
			if (firstSymbType < 4) {
				retValue.type = BIN_OPERATOR;  return Value(BIN_OPERATOR, arrBinary[i])
			}

			switch (*chFirst){
				case '(': retValue.type = LBRACKET; break;
				case ')': retValue.type = RBRACKET; break;
				default:  retValue.type = BIN_OPERATOR;
			}
			return retValue;
		}
		else{
			token = new char[chLast-chFirst];
		
		}
	}

	chFirst++;
	while (*chFirst != '\0' && *chFirst != ' ' && !isDelim(chFirst)){
		chFirst++;
	}
	int size = chFirst - expr - pos + 1;
	token = new char[size];
	memcpy(token, expr + pos, size - 1);
	token[size - 1] = '\0';
	pos = chFirst - expr;
	return NUMBER;
}
*/
//ttype tokenizer (char *&token, char *expr, int &pos)
//{
//	//delete token;
//	char *chFirst = expr + pos;
//
//	while(*chFirst == ' '){
//		chFirst++;
//		pos++;
//	}	
//	if (*chFirst == '\0') {
//		token = NULL;
//		return END;
//	}
//
//	if (isDelim(chFirst)) {
//		token = new char [2];
//		token[0] = *chFirst;
//		token[1] = '\0';
//		++pos;
//		switch (*chFirst){
//			case '(': return LBRACKET;
//			case ')': return RBRACKET;
//			default : return BIN_OPERATOR;
//		}
//	}
//
//	chFirst++;
//	while(*chFirst != '\0' && *chFirst != ' ' && !isDelim(chFirst)){
//		chFirst++;
//	}
//	int size = chFirst - expr - pos + 1;
//	token = new char [size];
//	memcpy(token, expr+pos, size-1);
//	token[size-1] = '\0';
//	pos = chFirst-expr;
//	return NUMBER;
//}

//int priority(char op)
//{
//	switch (op){
//		case '+':case'-':	return 0;
//		case '*':case'/':	return 1;
//		case '^'		:	return 2;
//	}
//}
//ttype valType(char token)
//{
//	switch (token){
//		case '(':return LBRACKET;
//		case ')':return RBRACKET;
//		case '+': case'-': case'*':case'/':case'^': return BIN_OPERATOR;
//		default :return NUMBER;
//	}
//}

//bool isRightAssociated(char operation)
//{
//	switch (operation){
//		case '^': return true;
//	}
//	return false;
//}

//template <size_t size>
//void calcQueueHead(double(&queue)[size], int &head, char op)
//{
//	switch (op){
//		case '+':	queue[head - 1] += queue[head]; break;
//		case '-':	queue[head - 1] -= queue[head]; break;
//		case '*':	queue[head - 1] *= queue[head]; break;
//		case '/':	queue[head - 1] /= queue[head]; break;
//		case '^':	queue[head - 1] =  pow (queue[head-1], queue[head]) ; break;
//	}
//	--head;
//}

void main()
{
	char* expr = "0123+cot-893";
	char* chFirst = expr + 5;
	char* chLast = expr + 8;
	
	int index;
	if ((index = findName(chFirst, chLast, arrBinaryNames)) != -1) cout << "binary" << index;

	else if ((index = findName(chFirst, chLast, arrFunctionNames)) != -1) cout << "function " << index<< " " <<arrFunctionNames[index][0];
	else if (isDouble(chFirst, chLast)) cout << "double " << atoi(chFirst);
	else cout << "undef";
	/*
	double outQueue[100];
	char stack[200], *inputStack[200];
	int opTop = -1, inpTop = 0, head = -1;

	double res = 0;
	char input[200];

	cin.getline(input, 200);

	char  *token = NULL, *prevToken = "(";
	bool unary = true;
	ttype type;
	int n = 0;

	while ((type = tokenizer (token, input, n)) != END){

		if (type == NUMBER) {
			outQueue[++head] = atof(token);
			if (unary)
				switch (*prevToken){
					case '-': outQueue[head] = -outQueue[head]; break;
				}
			cout << outQueue[head] << " ";

			unary = true;

		}//end if NUMBER

		else if (type == BIN_OPERATOR){
			if (valType(prevToken[0]) == NUMBER || valType(prevToken[0]) == RBRACKET){
				while (opTop >= 0 && valType(stack[opTop]) == BIN_OPERATOR){
					if (isRightAssociated(token[0])) {
						if (priority(token[0]) >= priority(stack[opTop])) break;
					}
					else if (priority(token[0]) > priority(stack[opTop])) break;

					calcQueueHead(outQueue, head, stack[opTop]);
					cout << stack[opTop--] << " ";
				}
				stack[++opTop] = token[0];

				unary = false;
			}
			else {
				unary = true;

			}
		} //end if BIN_OPERATOR

		else if (type == LBRACKET) {
			stack[++opTop] = token[0]; 
			unary = true;
		}

		else if (type == RBRACKET) {
			while (valType(stack[opTop]) != LBRACKET){
				calcQueueHead(outQueue, head, stack[opTop]);
				cout << stack[opTop--] << " ";
			}
			if (opTop >= 0) opTop--;
			else { cout << "\nError";opTop = -1; cin.get(); exit(1); }

			unary = false;
		}

		prevToken = token;	
	} // end while tokenizer

	while (opTop >= 0){
		if (valType(stack[opTop]) != BIN_OPERATOR) { cout << "\nError"; cin.get(); exit(1); }

		calcQueueHead(outQueue, head, stack[opTop]);

		cout << stack[opTop--] << " ";
	}
	cout << "\nresult: " << outQueue[0];
	*/
	cin.get();
}