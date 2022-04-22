#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define Max_len 1024
#define True 1
#define False 0

void test1()
{
	//버퍼
	char buffer[Max_len] = { 0, };

	//읽을 문자열
	char* str = NULL;

	//알파벳 빈도수 배열
	int frequncy_Alphabet[26] = { 0, };

	//문자열 길이
	int len;

	printf("Input a string:\n");

	//문자열 읽기
	gets(buffer);
	len = (int)strlen(buffer);
	str = (char*)calloc(len + 1, sizeof(char));
	strncpy(str, buffer, len + 1);
	
	//알파벳 빈도수 체크
	for (int i = 0; i < len; i++)
	{
		//알파베 아닌경우 건너뛰기
		if (str[i] < 'A' || (str[i] > 'Z' && str[i] < 'a') || str[i]>'z')
			continue;

		//대문자
		else if ((str[i] >= 'A') && (str[i] <= 'Z'))
			frequncy_Alphabet[str[i] - 'A'] ++;

		//소문자
		else
			frequncy_Alphabet[str[i] - 'a'] ++;
	}

	printf("[Alphabet frequency]\n");
	for (int i = 0; i < 26; i++)
	{
		printf("%c: %d\n", i + 'a',frequncy_Alphabet[i]);
	}
	
	free(str);
}

//연결리스트 노드 구조 정의
typedef struct _LISTNODE_ {
	char data[Max_len];
	struct _LISTNODE_* link;	
} listnode;

//head 노드 정의
typedef struct _LINKEDLIST_H_ {
	listnode* head;
}linkedlist_h;

//공백 연결리스트 생성
linkedlist_h* createLinkedList_h(void) {
	linkedlist_h* L;
	L = (linkedlist_h*)calloc(1, sizeof(linkedlist_h));
	L->head = NULL;
	return L;
}

//연결리스트 순차적으로 출력
void printList(linkedlist_h* L)
{
	listnode* p;
	printf("L= (");
	p = L->head;
	while (p != NULL)
	{
		printf("%s", p->data);
		p = p->link;
		if (p != NULL)
			printf(", ");
	}
	printf(") \n");
}

//첫 번째 노드 삽입
void insertFirstNode(linkedlist_h* L, char* x) {
	listnode* newnode;
	newnode = (listnode*)malloc(sizeof(listnode));
	strcpy(newnode->data, x);
	newnode->link = L->head;
	L->head = newnode;
}

//노드 중간 삽입
void insertMiddleNode(linkedlist_h* L, listnode* pre, char* x)
{
	listnode* newnode;

	newnode = (listnode*)malloc(sizeof(listnode));
	strcpy(newnode->data, x);

	if (L->head == NULL) {
		newnode->link = NULL;
		L->head = newnode;
	}

	else if (pre == NULL) {
		newnode->link = L->head;
		L->head = newnode;
	}

	else {
		newnode->link = pre->link;
		pre->link = newnode;
	}
}

//노드 마지막 삽입
void insertlastnode(linkedlist_h* L, char* x) {
	listnode* newnode;
	listnode* temp;

	newnode = (listnode*)malloc(sizeof(listnode));
	strcpy(newnode->data, x);
	newnode->link = NULL;

	if (L->head == NULL) {
		L->head = newnode;
		return;
	}

	temp = L->head;
	while (temp->link != NULL) temp = temp->link;
	temp->link = newnode;
}

//노드검색
listnode* searchnode(linkedlist_h* L, char* x)
{
	listnode* temp;
	temp = L->head;
	while (temp != NULL)
	{
		if (strcmp(temp->data, x) == 0) return temp;
		else temp = temp->link;
	}
	return temp;
}

// 노드 삭제
void deltenode(linkedlist_h* L, listnode* p)
{
	listnode* pre = NULL;
	listnode* cur = NULL;
	listnode* find = NULL;


	if (L->head == NULL || p == NULL) return;

	pre = cur = L->head;
	if (pre == p)
	{
		cur = pre->link;
		free(pre);
		L->head = cur;
		return;
	}

	cur = cur->link;
	while (cur != NULL)
	{
		if (cur == p)
		{
			find = cur;
			break;
		}
		pre = cur;
		cur = cur->link;
	}
	if (find != NULL)
	{
		pre->link = find->link;
		free(find);
	}
}

//메모리해제
void freelinkedlist_h(linkedlist_h* L)
{
	listnode* p;

	if (L != NULL)
	{
		while (L->head != NULL) {
			p = L->head;
			L->head = L->head->link;
			free(p);
			p = NULL;
		}
		L->head = NULL;
	}
	else
	{
		fprintf(stderr, "error: NULL list\n");
		return;
	}
}

