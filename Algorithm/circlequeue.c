#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define Q_size 10

typedef int element;

typedef struct _queuetype_ {
	element queue[Q_size];
	int front, rear;
}queuetype;

queuetype* creatrequeue()
{
	queuetype* Q;
	Q = (queuetype*)calloc(1, sizeof(queuetype));
	Q->front = 0;
	Q->rear = 0;

	return Q;
}

int isfull(queuetype* Q)
{
	if (((Q->rear+1)%Q_size) == (Q->front%Q_size))
	{
		printf("circle queue is full");
		return TRUE;
	}
	else
		return FALSE;
}

int isempty(queuetype* Q)
{
	if (Q->front == Q->rear)
		return TRUE;
	else
		return FALSE;
}

void enqueue(queuetype* Q, element item)
{
	if (isfull(Q))
		return;
	else
	{
		Q->rear = (Q->rear+1)%Q_size;
		Q->queue[Q->rear] = item;
	}
}

element dequeue(queuetype* Q)
{
	if (isempty(Q))
		return;
	else {
		Q->front = (Q->front+1)%Q_size;
		return Q->queue[Q->front];
	}
}

element peek(queuetype* Q)
{
	if (isempty(Q))
		return;
	else
		return Q->queue[(Q->front + 1)%Q_size];
}

void printqueue(queuetype* Q)
{
	int first = (Q->front + 1) % Q_size;
	int last = (Q->rear + 1) % Q_size;
	int i = first;

	while (i != last)
	{
		printf("%d ", Q->queue[i]);
		i = (i + 1) % Q_size;
	}
	printf("\n");
}

void testqueue()
{
	queuetype* Q1 = creatrequeue();
	queuetype* Q2 = creatrequeue();
	for (int i = 0; i < 9; i++)
	{
		enqueue(Q1, i);
		printqueue(Q1);
	}
	for (int i = 0; i < 5; i++)
	{
		dequeue(Q1);
		printqueue(Q1);
	}

	//거짓포화(배열을 이용한 단점)
	for (int i = 0; i < 16; i++)
	{
		enqueue(Q2, i);
		dequeue(Q2);
		printqueue(Q2);
	}
}

int main()
{
	testqueue();
	getchar();
	return 0;
}