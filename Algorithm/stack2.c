#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define stacksize 100
typedef int element;

typedef struct _arraysize_
{
	element stackarr[stacksize];
	int topindex;
	int size;
}arraysize;

void init(arraysize* stack, int size)
{
	stack->size = size;
	stack->topindex = -1;
}

int isempty(arraysize* stack)
{
	if (stack->topindex == -1)
		return 1;
	else
		return 0;
}

int isfull(arraysize* stack)
{
	if (stack->topindex == (stack->size - 1))
		return 1;
	else
		return 0;
}

void push(arraysize* stack, element item)
{
	if (isfull(stack))
		return 0;
	else
	{
		stack->topindex++;
		stack->stackarr[stack->topindex] = item;
	}
}

element pop(arraysize* stack)
{
	if (isempty(stack))
		return 0;
	else
	{
		return stack->stackarr[(stack->topindex)];
	}
}

element peek(arraysize* stack)
{
	if (isempty(stack))
		return 0;
	else
	{
		return stack->stackarr[(stack->topindex)--];
	}
}

void printstack(arraysize* stack)
{
	for (int i = stack->topindex; i >= 0; i--)
		printf("%d ", stack->stackarr[i]);
	printf("\n");
}

void stacktest()
{
	arraysize stack1;

	init(&stack1, 20);
	printstack(&stack1);
	for (int i = 0; i < 19; i++)
	{
		push(&stack1,i);
		printstack(&stack1);
	}
}
int main()
{
	stacktest();
	return 0;
}