#ifndef  __CLASS_TEST_OPERATOR_OVERLOAD__HH__
#define  __CLASS_TEST_OPERATOR_OVERLOAD__HH__

#include <iostream>
#include <string>
#include <stdio.h>
#include <typeinfo>



	/*
	算术运算符：  +,-,*,/,%,++,--;
	位操作运算符: &,|,~,^,<<,>>;
	逻辑运算符: !,&&,||;
	比较运算符：<,>, >=,<=,==,!=
	赋值运算符: =,+=,-=,*=,/=,%=,&=,!=,^=,<<=,>>=;
	其他运算符: [], (), ->, , new, delete, new[], delete[],->*.
	下列运算符不允许重载:
	. .*  :: ?:

	*/

class CTestOperatorOverload
{
private:
	double shibu;
	double xubu;
public:
	CTestOperatorOverload();
	CTestOperatorOverload(double shibuValue, double xubuValue);
	~CTestOperatorOverload();

public:
	CTestOperatorOverload operator+(const CTestOperatorOverload& object);
	CTestOperatorOverload operator-(const CTestOperatorOverload& object);
	CTestOperatorOverload operator*(const CTestOperatorOverload& object);
	CTestOperatorOverload operator/(const CTestOperatorOverload& object);

	friend void do_print(const CTestOperatorOverload& object);

public:
	void operator++()//这是一元操作
	{
		int a = 1;
	}
	void operator++(int)//这是二元操作
	{
		int a = 1;
	}
};


#endif//__CLASS_TEST_OPERATOR_OVERLOAD__HH__