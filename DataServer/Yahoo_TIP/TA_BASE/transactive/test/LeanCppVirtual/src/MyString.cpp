#include "MyString.h"

CMyString::CMyString( const char* str /*= NULL*/ )
{
	m_pData = NULL;
	if (NULL == str)
	{
		m_pData = new char[1];
		(*m_pData) = '\0';
	}
	else
	{
		int nLength = 0;
		nLength = strlen(str);
		m_pData = new char[nLength + 1];
		strcpy(m_pData, str);//
	}
}
/*
因为拷贝构造函数是放在本身这个类里的，
而类中的函数可以访问这个类的对象的所有成员，当然包括私有成员了。
引用参数对象也是String类的，所以没问题

问题（知识点）描述： 
a． 在C++的类的成员函数中，允许直接访问该类的对象的私有成员变量。 
b． 在类的成员函数中可以访问同类型实例的私有变量。 
c． 拷贝构造函数里，可以直接访问另外一个同类对象（引用）的私有成员。 
d． 类的成员函数可以直接访问作为其参数的同类型对象的私有成员。 
*/
CMyString::CMyString( const CMyString& other )
{
	int nLength = 0;
	nLength = strlen(other.m_pData);
	m_pData = NULL;
	m_pData = new char[nLength + 1];
	strcpy(m_pData, other.m_pData);//
}

CMyString::~CMyString()
{
	if (NULL != m_pData)
	{
		//由于m_pData是内部数据类型，也可以写成delete m_pData;//malloc/free new/delete
		delete[] m_pData;
		m_pData = NULL;

	}
}

CMyString& CMyString::operator=( const CMyString& other )
{
	//检查自赋值
	if (this == &other)
	{
		return *this;
	}
	//free memory first
	if (NULL != m_pData)
	{
		delete[] m_pData;
		m_pData = NULL;
	}

	int nLength = 0;
	nLength = strlen(other.m_pData);
	m_pData = NULL;
	m_pData = new char[nLength + 1];
	strcpy(m_pData, other.m_pData);//
	return *this;
}

