#ifndef __CLASS_MYSTRING_HH__
#define  __CLASS_MYSTRING_HH__

#include <iostream>
#include <string>

class CMyString
{
public:
	//普通构造函数
	CMyString(const char* str = NULL);
	//拷贝构造函数
	CMyString(const CMyString& other);
	//析构函数
	virtual ~CMyString();
public:
	//赋值函数
	CMyString& operator=(const CMyString& other);
private:
	char* m_pData;
};



/*
在C++中当创建一个空类时，C++就会默认的为这个类创建4个函数：
默认的构造函数、析构函数、拷贝构造函数、以及赋值操作符。
*/
class CEmpty
{
public:
	//默认的构造函数
	CEmpty(){;}
	//默认的拷贝构造函数
	CEmpty(const CEmpty& rhs){;}
	//默认的析构函数
	virtual ~CEmpty(){;}
public:
	//默认的 赋值操作符
	CEmpty& operator=(const CEmpty& other){;}
	//取地址
	CEmpty* operator&(){return this;}
	//取地址的const 
	//返回值是const的 不能修改
	//this 指针是const 不能修改类成员的值 也不能调用非const的成员函数
	const CEmpty* operator&() const {return this;}
};


#endif //__CLASS_MYSTRING_HH__