#define _CRT_SECURE_NO_WARNINGS

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
		return -1;
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
		return -1;
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


int stack_size()
{
	stackNode* temp = top;
	int cnt = 0;
	if (is_empty())
		return cnt;
	else
	{
		while (temp != NULL)
		{
			cnt++;
			temp = temp->link;
		}
	}
	return cnt;
}

void test_10828()
{
	init();
	int cnt;
	scanf("%d", &cnt);
	char ope[100] = { 0, };
	char nlc;
	char check;
	int check_int=0;
	for (int i = 0; i < cnt; i++)
	{
		scanf("%s", &ope);
		scanf("%c", &nlc);

		if (strlen(ope) == 3) //pop,top
		{
			check = ope[0];
			switch (check)
			{
			case 'p':
				printf("%d\n", pop()); break;
			case 't':
				printf("%d\n", peek()); break;
			}
		}
		else
		{
			check = ope[0];
			switch (check) //push,empty,size
			{
			case 'p':
				scanf("%d", &check_int);
				scanf("%c", &nlc);
				push(check_int);
				break;
			case 'e':
				printf("%d\n",is_empty());
				break;
			case 's':
				printf("%d\n",stack_size()); break;
			}
		}
	}
}

void test_1874()
{
	init();
	char nlc;
	int num = 0;
	int temp = 0;
	int temp2 = 0;
	int flag = 0;
	
	int cnt = 0;
	scanf("%d", &num);
	scanf("%c", &nlc);


	int* check = (int*)calloc(num+1, sizeof(int));
	char* result = (char*)calloc(num * 2, sizeof(char));

	scanf("%d", &temp);
	scanf("%c", &nlc);

	for (int i = 1; i <= temp; i++)
	{
		push(i);
		result[cnt] = '+';
		cnt++;
	}
	check[temp] = 1; //popµÊ
	pop();
	result[cnt] = '-';
	cnt++;

	for (int i = 0; i < num - 1; i++)
	{
		scanf("%d", &temp2);
		scanf("%c", &nlc);
		
		


		if (peek() > temp2)
		{
			printf("NO");
			flag = 1;
			break;
		}

		else if (peek() == temp2)
		{
			check[temp2] = 1;
			pop();
			result[cnt] = '-';
			cnt++;
		}
		else if (is_empty())
		{
			for (int j=1; j <= temp2; j++)
			{
				if (check[j] == 0)
				{
					push(j);
					result[cnt] = '+';
					cnt++;
				}
				else
					continue;
			}
			check[temp2] = 1;
			pop();
			result[cnt] = '-';
			cnt++;
		}
		else {
			for (int j = peek()+1; j <= temp2; j++)
			{
				if (check[j] == 0)
				{
					push(j);
					result[cnt] = '+';
					cnt++;
				}
				else
					continue;
			}
			check[temp2] = 1;
			pop();
			result[cnt] = '-';
			cnt++;
		}
	}

	if (flag==0)
	{
		for (int i = 0; i < 2 * num; i++)
		{
			printf("%c\n", result[i]);
		}
	}



}

void test_17298()
{
	init();
	int num = 0;
	char nlc;
	scanf("%d", &num);
	scanf("%c", &nlc);
	int* in = (int*)calloc(num, sizeof(int));
	int* result = (int*)calloc(num, sizeof(int));
	for (int i = 0; i < num; i++)
	{
		scanf("%d", &in[i]);
	}

	for (int i = num - 1; i >= 0; i--)
	{
		if (is_empty())
			result[i] = -1;
		else
		{
			while (peek() <= in[i])
			{
				if (pop() == -1)
					break;
			}
			if (is_empty())
				result[i] = -1;
			else
				result[i] = peek();
		}
		push(in[i]);

	}
	for (int i = 0; i < num; i++)
		printf("%d ", result[i]);
}
int main()
{
	//test_10828();
	//test_1874();
	test_17298();
	return 0;
}