//key값을 이용하여 오름차순 정렬하여 리스트에 연결
void orderedinsert_A(linkedlist_h* L, char* x)
{
	listnode* pre = NULL;
	listnode* cur = NULL;
	listnode* newnode = NULL;

	newnode = (listnode*)malloc(sizeof(listnode));
	strncpy(newnode->data, x,Max_len);
	newnode->link = NULL;

	pre = cur = L->head;

	if (cur == NULL)
	{
		L->head = newnode;
		return;
	}
	else if (cur != NULL)
	{
		if (strncmp(cur->data, x, Max_len) > 0)
		{
			newnode->link = cur;
			L->head = newnode;
			return;
		}
	}

	cur = cur->link;
	while (cur != NULL)
	{
		if (strncmp(cur->data, x, Max_len) > 0)
		{
			break;
		}
		pre = cur;
		cur = cur->link;
	}
	newnode->link = pre->link;
	pre->link = newnode;
}

//key값을 이용하여 내림차순 정렬하여 리스트에 연결
void orderedinsert_D(linkedlist_h* L, char* x)
{
	listnode* pre = NULL;
	listnode* cur = NULL;
	listnode* newnode = NULL;

	newnode = (listnode*)malloc(sizeof(listnode));
	strncpy(newnode->data, x, Max_len);
	newnode->link = NULL;

	pre = cur = L->head;

	if (cur == NULL)
	{
		L->head = newnode;
		return;
	}
	else if (cur != NULL)
	{
		if (strncmp(cur->data, x, Max_len) < 0)
		{
			newnode->link = cur;
			L->head = newnode;
			return;
		}
	}

	cur = cur->link;
	while (cur != NULL)
	{
		if (strncmp(cur->data, x, Max_len) < 0)
		{
			break;
		}
		pre = cur;
		cur = cur->link;
	}
	newnode->link = pre->link;
	pre->link = newnode;
}


void test2()
{
	linkedlist_h* L;
	linkedlist_h* L2;
	linkedlist_h* L3;
	linkedlist_h* L4;
	listnode* p;

	L = createLinkedList_h();
	L2 = createLinkedList_h();
	L3 = createLinkedList_h();
	L4 = createLinkedList_h();

	printf("\n(1) 리스트 머리에 노드 삽입하기! \n");
	insertFirstNode(L, "apple");
	insertFirstNode(L, "banana");
	insertFirstNode(L, "cat");
	printList(L);

	printf("\n(2) 리스트 꼬리에 노드 삽입하기! \n");
	insertlastnode(L2, "apple");
	insertlastnode(L2, "banana");
	insertlastnode(L2, "cat");
	printList(L2);

	printf("\n(3) 리스트에서 노드 탐색하기! \n");
	p = searchnode(L, "banana");
	if (p == NULL) printf("찾는 데이터가 없습니다.\n");
	else printf("[%s]를 찾았습니다.\n", p->data);

	insertMiddleNode(L, p, "test");	

	p = searchnode(L, "test");
	if (p == NULL) printf("찾는 데이터가 없습니다.\n");
	else printf("[%s]를 찾았습니다.\n", p->data);

	printf("\n(4) 리스트에서 중간에 노드 삽입하기! \n");
	insertMiddleNode(L, p, "zero");
	printList(L);

	printf("\n(5) 리스트에 정렬하여 노드 삽입하기!\n");
	orderedinsert_A(L3, "absolute");
	orderedinsert_A(L3, "affine");
	orderedinsert_A(L3, "attain");
	orderedinsert_A(L3, "blue");
	orderedinsert_A(L3, "friday");
	orderedinsert_A(L3, "test");
	printList(L3);

	printf("\n(6) 리스트에서 노드 삭제하기! \n");
	p = searchnode(L3, "absolute");
	deltenode(L3, p);
	printList(L3);

	printf("\n(7) 리스트에 정렬하여 노드 삽입하기(내림차순정렬)!\n");
	orderedinsert_D(L4, "absolute");
	orderedinsert_D(L4, "affine");
	orderedinsert_D(L4, "attain");
	orderedinsert_D(L4, "blue");
	orderedinsert_D(L4, "friday");
	orderedinsert_D(L4, "test");
	printList(L4);

	freelinkedlist_h(L);
	if (L != NULL)
		free(L);
	freelinkedlist_h(L2);
	if (L2 != NULL)
		free(L2);
	freelinkedlist_h(L3);
	if (L3 != NULL)
		free(L3);
	freelinkedlist_h(L4);
	if (L4 != NULL)
		free(L4);



}



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
		return True;
	else
		return False;
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
	{
		printf("\n\n Stack is empty	 !\n");
		return 0;
	}
	else
	{
		item = temp->data;
		top = temp->link;
		free(temp);

		return item;
	}
}

element peek()
{

	if (top == NULL)
	{
		printf("Stack is empty");
		return 0;
	}
	else
	{
		return (top->data);
	}
}

