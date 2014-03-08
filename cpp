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

const char delim[] = "+-/*()^%";


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
	while(*symb != '\0' &&*symb != ' ' && !isDelim(symb)){
		symb++;
	}
	int size = symb - expr - pos + 1;
	token = new char [size];
	memcpy(token, expr+pos, size-1);
	token[size-1] = '\0';
	pos = symb-expr;
	return NUMBER;
}



void main()
{
	char operatorStack[200], *inputStack[200];
	int opTop = 0, inpTop = 0;

	double res = 0;
	char lastOperator = '+';
	char input[200];

	cin.getline(input, 200);

	char  *token= NULL;

	ttype type;
	int n = 0;

	while ((type = tokenizer (token, input, n)) != END){
		if (type == OPERATOR){
			lastOperator = token[0];
		}

		else if (type == NUMBER){
			switch (lastOperator)
			{
				case '+': res += atof(token); break;
				case '-': res -= atof(token); break;
				case '*': res *= atof(token); break;
				case '/': res /= atof(token); break;
			}


		}
		inputStack[inpTop++] = token;
		cout << token << "|\n";
	}
	while (inpTop > 0){
		cout << inputStack[--inpTop] << endl;
	}
	cout << endl << res;
	

	cin.get();
}
