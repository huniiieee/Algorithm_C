#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
		printf("%d ", p->data);
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

void stack_array_test()
{
	element item;
	init();
	for (int i = 0; i < 10; i++)
	{
		push(i);
		printstack();
	}
}

int main()
{
	stack_array_test();
	freestack();
	printstack();

	return 0;
}