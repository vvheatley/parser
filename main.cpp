#include <iostream>
#include <math.h>

#include "value.h"
#include "tree.h"

using namespace std;

const char garantedDelim[] = " ()\0";

inline int isGarantedDelim (char *chFirst)
{
	for (int i = 0; garantedDelim[i] != '\0'; ++i){
		if (*chFirst == garantedDelim[i] || *chFirst == '\0') return i;
	}
	return -1;
}
//------------------------------------------------------------------------------------
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
		if (*ch == 'e' || *ch == 'E') { 
			if (!size1 && !size2) return false;
			break; 
		}
		if (!isdigit(*ch)) return false;

		++size2;
		++ch;
	}
	++ch;
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

	char* chLast = chFirst + 1;	 //наступний символ після останнього символа токена

	if (*chFirst == '(')	retValue.type = LBRACKET;
	else if (*chFirst == ')')	retValue.type = RBRACKET;
	else {


		while (isGarantedDelim(chLast) == -1) ++chLast;

		while (chLast > chFirst){
			int index;

			//if is double { retValue.ttype = NUMBER; retValue.number = atoi (token); }
			if (isDouble(chFirst, chLast)) {
				retValue.type = NUMBER;
				retValue.number = atof(chFirst);
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
	}
	pos = chLast - expr;
	return retValue;
}


template <size_t size>
void calcQueueHead(Value (&queue)[size], int &head, const Binary &op)
{
	Value result;
	result.type = NUMBER;
	result.number = op.pFunc(queue[head-1].number, queue[head].number);

	queue[head - 1] = result;
	--head;
}

void print(const Value &val)
{
	switch(val.type){
		case NUMBER:		cout << ""	<< val.number; break;
		case UN_OPERATOR:	cout << "un" << arrBinaryNames[val.unary.index][0]; break;
		case BIN_OPERATOR:	cout << arrBinaryNames[val.binary.index][0]; break;
		case FUNCTION:		cout << arrFunctionNames[val.function.index][0]; break;
		case LBRACKET:		cout << "("; break;
		case RBRACKET:		cout << ")"; break;
		case END:			cout << "end"; break;
		default:			cout << "undef";
	}
	cout << " ";
}
//------------------------------------------------------------------------------------------

void main()
{
	//cout << sizeof (Value) << " " << " " << sizeof (ttype) << "\n" << sizeof (double) << " " << sizeof (Binary) << " " << sizeof (Unary) << " " <<  sizeof (Function);

	//char* expr = "2e+3";
	//char* chFirst = expr + 5;
	//char* chLast = expr + 8;
	//
	//int index;
	//if ((index = findName(chFirst, chLast, arrBinaryNames)) != -1) cout << "binary" << index;
	//else if ((index = findName(chFirst, chLast, arrFunctionNames)) != -1) cout << "function " << index<< " " <<arrFunctionNames[index][0];
	//else 
	//if (isDouble(expr, expr + 4))
	//	cout << "double " << atof(expr);
	//else cout << "undef";
	//int n = 3;

	//Value tok = ntokenizer(expr, n);
	//print(tok);
	//if (tok.type == FUNCTION) cout << "function " << tok.function.foo(1);
	//else if (tok.type == BIN_OPERATOR) cout << "bin " << tok.binary.pFunc(2, 3);
	//else if (tok.type == NUMBER) cout << "numb " << tok.number;
	//else if (tok.type == END) cout << "end ";
	//else cout << "undef";
	//cout << endl << n;

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

	Value outQueue[100];
	Value stack[100];
	int opTop = -1, head = -1;

	Value token;

	char input[300];
	cin.getline(input, 300);

	int pos = 0;
	token = ntokenizer(input, pos);

	while (token.type != END){
		if (token.type == NUMBER){
			print(token);
			outQueue[++head] = token;
		}

		else if (token.type == BIN_OPERATOR){
			while (opTop >= 0 && stack[opTop].type == BIN_OPERATOR){
				if (isLeftAssoc[token.binary.index])
				{
					if (binPrecedence[token.binary.index] > binPrecedence[stack[opTop].binary.index]) break;
				}
				else if (binPrecedence[token.binary.index] >=  binPrecedence[stack[opTop].binary.index]) break;

				calcQueueHead(outQueue, head, stack[opTop].binary);
				print(stack[opTop--]);
			}
			stack[++opTop] = token;
		}

		else if (token.type == LBRACKET) {
			stack[++opTop] = token;
		}

		else if (token.type == RBRACKET){
			while (stack[opTop].type != LBRACKET){
				calcQueueHead(outQueue, head, stack[opTop].binary);
				print(stack[opTop--]);
			}
			if (opTop >= 0) opTop--;
			else { cout << "\nError"; opTop = -1; cin.get(); exit(1); }
		}
		token = ntokenizer(input, pos);
	} //end while

	//--------------
	while (opTop >= 0){
		if (stack[opTop].type != BIN_OPERATOR) { cout << "\nError"; cin.get(); exit(1); }
		calcQueueHead(outQueue, head, stack[opTop].binary);
		print (stack[opTop--]);
	}
	cout << "\nresult: ";
	print(outQueue[0]);
	cout << endl;
	cin.get();
}