#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define True 1
#define False -1

typedef int element;

typedef struct _stackNode {
	element data;
	struct _stackNode* link;
}stackNode;

stackNode* top;

void init()
{
	top = NULL;
}

int is_empty()
{
	if (top == NULL)
		return 1;
	else
		return 0;
}

void push(element item)
{
	stackNode* temp = (stackNode*)calloc(1, sizeof(stackNode));
	temp->data = item;
	temp->link = top;
	top = temp;
}

element pop()
{
	element item;
	stackNode* temp = top;
	if (top == NULL)
		return 0;
	else
	{
		item = top->data;
		top = top->link;
		free(temp);

		return item;
	}
}

element peek()
{

	if (top == NULL)
		return 0;
	else
	{
		return top->data;
	}
}

void printstack()
{
	stackNode* p = top;
	while (p)
	{
		printf("%c ", p->data);
		p = p->link;
	}
	printf("\n");
}

void freestack()
{
	stackNode* pre = NULL;
	stackNode* cur = NULL;

	pre = cur = top;
	while (cur != NULL)
	{
		pre = cur;
		cur = cur->link;
		free(pre);
		pre = NULL;
	}
	top = NULL;
}

int testpair(char* exp)
{
	char symbol, open_pair;
	int len = strlen(exp);

	init();
	for (int i = 0; i < len; i++)
	{
		printstack();
		symbol = exp[i];
		switch (symbol)
		{
		case '(':
		case '{':
		case '[':
			push(symbol);
			break;
		
		case ')':
		case '}':
		case ']':
			if (is_empty())
				return False;
			else
			{
				open_pair = pop();
				if (open_pair == '(' && symbol == ')')
					break;
				else if (open_pair == '{' && symbol == '}')
					break;
				else if (open_pair == '[' && symbol == ']')
					break;
				else
					return False;
			}
		}
	}
	if (is_empty())
		return True;
	else
		return False;
}

int precedence(char op)
{
	switch (op)
	{
	case '(' :
	case ')' :
		return 0;
	case '+' :
	case '-' :
		return 1;
	case '*' :
	case '/' :
		return 2;
	}
}

void infix_to_postfix(char* infix, char* postfix)
{
	int i = 0;
	int j = 0;
	char c, op;
	while (infix[i] != '\0')
	{
		c = infix[i++];

		if (c >= '0' && c <= '9')
		{
			postfix[j++] = c;

			while (infix[i] >= '0' && infix[i] <= '9') //피연산자가 10보다 클수 잇기 떄문에
			{
				postfix[j++] = infix[i++];
			}
			postfix[j++] = ' '; //피연산자와 연산자 구분
		}
		
		else if (c == '(')
		{
			push(c);
		}
		else if (c == ')')
		{
			while (!(is_empty()))
			{
				op = pop();
				if (op == ')')
				{
					break;
				}
				else
				{
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
			}
		}
		else if (c == '+' || c == '*' || c == '-' || c == '/')
		{
			while (!(is_empty())) {
				op = peek();
				if (precedence(c) <= precedence(op))
				{
					op = pop();
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
				else
					break;
			}
			push(c);
		}
		while (!is_empty())
		{
			postfix[j++] = pop();
			postfix[j++] = ' ';
		}
		postfix[j] = '\0';
		 
	}
}

int evalPostfix(char* exp)
{
	int ope1, ope2, value, i;
	int len = strlen(exp);

	char symbol;
	
	init();
	
	for (i = 0; i < len; i++)
	{
		symbol = exp[i];
		
		if (symbol >= '0' && symbol <= '9')
		{
			value = symbol - '0';
			i++;
			while (exp[i] >= '0' && exp[i] <= '9')
			{
				value *= 10;
				value += (exp[i++] - '0'); 
			}
			push(value);
		}
		else
		{
			ope2 = pop();
			ope1 = pop();
			symbol = exp[i];
			switch (symbol)
			{
			case '+': push(ope1 + ope2); break;
			case '-': push(ope1 - ope2); break;
			case '*': push(ope1 * ope2); break;
			case '/': push(ope1 / ope2); break;
			case '%': push(ope1 % ope2); break;
			}
		}
	}
	return pop();
 }

void bracket_test()
{
	int ret;
	char* express = "{(a+b)*5+{(xos(+y)+7)}-1}*4";
	ret = testpair(express);
	if (ret == True)
		printf("good");
	else
		printf("no");
}

int main()
{
	bracket_test();
	return 0;
}