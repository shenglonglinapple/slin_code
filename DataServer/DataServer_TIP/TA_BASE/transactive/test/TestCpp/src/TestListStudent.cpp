#include "TestListStudent.h"

#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <string.h>


CTestListStudent::CTestListStudent()
{

}

CTestListStudent::~CTestListStudent()
{

}


void CTestListStudent::testMy_itoa()
{
	/*
	整数转化成字符串，可以采用加 '0'，再逆序
	*/
	int num = 12345;
	int j = 0;
	int nindex = 0;
	char temp[7] = {0};
	char str[7] = {0};
	//itoa(number, string, 10);

	while (0 != num)
	{
		temp[nindex] = (num % 10) + '0';
		nindex++;
		num = (num / 10);		
	}//while
	temp[nindex] = 0;
	//printf(" temp=%s\n", temp);
	//
	nindex = nindex - 1;
	j = 0;
	while (nindex >= 0)
	{
		str[j] = temp[nindex];
		j++;
		nindex--;
	}//while (nindex >= 0)
	str[j] = 0;
	//printf(" str=%s\n", str);

}

void CTestListStudent::testMy_atoi()
{
	int num = 12345;
	int j = 0;
	int i = 0;
	int sum = 0;
	char temp[7] = {'1', '2', '3', '4', '5','\0'};
	char str[7] = {0};

	i = 0;
	sum = 0;
	while (temp[i])
	{
		sum = (sum * 10) + (temp[i] - '0');
		i++;
	}//while (temp[i])
	printf("  sum=%d \n", sum);
}



char* CTestListStudent::testMy_strcpy( char* strDest, const char* strSrc )
{
	assert(NULL != strDest);
	assert(NULL != strSrc);
	assert((NULL != strSrc) && (NULL != strDest));
	char* address = strDest;
	while (*strSrc != '\0')
	{
		*strDest = *strSrc;
		strDest++;
		strSrc++;
	}
	*strDest = '\0';
	
	/*
	char* address = strDest;
	while ((*strDest++=*strSrc++)!= '\0')
	NULL;
	*/

	/*
	为了实现链式表达式，返回具体的值
	int length = strlen(testMy_strcpy(strDest, "hello world"));
	*/
	return address;

	
}

void CTestListStudent::stringcpy( char* to, const char* from )
{
	assert(NULL != to && NULL != from);
	while (*from != '\0')
	{
		*to++ = *from++;
	}//while
	*to = '\0';

	/*
	char* f = NULL;
	char* t = NULL;
	f = (char*)malloc(15);
	t = (char*)malloc(15);
	stringcpy(f, "asdfghjkl");
	stringcpy(t, t);


	*/

	//int n=10, a[n];
}

const char* CTestListStudent::testMy_strstri( const char* strSrc, const char* strCharSet )
{
	int nIndexI = 0;

	for (nIndexI = 0; strSrc[nIndexI] != '\0'; nIndexI++)
	{
		int nIndexJ = 0;
		int temp = nIndexI;
		if (strSrc[nIndexI] == strCharSet[nIndexJ])
		{
			while (strSrc[nIndexI++] == strCharSet[nIndexJ++])
			{
				if (strCharSet[nIndexJ] == '\0')
				{
					return &strSrc[nIndexI - nIndexJ];
				}

			}//while

			nIndexI = temp;
		}//if

	}//for

	return NULL;

}

void CTestListStudent::do_test_for_testMy_strstri()
{
	char* strSrc = "12345554555123";
	std::cout<<strSrc<<std::endl;
	char strCharSet[10] = {};
	std::cin>>strCharSet;
	std::cout<<testMy_strstri(strSrc, strCharSet)<<std::endl;
	char* string2=strstr("12345554555123", "234");
	std::cout<<string2<<std::endl;
}

void CTestListStudent::testMy_trunAroundString()
{
	
}

