#ifndef  __CLASS_MY_CLASS_PROTECTED_HH__
#define  __CLASS_MY_CLASS_PROTECTED_HH__



#include <iostream>
#include <string>

class CMyClassProtectedA
{
public:
	CMyClassProtectedA(int nValue):m_nValue(nValue)
	{

	}
	~CMyClassProtectedA()
	{

	}
protected:
	int m_nValue;
};
class CMyClassProtectedB : public CMyClassProtectedA
{
public:
	CMyClassProtectedB(int nValue) : CMyClassProtectedA(nValue)
	{

	}
	~CMyClassProtectedB()
	{

	}
	//void fb(CMyClassProtectedA  &a) 
	//{
	//	std::cout<<a.m_nValue<<std::endl;//error C2248: 'CMyClassProtectedA::m_nValue' : cannot access protected member declared in class 'CMyClassProtectedA'
	//}
	void fb(CMyClassProtectedB  &b) 
	{
		std::cout<<b.m_nValue<<std::endl;//error C2248: 'CMyClassProtectedA::m_nValue' : cannot access protected member declared in class 'CMyClassProtectedA'
	}
};
#endif //__CLASS_MY_CLASS_PROTECTED_HH__

/*
C++中类访问权限控制：
第一：private, public, protected 访问标号的访问范围，在没有继承的情况下：
private：
只能由1.该类中的函数、2.其友元函数访问。
不能被任何其他访问，该类的对象也不能访问。
protected：
可以被1.该类中的函数、2.子类的函数、以及3.其友元函数访问。
但不能被该类的对象访问。
public：
可以被1.该类中的函数、2.子类的函数、3.其友元函数访问，也可以由4.该类的对象访问。
注：友元函数包括3种：设为友元的普通的非成员函数；设为友元的其他类的成员函数；设为友元类中的所有成员函数。
第二：类的继承后方法属性变化，具体情况如下：
private 属性是不能够被继承的，protected继承和private继承能降低访问权限。
使用private继承，父类的protected和public属性在子类中变为private；
使用protected继承，父类的protected和public属性在子类中变为protected；
使用public继承，父类中的protected和public属性不发生改变; 
如下所示： 
public:        protected:       private:
public继承          public        protected        不可用 
protected继承       protected     protected        不可用 
private继承         private       private          不可用 


class A
{
public:
A(int i) : a(i){}
protected:
int a;
};
class B : public A
{
public:
B(int i) : A(i) {}
void fb(A  &a) {cout<<a.a<<endl;}
};
编译出错；若将倒数第二行改为
void fb(B  &a) {cout<<a.a<<endl;}
则编译运行都没问题：
保护类型只能被本类中的方法或者派生类访问，不能被本类的具体对象访问。a是类A的保护类型成员，能被A中的方法（函数）访问，能被B类访问，不能被类A的具体对象A a访问。
一个类的保护成员或私有成员只能被该类的成员函数或该类的友元函数来访问，外部代码不能访问，B类中的函数fb对于A类中的保护成员变量a来说是外部代码不能通过该类的对象直接访问，由于B类公有继承了A类，a在A类中是保护成员，则在B类中也是保护成员，因此B类中的函数可以访问自己的保护成员。
*/

