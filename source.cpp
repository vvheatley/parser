#include <iostream>
#include <math.h>

using namespace std;

enum ttype{
	END,
	OPERATOR,
	NUMBER,
	LBRACKET,
	RBRACKET,
};

const char delim[] = "+-/*()";

inline bool isDelim (char *symb)
{
	for (int i = 0; delim[i] != '\0'; ++i){
		if (*symb == delim[i]) return true;
	}
	return false;
}
ttype tokenizer (char *&token, char *expr, int &pos)
{
	//delete token;
	char *symb = expr + pos;

	while(*symb == ' '){
		symb++;
		pos++;
	}	
	if (*symb == '\0') {
		token = NULL;
		return END;
	}
	if (isDelim(symb)) {
		token = new char [2];
		token[0] = *symb;
		token[1] = '\0';
		++pos;
		switch (*symb){
			case '(': return LBRACKET;
			case ')': return RBRACKET;
			default : return OPERATOR;
		}
	}

	symb++;
	while(*symb != '\0' && *symb != ' ' && !isDelim(symb)){
		symb++;
	}
	int size = symb - expr - pos + 1;
	token = new char [size];
	memcpy(token, expr+pos, size-1);
	token[size-1] = '\0';
	pos = symb-expr;
	return NUMBER;
}

int priority(char op)
{
	switch (op){
		case '+':case'-':return 0;
		case '*':case'/':return 1;
	}
	//return -1;
}
ttype valType(char token){
	switch (token){
		case '(':return LBRACKET;
		case ')':return RBRACKET;
		default :return OPERATOR;
	}
}

template <size_t size>
void printStack(char (&stack)[size], int opTop){
	while (opTop >=0)
		cout << stack[opTop--] << "  ";
	cout << endl;

}
void main()
{
	char stack[200], *inputStack[200];
	int opTop = 0, inpTop = 0;

	double res = 0;
	char lastOperator = '+';
	char input[200];

	cin.getline(input, 200);

	char  *token= NULL;

	ttype type;
	int n = 0;

	while ((type = tokenizer (token, input, n)) != END){
		if (type == NUMBER) cout << token << " ";

		else if (type == OPERATOR){
			while (opTop > 0 && valType(stack[opTop-1]) == OPERATOR && priority(token[0]) <= priority(stack[opTop-1])){

				cout << stack[--opTop] << " ";
			}
			stack[opTop++] = token[0];
		}

		else if (type == LBRACKET) stack[opTop++] = token[0];

		else if (type == RBRACKET) {
			while (valType(stack[opTop-1]) != LBRACKET){
				cout << stack[--opTop] << " ";
			}
			if (opTop > 0) opTop--;
			else {
				cout << "Error";
				opTop = 0;
				break;
			}
		}
	}
	while (opTop > 0){
		if (valType(stack[opTop-1]) != OPERATOR) { cout << "Error"; break; }
		cout << stack[--opTop] << " ";
	}
	cin.get();
}
