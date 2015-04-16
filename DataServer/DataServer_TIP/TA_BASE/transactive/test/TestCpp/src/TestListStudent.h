#ifndef  __CLASS_TEST_LIST_STUDENT__HH__
#define  __CLASS_TEST_LIST_STUDENT__HH__

#include <iostream>
#include <string>
#include <stdio.h>
#include <string.h>
#include <conio.h>


#if 0

typedef struct student
{
	int data;
	struct student* next;
}node;

node* create()
{
	node* head = NULL;
	node* p = NULL;
	node* s = NULL;
	int x = 0;
	int cycle = 1;

	head = (node*)malloc(sizeof(node));
	p = head;
	while (cycle)
	{
		printf("\n please input the data:");
		scanf("%d", &x);
		if (x != 0)
		{
			s = (node*)malloc(sizeof(node));
			s->data = x;
			printf("\n %d", s->data);
			p->next = s;
			p = s;
		}
		else
		{
			cycle = 0;
		}
	}//while

	//head = head->next;
	p->next = NULL;
	printf("\n yyy %d", head->data);
	return head;
}

int length(node* head)
{
	int n = 0;
	node* p = NULL;
	p = head;
	while (p != NULL)
	{
		p = p->next;
		n++;
	}//while
	return n;
}

void print(node* head)
{
	node* p;
	int n;
}

node* del()
{

}

#endif

class CTestListStudent
{
public:
	CTestListStudent();
	~CTestListStudent();
public:
	void testMy_itoa();
	void testMy_atoi();
	char* testMy_strcpy(char* strDest, const char* strSrc);

	void stringcpy(char* to, const char* from);

	/*
	"12345678" "234"
	"2345678"
	*/
	const char* testMy_strstri(
		const char* strSrc,
		const char* strCharSet);
	void do_test_for_testMy_strstri();

	/*
	将一句话的单词进行倒置，标点符号不倒置。
	src="I come from tianjin."
	dest="tianjin. from come i"

	src="I come from tianjin."
	temp=".nijnait morf emoc I"
	dest="tianjin. from come i"
	*/
	void testMy_trunAroundString();
};

#endif//__CLASS_TEST_LIST_STUDENT__HH__



