#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define stack_size 100
#define maze_size  6


typedef struct _stackobjectrec_ {
	short r;
	short c;
}stackobject;

stackobject stack[stack_size];
int top = -1;
stackobject here = { 1,0 };

char maze[maze_size][maze_size] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

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

void push(stackobject item)
{
	if (isfull())
		return;
	else
	{
		top += 1; 
		stack[top] = item;
	}
}

stackobject pop()
{
	if (isEmpty())
		return;
	else
		return stack[top--];
}


void printstack()
{
	for (int i = maze_size - 1; i > top; i--)
	{
		printf("|     |\n");
	}
	for (int i = top; i >= 0; i--) {
		printf("|(%01d,%01d)|\n", stack[i].r, stack[i].c);
	}
	printf("---------\n");
}

void pushloc(int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		stackobject temp;
		temp.r = r;
		temp.c = c;
		push(temp);
	}
}

void printmaze(char m[maze_size][maze_size])
{
	int r, c;
	printf("\n\n");
	for (r = 0; r < maze_size; r++)
	{
		for (c = 0; c < maze_size; c++)
		{
			if (c == here.c && r == here.r)
			{
				printf("m ");
			}
			else
			{
				printf("%c ", m[r][c]);
			}
		}
		printf("\n");
	}
}

void findroot()
{
	short r, c;
	
	printmaze(maze);
	printstack();

	while (maze[here.r][here.c] != 'x')
	{

		printmaze(maze);
		r = here.r;
		c = here.c;
		
		maze[r][c] = '.';
		pushloc(r - 1, c);
		pushloc(r + 1, c);
		pushloc(r, c + 1);
		pushloc(r, c - 1);
		printstack();

		if (isEmpty()) {
			printf("Failure\n");
			return;
		}
		else
		{
			here = pop();  
		}
		printmaze(maze);
		printstack();
		getchar();
	}
	printf("\nsuccess\n");
}

int main()
{
	findroot();
	getchar();
	return 0;
}