void printstack()
{
	stackNode* p = top;
	while (p)
	{
		printf("%c ", p->data);
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

int testpair(char* exp)
{
	char symbol, open_pair;
	int len = (int)strlen(exp);

	init();
	for (int i = 0; i < len; i++)
	{
		
		symbol = exp[i];
		switch (symbol)
		{
		case '(':
		case '{':
		case '[':
			push(symbol); break;

		case ')':
		case '}':
		case ']':
			if (top==NULL)
				return False;
			else
			{
				open_pair = pop();
				if ((open_pair == '(' && symbol != ')') || (open_pair == '[' && symbol != ']') || (open_pair == '{' && symbol != '}'))
					return False;
				else
					break;
			}
		}
	}
	if (top==NULL)
		return True;
	else
		return False;
}

int precedence(char op)
{
	switch (op)
	{
	case '(':
	case ')':
		return 0;
	case '+':
	case '-':
		return 1;
	case '*':
	case '/':
	case '%':
		return 2;
	}
	return -1;
}

void infix_to_postfix(char* infix, char* postfix)
{
	int i = 0;
	int j = 0;
	char c, op;
	while (infix[i] != '\0')
	{
		c = infix[i++];

		if (c >= '0' && c <= '9')
		{
			postfix[j++] = c;

			while (infix[i] >= '0' && infix[i] <= '9') //피연산자가 10보다 클수 잇기 떄문에
			{
				postfix[j++] = infix[i++];
			}
			postfix[j++] = ' '; //피연산자와 연산자 구분
		}

		else if (c == '(')
		{
			push(c);
		}
		else if (c == ')')
		{
			while (!is_empty())
			{
				op = pop();
				if (op == '(')
				{
					break;
				}
				else
				{
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
			}
		}
		else if (c == '+' || c == '*' || c == '-' || c == '/' || c=='%')
		{
			while (!is_empty()) {
				op = peek();
				if (precedence(c) <= precedence(op))
				{
					op = pop();
					postfix[j++] = op;
					postfix[j++] = ' ';
				}
				else
					break;
			}
			if (c == '-')
			{
				op = 0;
			}
			push(c);
		}
	}
	while (!is_empty())
	{
		postfix[j++] = pop();
		postfix[j++] = ' ';
	}
	postfix[j] = '\0';
}

int evalPostfix(char* exp)
{
	int ope1, ope2, value, i;
	int len = (int)strlen(exp);

	char symbol;

	top = NULL;

	for (i = 0; i < len; i++)
	{
		symbol = exp[i];

		if (symbol >= '0' && symbol <= '9')
		{
			value = symbol - '0';
			i += 1;
			while (exp[i] >= '0' && exp[i] <= '9')
			{
				value *= 10;
				value += (exp[i] - '0');
				i += 1;
			}
			push(value);
		}
		else if (symbol =='+' || symbol =='-' || symbol == '*' || symbol == '/' || symbol == '%')
		{
			ope2 = pop();
			ope1 = pop();
			
			switch (symbol)
			{
			case '+': push(ope1 + ope2); break;
			case '-': push(ope1 - ope2); break;
			case '*': push(ope1 * ope2); break;
			case '/': push(ope1 / ope2); break;
			case '%': push(ope1 % ope2); break;
			}
		}
	}
	return pop();
}

void test3()
{
	int result;
	char infix_expr[13][80] = { "3*5-6/2", 
		"((4+2)/4)-(3+70/(7*5))", 
		"((((5*6)+7)-8)*9)", 
		"((((5*6)+7)-8)*9)+(9+8)*7", 
		"((((5*6)+7)-8)*9)+(((9+8)*7)%4)", 
		"(((((((((1*2)*3)*4)*5)*6)*7)*8)*9)*10)",
		"1*2+3*4+6/2+8%3+9-8", 
		"70+80*9-10+(60+70+80*2-10)", 
		"(9-(4/2+1))*(5*2-2)", 
		"((80*87)/4)*2-705", 
		"100*((90-80+20*5)-(30*20-10/5))", 
		"(9-(4/2+1+(10*5)+7*6))*(50*20-10%2)", 
		"123+456*(789+(90-80+20*5)-(30*20-10/5))" };

	char postfix_expr[320] = { 0x00, };
	for (int i = 0; i < 13; i++)
	{
		printf("[%02d]-th 수식평가\n", i);
		if (testpair(infix_expr[i]) == 1)
			printf("괄호 개수가 일치함\n");
		else
			printf("괄호 개수가 불일치함\n");

		memset(postfix_expr, 0, sizeof(postfix_expr));

		init();
		infix_to_postfix(infix_expr[i], postfix_expr);

		printf("\n\ninfix: %s -> postfix: %s\n", infix_expr[i], postfix_expr);

		printf("후위 표기식 : %s", postfix_expr);

		result = evalPostfix(postfix_expr);
		printf("\n\n연산결과 => %d\n\n", result);
		freestack();
	}


}


int main()
{
	test1();
	test2();
	test3();
	getchar();
	return 0;
}