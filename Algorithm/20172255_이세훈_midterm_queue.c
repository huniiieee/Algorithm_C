#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//test 2164
#if 0
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
		return 1;
	}
	else {
		return 0;
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
		return -1;
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
		return -1;
	else
	{
		item = lq->front->data;
		return item;
	}
}

element back(LQUEUE_TYPE* lq)
{
	element item;
	if (isempty(lq))
		return -1;
	else
	{
		item = lq->rear->data;
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

int queue_size(LQUEUE_TYPE* lq)
{
	QNODE* temp = lq->front;
	int cnt = 0;
	if (isempty(lq))
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

void test_2164()
{
	LQUEUE_TYPE* lq = createLinkedQueue();
	int cnt;
	char nlc;
	element temp;
	scanf("%d", &cnt);
	scanf("%c", &nlc);

	for (int i = 1; i < cnt+1; i++)
		enqueue(lq, i);

	for (int i = 0; i < cnt - 1; i++)
	{
		deQueue(lq);
		temp = deQueue(lq);
		enqueue(lq, temp);
	}
	printf("%d", lq->front->data);
}

#endif

// test 18258 (연결리스트 사용하면 size구하는데 시간초과 떠서 배열 사용)
#if 0
#define TRUE 1
#define FALSE 0

#define Q_size 4000000

typedef int element;

typedef struct _queuetype_ {
	element queue[Q_size];
	int front, rear;
}queuetype;

queuetype* creatrequeue()
{
	queuetype* Q;
	Q = (queuetype*)calloc(1, sizeof(queuetype));
	Q->front = -1;
	Q->rear = -1;

	return Q;
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
	Q->rear += 1;
	Q->queue[Q->rear] = item;
	
}

element dequeue(queuetype* Q)
{
	if (isempty(Q))
		return -1;
	else {
		Q->front += 1;
		return Q->queue[Q->front];
	}
}

element peek(queuetype* Q)
{
	if (isempty(Q))
		return -1;
	else
		return Q->queue[Q->front + 1];
}

element back(queuetype* Q)
{
	if (isempty(Q))
		return -1;
	else
		return Q->queue[Q->rear];
}

void test_18258()
{
	queuetype* q = creatrequeue();
	int cnt;
	char nlc;
	scanf("%d", &cnt);
	scanf("%c", &nlc);

	char ope[100] = { 0, };
	char check;
	int check_int = 0;
	for (int i = 0; i < cnt; i++)
	{
		scanf("%s", &ope);
		scanf("%c", &nlc);

		if (strlen(ope) == 3) //pop
			printf("%d\n", dequeue(q));
		else
		{
			check = ope[0];
			switch (check)
			{
			case 'e':
				printf("%d\n", isempty(q)); break;
			case 'f':
				printf("%d\n", peek(q)); break;
			case 'b':
				printf("%d\n", back(q)); break;
				break;
			case 's':
				printf("%d\n", q->rear-q->front); break;
			case 'p':
				scanf("%d", &check_int);
				scanf("%c", &nlc);
				enqueue(q, check_int);
				break;
			}
		}
	}
}
#endif


int main()
{
	test_18258(); //배열 사용 
	test_2164(); //연결리스트 사용 
	return 0;
}
