#include <iostream>
#include <math.h>

#include "value.h"
#include "tree.h"

using namespace std;

const char delim[] = "+-*/^()";
const char garantedDelim[] = " ()\0";

inline int isGarantedDelim (char *chFirst)
{
	for (int i = 0; garantedDelim[i] != '\0'; ++i){
		if (*chFirst == garantedDelim[i] || *chFirst == '\0') return i;
	}
	return -1;
}
//------------------------------------------------------------------------------------
inline bool isDelim (char *chFirst)
{
	for (int i = 0; delim[i] != '\0'; ++i){
		if (*chFirst == delim[i] || *chFirst == '\0') return true;
	}
	return false;
}
//------------------------------------------------------------------------------------
//------------------------------------------------------------------------------
inline int findName(char* chFirst, char* chLast, char*** arrExampleNames)
{
	int index = 0;

	char* chExample;
	char* chToken;
	char** arrNames;

	while (arrExampleNames[index]){
		arrNames = arrExampleNames [index];

		while (*arrNames){					//масив імен
			chExample = *arrNames; //перший символ зразку
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
	int size1 = 0; //до крапки
	int size2 = 0; //після крапки

	char* ch = chFirst;

	//if (*ch == '+' || *ch == '-') ++ch;

	while (true){
		if (ch == chLast) return size1 ? true : false;
		if (*ch == 'e' || *ch == 'E') break;
		if (*ch == '.' || *ch == ',') {++ch; break; }
		if (!isdigit(*ch)) return false;

		++size1;
		++ch;
	}//end while(true)

	while (true){
		if (ch == chLast) return size1 || size2 ? true : false;
		if (*ch == 'e' || *ch == 'E') { if (!size1 && !size2) return false; }
		if (!isdigit(*ch)) return false;

		++size2;
		++ch;
	}

	if (*ch == '-' || *ch == '+') ++ch;

	for (; ch != chLast; ++ch){
		if (!isdigit(*ch)) return false;
	}

	return true;
}
//------------------------------------------------------------------------------
Value ntokenizer( char *expr, int &pos)
{
	Value retValue;
	//delete token;

	char *chFirst = expr + pos;

	while (*chFirst == ' '){ //spaces
		chFirst++;
		//pos++;
	}
	if (*chFirst == '\0') {
		retValue.type = END;
		++pos;
		return retValue;
	}

	if (*chFirst == '(')	retValue.type = LBRACKET;
	else if (*chFirst == ')')	retValue.type = RBRACKET;

	char* chLast = chFirst + 1; //наступний символ після останнього символа токена

	while (isGarantedDelim(chLast) == -1) ++chLast;

	while (chLast > chFirst){
		int index;

		//if is double { retValue.ttype = NUMBER; retValue.number = atoi (token); }
		if (isDouble(chFirst, chLast)) {
			retValue.type = NUMBER;
			retValue.number = atoi(chFirst);
			break;
		}

		//if isBinary {retValue.ttype = bin; retValue.Binary = Binary[i] }	
		else if ((index = findName(chFirst, chLast, arrBinaryNames)) != -1) {
			retValue.type = BIN_OPERATOR;
			retValue.binary = arrBinary[index];
			retValue.binary.index = index;
			break;
		}

		//if is Function { retValue.ttype = FUNCTION; retValue.Function = function[i]}
		else if ((index = findName(chFirst, chLast, arrFunctionNames)) != -1){
			retValue.type = FUNCTION;
			retValue.function = arrFunction[index];
			retValue.function.index = index;
			break;
		}

		--chLast;
	}
	pos = chLast - expr;
	return retValue;
}


template <size_t size>
void calcQueueHead(double(&queue)[size], int &head, char op)
{
	switch (op){
		case '+':	queue[head - 1] += queue[head]; break;
		case '-':	queue[head - 1] -= queue[head]; break;
		case '*':	queue[head - 1] *= queue[head]; break;
		case '/':	queue[head - 1] /= queue[head]; break;
		case '^':	queue[head - 1] =  pow (queue[head-1], queue[head]) ; break;
	}
	--head;
}

void print(const Value &val)
{
	switch(val.type){
		case NUMBER:		cout << "num"	<< val.number; break;
		case BIN_OPERATOR:	cout << "bin"	<< arrBinaryNames[val.binary.index][0]; break;
		case FUNCTION:		cout << "func"	<<arrFunctionNames[val.function.index][0]; break;
		case END:			cout << "end";
		default:			cout << "undef";
	}
	cout << " ";
}
//------------------------------------------------------------------------------------------
void main()
{
	char* expr = "01+34";
	//char* chFirst = expr + 5;
	//char* chLast = expr + 8;
	//
	//int index;
	//if ((index = findName(chFirst, chLast, arrBinaryNames)) != -1) cout << "binary" << index;
	//else if ((index = findName(chFirst, chLast, arrFunctionNames)) != -1) cout << "function " << index<< " " <<arrFunctionNames[index][0];
	//else if (isDouble(chFirst, chLast)) cout << "double " << atoi(chFirst);
	//else cout << "undef";

	int n = 3;

	Value tok = ntokenizer(expr, n);
	print(tok);
	//if (tok.type == FUNCTION) cout << "function " << tok.function.foo(1);
	//else if (tok.type == BIN_OPERATOR) cout << "bin " << tok.binary.pFunc(2, 3);
	//else if (tok.type == NUMBER) cout << "numb " << tok.number;
	//else if (tok.type == END) cout << "end ";
	//else cout << "undef";

	cout << endl << n;

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

	//Value outQueue[100];
	//Value stack[100];
	//int opTop = -1, head = -1;

	//Value token;

	//char input[300];
	//cin.getline(input, 300);

	//int pos = 0;
	//token = ntokenizer(input, pos);
	//while (token.type != END){
	//	if (token.type == NUMBER){
	//		outQueue[++head] = token;
	//	}

	//	else if (token.type == BIN_OPERATOR){
	//		while (opTop >= 0 && stack[opTop].type == BIN_OPERATOR){
	//			if (token.binary.isLeftAssoc)
	//			{
	//				if (token.binary.precedence > stack[opTop].binary.precedence) break;
	//			}
	//			else if (token.binary.precedence >= stack[opTop].binary.precedence) break;

	//			//calcQueueHead(outQueue, head, stack[opTop]);
	//			print(stack[opTop--]);
	//		}
	//		stack[++opTop] = token;
	//	}

	//	else if (token.type == LBRACKET) {
	//		stack[++opTop] = token;
	//	}
	//	else if (token.type == RBRACKET){
	//		while (stack[opTop].type != LBRACKET){
	//			//calcQueueHead(outQueue, head, stack[opTop]);
	//			print(stack[opTop--]);
	//		}
	//		if (opTop >= 0) opTop--;
	//		else { cout << "\nError"; opTop = -1; cin.get(); exit(1); }

	//	}
	//	token = ntokenizer(input, pos);
	//} //end while

	////--------------
	//while (opTop >= 0){
	//	if (stack[opTop].type != BIN_OPERATOR) { cout << "\nError"; cin.get(); exit(1); }
	//	//calcQueueHead(outQueue, head, stack[opTop]);
	//	print (stack[opTop--]);
	//}

	cin.get();
}