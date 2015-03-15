//http://blog.csdn.net/russell_tao/article/details/7167929
#include <iostream>
#include <string>

#include <iostream>
using namespace std;

class Father
{
public:
	Father()
	{
		m_fMember=1;
	}
	virtual ~Father() 
	{

	}

public:
	void testFunc()
	{
		cout<<"Father testFunc "<<m_fMember<<endl;
	}
	virtual void testVFunc()
	{
		cout<<"Father testVFunc "<<m_fMember<<endl;
	}
public:
	int m_fMember;
};

class Child : public Father
{
public:
	int m_cMember;
public:
	Child()
	{
		m_cMember=2;
	}
	virtual ~Child()
	{

	}
public:
	virtual void testVFunc()
	{
		cout<<"Child testVFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
	void testFunc()
	{
		cout<<"Child testFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
	void testNFunc()
	{
		cout<<"Child testNFunc "<<m_cMember<<":"<<m_fMember<<endl;
	}
};


int main()
{
	Father* pRealFather = new Father();
	Child* pFalseChild = (Child*)pRealFather;
	Father* pFalseFather = new Child();

	/*
	看看main函数里调用的五个test*Func方法吧，这里有静态的多态，也有动态的多态。编译是静态的，运行是动态的。以下解释C++编译器是怎么形成上述结果的。
	可以看到，第1、3次testFunc调用，其结果已经在编译出来的汇编语言中定死了
	编译完就已经决定出同一个API用哪种实现，这就是编译期的多态

第2、4次testVFunc调用则不然，编译完以后也不知道以后究竟是调用Father还是Child的testVFunc实现，
直到运行时，拿到CPU寄存器里的指针了，才知道这个指针究竟指向Father还是Child的testVFunc实现。这就是运行期的多态了。
	
	这里，m_fMember被Father的构造函数初始化为1，而m_cMember已经内存越界了！没错，在32位机器上，Father对象只有8个字节，而Child对象有12个字节，访问的m_cMember就是第9-12个字节转换成的int类型。通常情况，这段内存都是全0的，所以，m_cMember是0。看看结果：Child testFunc 0:1。
	
	然后它调用testVFunc了，这次执行父类还是子类的？是父类的，因为这个对象是Father对象，在new出来的时候，Father的构造函数会把vptl指针指向自己的testVFunc实现哟。所以将会执行C++代码
	*/
	pFalseFather->testFunc();//1//Father testFunc 1
	pFalseFather->testVFunc();//2//child

	pFalseChild->testFunc();//3//Child testFunc -33333:1
	pFalseChild->testVFunc();//4//father	
	pFalseChild->testNFunc();//5//child	

	return 0;
}


//int main(void)
//int main()
//int main(int argc, char *argv[])
// int main(int argc, char *argv[])
// {
// 	int nFunRes = 0;
// 
// 	return nFunRes;
// }




