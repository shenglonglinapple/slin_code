//http://blog.csdn.net/russell_tao/article/details/7167929
#include <iostream>
#include <string>

#include <iostream>
using namespace std;


////////////////////////////////////////////TTTT_0000__
#if 0


class Father
{
public:
	Father()
	{
		m_fMember=1;
		std::cout<<"Father() set m_fMember="<<m_fMember<<std::endl;
	}
	virtual ~Father() 
	{
		std::cout<<"virtual ~Father() m_fMember="<<m_fMember<<std::endl;
	}

public:
	void testFunc()
	{
		std::cout<<"Father void testFunc() m_fMember="<<m_fMember<<std::endl;
	}
	virtual void testVFunc()//虚函数表指针 4
	{
		std::cout<<"Father virtual void testVFunc() m_fMember="<<m_fMember<<std::endl;
	}
public:
	int m_fMember;//4
};

class Child : public Father
{
public:
	int m_nValue;//ok
	const int m_c_nValue;//ok
	static int m_s_nValue;//ok
	static const int m_s_c_nValue;//ok

	//int m_nValue_T = 0;//error!//only static const integral data members can be initialized within a class
	//const int m_c_nValue_T = 0;//error!// must be initialized in constructor base/member initializer list//only static const integral data members can be initialized within a class//
	//static int m_s_nValue_T = 0;//error!//only static const integral data members can be initialized within a class
	static const int m_s_c_nValue_T = 0;//ok
	int m_cMember;//4
public:
	Child():m_c_nValue(0)//ok
	{
		m_cMember=2;
		std::cout<<"Child() set m_cMember="<<m_cMember<<std::endl;
	}
	virtual ~Child()
	{
		std::cout<<"virtual ~Child() m_cMember="<<m_cMember<<std::endl;
	}
public:
	virtual void testVFunc()
	{
		std::cout<<"Child() virtual void testVFunc() m_cMember="<<m_cMember<<std::endl;

	}
	void testFunc()
	{
		std::cout<<"Child() void testFunc() m_cMember="<<m_cMember<<std::endl;
	}
	void testNFunc()
	{
		std::cout<<"Child() void testNFunc() m_cMember="<<m_cMember<<std::endl;
	}
};






int main()
{

	/*
	看看main函数里调用的五个test*Func方法吧，这里有静态的多态，也有动态的多态。编译是静态的，运行是动态的。以下解释C++编译器是怎么形成上述结果的。
	可以看到，第1、3次testFunc调用，其结果已经在编译出来的汇编语言中定死了
	编译完就已经决定出同一个API用哪种实现，这就是编译期的多态

第2、4次testVFunc调用则不然，编译完以后也不知道以后究竟是调用Father还是Child的testVFunc实现，
直到运行时，拿到CPU寄存器里的指针了，才知道这个指针究竟指向Father还是Child的testVFunc实现。这就是运行期的多态了。
	
	这里，m_fMember被Father的构造函数初始化为1，而m_cMember已经内存越界了！没错，在32位机器上，Father对象只有8个字节，而Child对象有12个字节，访问的m_cMember就是第9-12个字节转换成的int类型。通常情况，这段内存都是全0的，所以，m_cMember是0。看看结果：Child testFunc 0:1。
	
	然后它调用testVFunc了，这次执行父类还是子类的？是父类的，因为这个对象是Father对象，在new出来的时候，Father的构造函数会把vptl指针指向自己的testVFunc实现哟。所以将会执行C++代码
	*/

	Father* pRealFather = new Father();
	Child* pFalseChild = (Child*)pRealFather;
	Father* pFalseFather = new Child();

	std::cout<<"sizeof(Father)="<<sizeof(Father)<<std::endl;//8
	std::cout<<"sizeof(Child)="<<sizeof(Child)<<std::endl;//12


	pFalseFather->testFunc();//1//Father void testFunc() m_fMember=1
	pFalseFather->testVFunc();//2//Child() virtual void testVFunc() m_cMember=2

	pFalseChild->testFunc();//3//Child() void testFunc() m_cMember=-33686019
	pFalseChild->testVFunc();//4//Father virtual void testVFunc() m_fMember=1	
	pFalseChild->testNFunc();//5//Child() void testNFunc() m_cMember=-33686019	
/*
Father() set m_fMember=1
Father() set m_fMember=1
Child() set m_cMember=2
sizeof(Father)=8
sizeof(Child)=12
Father void testFunc() m_fMember=1
Child() virtual void testVFunc() m_cMember=2
Child() void testFunc() m_cMember=-33686019
Father virtual void testVFunc() m_fMember=1
Child() void testNFunc() m_cMember=-33686019


*/
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
#endif
////////////////////////////////////////////TTTT_0000__

////////////////////////////////////////////TTTT_0001__
#if 1
//sizeof(CPU)=4Bytes
//<4  max
//>4  4
class CTSizeofA
{
public:
	bool m_bTemp;
	int m_nTemp;
	bool m_bTemp2;
};//12

class CTSizeofB
{
public:
	double d;
	float a;
	int b;
	char c;

};//8




int main(int argc, char *argv[])
{
	int nFunRes = 0;
	int nSizeStdString = 0;
	int nCTSizeofA = 0;
	int nCTSizeofB = 0;

	nSizeStdString = sizeof(std::string);
	nCTSizeofA = sizeof(CTSizeofA);
	nCTSizeofB = sizeof(CTSizeofB);

	std::cout<<"nSizeStdString="<<nSizeStdString<<std::endl;
	std::cout<<"nCTSizeofA="<<nCTSizeofA<<std::endl;
	std::cout<<"nCTSizeofB="<<nCTSizeofB<<std::endl;

	return nFunRes;
}

#endif
////////////////////////////////////////////TTTT_0001__




