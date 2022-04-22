#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stack_size 100

typedef int element;

element stack[stack_size];
int top = -1;

void init()
{
	top = -1;
}

int isEmpty()
{
	if (top == -1)
		return 1;
	else
		return 0;
}

int isfull()
{
	if (top == stack_size - 1)
		return 1;
	else
		return 0;
}

void push(element item)
{
	if (isfull())
		return ;
	else
	{
		top += 1;
		stack[top] = item;
	}
}

element pop()
{
	if (isEmpty())
		return 0;
	else
		return stack[top--];
}

element peek()
{
	if (isEmpty())
		return 0;
	else
		return stack[top];
}

void printstack()
{
	for (int i = top; i >= 0; i--)
		printf("%d ", stack[i]);
	printf("\n");
}

void stack_test1()
{
	printstack();
	for (int i = 0; i < 19; i++)
	{
		push(i);
		printstack();
	}
		
	
}

int main()
{
	stack_test1();
	return 0;
}