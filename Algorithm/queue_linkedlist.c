#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct _QNODE_ {
	element data;
	struct _QNODE_* link;
}QNODE;

typedef struct _LQUEUE_TYPE_ {
	QNODE* front;
	QNODE* rear;
}LQUEUE_TYPE;

LQUEUE_TYPE* createLinkedQueue()
{
	LQUEUE_TYPE* LQ = NULL;
	LQ = (LQUEUE_TYPE*)calloc(1, sizeof(LQUEUE_TYPE));
	LQ->front = NULL;
	LQ->rear = NULL;

	return LQ;
}

int isempty(LQUEUE_TYPE* lq)
{
	if (lq->front == NULL) {
		printf("empty");
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void enqueue(LQUEUE_TYPE* lq, element item)
{
	QNODE* newnode = NULL;
	newnode = (QNODE*)calloc(1, sizeof(QNODE));
	newnode->link = NULL;
	newnode->data = item;

	if (lq->front == NULL)
	{
		lq->front = newnode;
		lq->rear = newnode;
	}
	else
	{
		lq->rear->link = newnode;
		lq->rear = newnode;
	}

}

element deQueue(LQUEUE_TYPE* lq)
{
	QNODE* old = NULL;
	element item;

	if (isempty(lq))
		return FALSE;
	else
	{
		old = lq->front;
		lq->front = lq->front->link;
		item = old->data;
		if (lq->front == NULL)
			lq->rear = NULL;
		free(old);
		return item;
	}
}

element peek(LQUEUE_TYPE* lq)
{
	element item;
	if (isempty(lq))
		return FALSE;
	else
	{
		item = lq->front->data;
		return item;
	}
}

void printQ(LQUEUE_TYPE* lq)
{
	QNODE* temp = lq->front;
	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->link;
	}
	printf("\n");
}
void test1()
{
	LQUEUE_TYPE* lq = createLinkedQueue();
	LQUEUE_TYPE* lq2 = createLinkedQueue();
	for (int i = 0; i < 5; i++)
	{
		enqueue(lq, i);
		printQ(lq);
	}

	printf("거짓포화 여부 확인\n");
	for (int i = 0; i < 10; i++)
	{
		enqueue(lq2, i);
		deQueue(lq2);
		printQ(lq2);
	}
}

int main()
{
	test1();
	getchar();
	return 0;
}

