#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define queue_size 100
#define maze_size  6

typedef struct _queueobjectrec_ {
	short r;
	short c;
}POS;

typedef POS element;

element queue[queue_size];
int front, rear;

element here = { 1,0 }; 

char maze[maze_size][maze_size] = {
	{'1','1','1','1','1','1'},
	{'e','0','1','0','0','1'},
	{'1','0','0','0','1','1'},
	{'1','0','1','0','1','1'},
	{'1','0','1','0','0','x'},
	{'1','1','1','1','1','1'},
};

void init_queue()
{
	front = rear = 0;
}

int isEmpty()
{
	if (front == rear)
		return 1;
	else
		return 0;
}

int isfull()
{
	if (front == (rear + 1)&queue_size)
		return 1;
	else
		return 0;
}

void enqueue(element val)
{
	if (isfull())
	{
		printf("full");
		return;
	}
	else {
		rear = (rear + 1) % queue_size;
		queue[rear] = val;
	}
}

element dequeue()
{
	if (isEmpty())
	{
		printf("empty");
		return;
	}
	else {
		front = (front + 1) % queue_size;
		return queue[front];
	}
}

void printq()
{
	if (!isEmpty())
	{
		printf("\n[");
		for (int i = front +1; i <= rear; i++)
		{
			printf("(%d %d) ", queue[i].r, queue[i].c);
		}
		printf("]\n");
	}
}

void pushloc(int r, int c)
{
	if (r < 0 || c < 0) return;
	if (maze[r][c] != '1' && maze[r][c] != '.') {
		element temp;
		temp.r = r;
		temp.c = c;
		enqueue(temp);
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
	printq();

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
		printq();

		if (isEmpty()) {
			printf("Failure\n");
			return;
		}
		else
		{
			here = dequeue();
		}
		printmaze(maze);
		printq();
		getchar();
	}
	printf("\nsuccess\n");
}

int main()
{
	init_queue();
	findroot();
	getchar();
	return 0;
}