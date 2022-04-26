#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef int element;

typedef struct _dQNODE_ {
	element data;
	struct _dQNODE_* llink;
	struct _dQNODE_* rlink;
}DQNODE;

typedef struct _DQUEUE_TYPE_ {
	DQNODE* front;
	DQNODE* rear;
}DQUEUE_TYPE; 

DQUEUE_TYPE* createdeque()
{
	DQUEUE_TYPE* dq = NULL;
	dq = (DQUEUE_TYPE*)calloc(1, sizeof(DQUEUE_TYPE));
	dq->front = NULL;
	dq->rear = NULL;

	return dq;
}

int isempty(DQUEUE_TYPE* dq)
{
	if (dq->front == NULL)
		return TRUE;
	else
		return FALSE;
}

void insertfront(DQUEUE_TYPE* dq, element item)
{
	DQNODE* newnode = NULL;
	newnode = (DQNODE*)calloc(1, sizeof(DQNODE));
	newnode->data = item;

	if (dq->front == NULL)
	{
		dq->front = newnode;
		dq->rear = newnode;
		newnode->llink = NULL;
		newnode->rlink = NULL;
	}
	else
	{
		dq -> front->llink = newnode;
		newnode->llink = NULL;
		newnode->rlink = dq->front;
		dq->front = newnode;
	}
}

void insertrear(DQUEUE_TYPE* dq, element item)
{
	DQNODE* newnode = NULL;
	newnode = (DQNODE*)calloc(1, sizeof(DQNODE));
	newnode->data = item;

	if (dq->rear == NULL)
	{
		dq->front = newnode;
		dq->rear = newnode;
		newnode->llink = NULL;
		newnode->rlink = NULL;
	}
	else
	{
		dq->rear->rlink = newnode;
		newnode->llink = dq->rear;
		newnode->rlink = NULL;
		dq->rear = newnode;
	}
}

element deletefront(DQUEUE_TYPE* dq)
{
	DQNODE* old = NULL;
	element item;

	if (isempty(dq))
		return FALSE;
	else
	{
		old = dq->front;
		item = old->data;
		if (dq->front->rlink == NULL)
		{
			dq->front = NULL;
			dq->rear = NULL;
		}
		else
		{
			dq->front = old->rlink;
			dq->front->llink = NULL;
		}
		free(old);
		return item;
	}
}

element deleterear(DQUEUE_TYPE* dq)
{
	DQNODE* old = NULL;
	element item;

	if (isempty(dq))
		return FALSE;
	else
	{
		old = dq->rear;
		item = old->data;
		if (dq->rear->llink == NULL)
		{
			dq->front = NULL;
			dq->rear = NULL;
		}
		else
		{
			dq->rear = old->llink;
			dq->rear->rlink = NULL;
		}
		free(old);
		return item;
	}
}

element peek(DQUEUE_TYPE* dq)
{
	if (isempty(dq))
		return FALSE;
	else
		return dq->front->data;
}

void printdq(DQUEUE_TYPE* dq)
{
	DQNODE* temp = dq->front;

	while (temp)
	{
		printf("%d ", temp->data);
		temp = temp->rlink;
	}
	printf("\n");
}

void testdeq()
{
	DQUEUE_TYPE* dq = createdeque();
	for (int i = 0; i < 10; i++)
	{
		insertfront(dq, i);
		printdq(dq);
	}

	for (int i = 0; i < 10; i++)
	{
		insertrear(dq, i);
		printdq(dq);
	}
	for (int i = 0; i < 10; i++)
	{
		deletefront(dq, i);
		printdq(dq);
	}
	for (int i = 0; i < 10; i++)
	{
		deleterear(dq, i);
		printdq(dq);
	}
}

int main()
{
	testdeq();
	return 0;
}