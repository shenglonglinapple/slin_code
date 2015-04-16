#include <iostream>
#include <string>
#include <stdio.h>

#include "TestConstMutable.h"

void testAddress()
{
	unsigned int a = 0xFFFFFFF7;
	unsigned char i = (unsigned char)a;
	char* b = (char*)&a;

	//int 4B
	//1B=8bit
	//4B=32bit
	//int a=2                       00000000 00000000 00000000 00000010

	//unsigned int a = 0xFFFFFFF7   11111111 11111111 11111111 11110111
	//

	/*
	在了解内存对齐方式前，先介绍计算机的存储方式：Big Endian与Little Endian：
	Big Endian   即数据的高位在低地址，地位在高地址，并且把最高字节的地址作为变量的首地址
	Little Endian 即数据的高位在高地址，数据的低位在低地址，并且把最低字节的地址作为变量首地址。
	现实中，某些基于RISC(精简指令集)的cpu比如SPARC、PowerPC等，采用Big Endian，
	而Intel系列cpu采用Little Endian。如果想要知道自己的电脑是什么存储格式只需要输入以下代码：
	*/
	printf("\n%08x, %08x\n", i, *b);



	char ch[]={0x12,0x34,0x56,0x78};
	int* p=(int*)ch;
	std::cout<<std::hex<<*p<<std::endl;//如果是78563412，说明是 Little Endian,如果是12345678，则是Big Endian


}

void testDuiQi()
{
	/*
	http://blog.csdn.net/tengweitw/article/details/8913566

	自然对齐：如果一个变量的内存地址正好位于它字节长度的整数倍，它就被称做自然对齐
	对于标准数据类型，它的地址只要是它的长度的整数倍，而非标准数据类型按下面的原则对齐：
	数组 ：按照基本数据类型对齐，只要第一个对齐后面的自然也就对齐。 
	联合 ：按其包含的长度最大的数据类型对齐。 
	结构体： 结构体中每个数据类型都要对齐。        

	字节对齐的好处：
	　  字节对齐的根本原因在于CPU访问数据的效率问题。学过微机原理的都知道规则字和非规则字，
	   8086cpu访问规则字只要一个周期，而访问非规则字需要两个周期。
	   在这里原理也是一样的，只不过这里是32位的操作系统，最多一次访问4字节，
	   而8086是16位的，一次最多访问2字节。
	   假设上面整型变量的地址是自然对齐，比如为0x00000000，
	   则CPU如果取它的值的话需要访问一次内存，一次直接取从0x00000000-0x00000003的一个int型，
	   如果变量在0x00000001，则第一次访问0x00000001的char型，
	   第二次取从0x00000002-0x00000003的short型，第三次是0x00000004的char型，
	   然后组合得到所要的数据，如果变量在0x00000002地址上的话则要访问两次内存，
	   第一次为short，第二次为short，然后组合得到整型数据。如果变量在0x00000003地址上的话，
	   则与在 0x00000001类似。 
	   */
	/*
	但 8086 / 8088 系统中的存储器是以 8 位(一个字节)为一个存储单物理地址存储器元编址的。
	每一个存储用唯一的一个地址码来表示。
	一个字即16位的数据占据连续的两个单元。这两个单元都有各自的地址，
	处于低地址的字节的地址为这个字的地址。
	在存储器中，任何连续存放的两个字节都可以称为一个字。
	将偶数地址的字称为规则字，奇数地址的字称为非规则字。
	高地址的字节为高位字节，低地址的字节为低位字节。
	若00000H地址中存放一个字 2301H， 则00000H单元中存放01H, 00001H单元中存放23H,
	字2301H为规则字，而字4523为非规则字。
	*/

	/*
	int a=0x0abcde11;//a b c 的地址依次减小  
	int b=0x012345678;  
	double c=0x0f23456789abcdef1;  
	char d=0x0fa;  

	char *ptr=(char*)&a;  
	printf("a b每个字节的内容：\n");  
	printf("  地址  :内容\n");  
	for(int i=0;i<8;i++)  
		printf("%x  :%x\n",ptr+3-i,*(ptr+3-i));//说明整数是按 little-endian存储的  


	printf("\na b c d的首地址和地址与字节长度的余值：\n");  
	printf("a: %x :%d\n",&a,long(&a)%sizeof(a));//从这里可以看成变量的内存地址按变量顺序递减的   
	printf("b: %x :%d\n",&b,long(&b)%sizeof(b));//各个变量并不一定存放在连续的内存单元  
	printf("c: %x :%d\n",&c,long(&c)%sizeof(c));  
	printf("d: %x :%d\n",&d,long(&d)%sizeof(d));  

	*/
}




void testSizeofClass()
{

	/*
	A是结构体，默认情况下，为了方便对结构体内部元素的访问和管理，
	当结构体内的元素的长度都小于处理器的位数的时候，便以结构体里面最长的数据元素为对齐单位，结构体的长度一定是最长的数据元素的整数倍。
	如果结构体内存在 长度大于处理器位数的元素，那么就以处理器的位数为对齐单位。
	CPU的优化规则大致原则是这样的：对于n字节的元素(n=2,4,8,...),它的首地址能被n整除，才能获得最好的性能。
	*/
	struct 
	{
		short a1;
		short a2;
		short a3;
	}A;
	int nsizeofValue = sizeof(A);//6


	/*
	在这里是按8字节边界来对齐的
	上述变量已经都自然对齐了，为什么person对象最后还要填充7字节？
	因为当你定义person类型的数组时，如果不填充7字节，
	则除了第一个元素外其它的元素就可能不是自然对齐了。
	*/
	class CPerson1  
	{  
		bool m_isMan;  
		float m_height;  
		bool m_isFat;  
		double m_weight;  
		unsigned char m_books;  
	};  
	int nSizeofPerson1 = 0;
	nSizeofPerson1 = sizeof(CPerson1);//32=4+4+8+8+8
	std::cout<<nSizeofPerson1<<std::endl;


	/*
	下面通过使用编译指令来定义对齐方式：
	*/
#pragma pack(push,4)// 按4字节边界对齐  
	class person2  
	{  
		bool m_isMan;  
		float m_height;  
		bool m_isFat;  
		double m_weight;  
		unsigned char m_books;  
	};  
	int nSizeofPerson2 = 0;
	nSizeofPerson2 = sizeof(person2);//24=4+4+4+8+4  
	std::cout<<nSizeofPerson2<<std::endl;
#pragma pack(pop)     

	/*
	从上面可以知道，内存的大小和存取的效率随编译方式和变量定义有关，最好的方法是：
	按照字节大小从大到小依次定义变量成员，并尽可能采用小的成员对齐方式。
	*/
	//按照从小到大字节长度来定义变量  
	class person4  
	{  
		bool m_isMan;  
		bool m_isFat;  
		unsigned char m_books;  
		float m_height;  
		double m_weight;  
	};  
	int nSizeofPerson4 = 0;
	nSizeofPerson4 = sizeof(person4);//16=1+1+1+1字节的填充+4+8  
	std::cout<<nSizeofPerson4<<std::endl;



	//按照从大到小字节长度来定义变量  
	class person3  
	{  
		double m_weight;  
		float m_height;  
		unsigned char m_books;  
		bool m_isMan;  
		bool m_isFat;  
	};  
	int nSizeofPerson3 = 0;
	nSizeofPerson3 = sizeof(person3);//16=8+4+1+1+1+1字节的填充   
	std::cout<<nSizeofPerson3<<std::endl;
	/*
	从上面可以看出两者所占内存一样，但是稳定度不同，从小到大的方式的对齐方式而发生有的成员变量不会自然对齐
	*/

#pragma pack(push,1)// 按4字节边界对齐  
	class person5  
	{  
		bool m_isMan;  
		bool m_isFat;  
		unsigned char m_books;  
		float m_height;  
		double m_weight;  
	};  
	int nSizeofPerson5 = 0;
	nSizeofPerson5 = sizeof(person5);//15=1+1+1+4+8    
	std::cout<<nSizeofPerson5<<std::endl;

#pragma pack(pop)  
	/*
	在上面的程序中，double的偏移量为1+1+1+4=7，很有可能不会自然对齐,所以最好采用从大到小的方式来定义成员变量
	*/
}


void testOperator()
{
	/*
	unsigned char a=0xA5;
	unsigned char b = ~a>>4+1;
	a 4 1  to int  then unsigned char to b
	~ > + > >>

	unsigned char b = ((~a)>>(4+1));
	vs2008  eax 是16位的寄存器
	a    0xA5    0000 0000 1010 0101
	~a           1111 1111 0101 1010
	~a>>5        0000 0111 1111 1010 1 1010
	~a>>5        0000 0111 1111 1010 

	1111 1010
	0000 0111

	unsigned char b = 1111 1010
	b= 128+64+32+16+8+0+2+0 = 250
	*/
	unsigned char a=0xA5;
	unsigned char b = ~a>>4+1;
	printf("\n b=%d\n", b);//vs2008 250



	/*X 2~N   
	2     10       2-1       01       10&01=00     
	4    100       4-1       011       100&011=000
	8   1000       8-1      0111      1000&0111=0000
	16 10000       16-1    01111      10000&01111=00000
	X & (X - 1) == 0

	*/

	/*
	x & y 取相同的位与 
	x ~ y 取x和y的不同位 右移相当于除以2
	(x & y) + ((x ~ y) >> 1)
	*/


}

void testSizeofClassTest2()
{
	class CTestA
	{
	public:
		bool m_bValueA;//4
		int m_nValueInt;//4
		bool m_bValueB;//4
	};//12

	class CTestB
	{
	public:
		int m_nValueInt;//big first//4
		bool m_bValueA;//1
		bool m_bValueB;//3
	};//8

	int nSizeofValue = 0;
	nSizeofValue = sizeof(CTestA);
	printf("sizeof CTestA = %d \n", nSizeofValue);//vs2008 12 Byte   96bit

	nSizeofValue = sizeof(CTestB);
	printf("sizeof CTestB = %d \n", nSizeofValue);//vs2008 8 Byte    64bit


	/*
	//静态变量是存放在全局数据区， sizeof计算栈中分配的大小
	*/
	class A1
	{
	public:
		A1(){}
		~A1(){}
		int a;//4
		//static int b;// error C2246: 'testSizeofClassTest2::A1::b' : illegal static data member in locally defined class
	};//4
	nSizeofValue = sizeof(A1);
	printf("sizeof A1 = %d \n", nSizeofValue);//vs2008 4 Byte   32bit  

	class A2
	{
	public:
		int a;//4
		char c;//4
	};//8
	nSizeofValue = sizeof(A2);
	printf("sizeof A2 = %d \n", nSizeofValue);//vs2008 8 Byte   64bit  


	class A3
	{
	public:
		float a;//4
		char c;//4
	};//8
	nSizeofValue = sizeof(A3);
	printf("sizeof A3 = %d \n", nSizeofValue);//vs2008 8 Byte   64bit  


	class A4
	{
	public:
		float a;//4
		int b;//4
		char c;//4
	};//12
	nSizeofValue = sizeof(A4);
	printf("sizeof A4 = %d \n", nSizeofValue);//vs2008 12 Byte   96bit  


	class A5
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//8 考虑数组问题
	};//24
	nSizeofValue = sizeof(A5);
	printf("sizeof A5 = %d \n", nSizeofValue);//vs2008 24 Byte  192bit  

	class A6
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//4
		int nValue;//4
	};//24
	nSizeofValue = sizeof(A6);
	printf("sizeof A6 = %d \n", nSizeofValue);//vs2008 24 Byte  192bit  

	class A7
	{
	public:
		double d;//8
		float a;//4
		int b;//4
		char c;//8
		double fValue;//8
	};//32
	nSizeofValue = sizeof(A7);
	printf("sizeof A7 = %d \n", nSizeofValue);//vs2008 32 Byte  256bit  


}


void testFunStringArray()
{
	//To output "TrendMicroSoftUSCN"
	std::string strArri[] = {"Trend", "Micro", "Soft"};
	std::string* pStrArri = new std::string[2];
	double* pDouble = new double[10];
	pStrArri[0] = "US";
	pStrArri[1] = "CN";

	std::cout<<"sizeof(strArri)="<<sizeof(strArri)<<std::endl;//60
	std::cout<<"sizeof(std::string)="<<sizeof(std::string)<<std::endl;//20
	std::cout<<"sizeof(pStrArri)="<<sizeof(pStrArri)<<std::endl;//4
	std::cout<<"sizeof(*pStrArri)="<<sizeof(*pStrArri)<<std::endl;//20
	std::cout<<"sizeof(pDouble)="<<sizeof(pDouble)<<std::endl;//4
	std::cout<<"sizeof(*pDouble)="<<sizeof(*pDouble)<<std::endl;//8


	//sizeof(strArri)=12
	for (int nIndex = 0; nIndex < sizeof(strArri)/sizeof(std::string); nIndex++)
	{
		std::cout<<strArri[nIndex];
	}

	/*
	for (int nIndexj = 0; nIndexj < sizeof(pStrArri)/sizeof(std::string); nIndexj++)
	{
	std::cout<<pStrArri[nIndexj];
	}
	sizeof(pStrArri)=4=sizeof(std::string*)
	*/
	for (int nIndexj = 0; nIndexj < sizeof(*pStrArri)*2/sizeof(std::string); nIndexj++)
	{
		std::cout<<pStrArri[nIndexj];
	}	

	std::cout<<std::endl;
}


void testFunSizeofClassTest3()
{
	class Base
	{
	public:
		virtual void f(int nValue)
		{
			std::cout<<"Base::f(int nValue)"<<std::endl;
		}

		virtual void f(double fValue)
		{
			std::cout<<"Base::f(double fValue)"<<std::endl;
		}

		virtual void g(int nValue = 10)
		{
			std::cout<<"Base::g(int nValue = 10)"<<std::endl;
		}
		virtual void g2(int nValue = 10)
		{
			std::cout<<"Base::g2(int nValue = 10)"<<std::endl;
		}

		/*
		var[] 等价于 *var 已经退化为一个指针了，大小是4
		*/
		int test(char var[])
		{
			return sizeof(var);
		}
	};

	class Derived : public Base
	{
	public:
		Derived()
		{
			std::cout<<"Derived-ctor"<<std::endl;
		}

		~Derived()
		{
			std::cout<<"Derived-dtor"<<std::endl;
		}


		virtual void g(int nValue = 20)
		{
			std::cout<<"Derived::g(int nValue = 20)"<<nValue<<std::endl;
		}
	};


	Base b;
	Derived d;

	Base* pb = new Derived();

	std::cout<<"sizeof(Base)="<<sizeof(Base)<<std::endl;//4  sizeof(指针)
	std::cout<<"sizeof(Derived)="<<sizeof(Derived)<<std::endl;//4  sizeof(指针)



	/*
	为什么会出现这种结果呢？初学者肯定会很烦恼是吗？类a，b明明是空类，它的大小应该为为０，为什么　编译器输出的结果为１呢？这就是我们刚才所说的实例化的原因（空类同样可以被实例化），每个实例在内存中都有一个独一无二的地址，为了达到这个目的，编译器往往会给一个空类隐含的加一个字节，这样空类在实例化后在内存得到了独一无二的地址．所以a，b的大小为１．
	而类c是由类a派生而来，它里面有一个纯虚函数，由于有虚函数的原因，有一个指向虚函数的指针（vptr），在３２位的系统分配给指针的大小为４个字节，所以最后得到c类的大小为４．
	类d的大小更让初学者疑惑吧，类d是由类b，c派生迩来的，它的大小应该为二者之和５，为什么却是８　　呢？这是因为为了提高实例在内存中的存取效率．类的大小往往被调整到系统的整数倍．并采取就近的法则，里哪个最近的倍数，就是该类的大小，所以类d的大小为８个字节．
	当然在不同的编译器上得到的结果可能不同，但是这个实验告诉我们初学者，不管类是否为空类，均可被实例化（空类也可被实例化），每个被实例都有一个独一无二的地址．
	*/
	class A
	{

	};//1 /*空类所占的空间为1*/
	class A2
	{

	};//1
	class B : public A
	{

	};//1
	class C : public virtual B
	{

	};//4  /*虚继承涉及虚表（虚指针）*/

	class D :  public A
	{
		virtual void fun()=0;
	};//4  /*虚继承涉及虚表（虚指针）*/

	class E :  public A
	{
		virtual void fun(){}
	};//4  /*虚继承涉及虚表（虚指针）*/

	class F : public E, public A2
	{

	};//8

	std::cout<<"sizeof A="<<sizeof(A)<<std::endl;//1
	std::cout<<"sizeof A2="<<sizeof(A2)<<std::endl;//1
	std::cout<<"sizeof B="<<sizeof(B)<<std::endl;//1
	std::cout<<"sizeof C="<<sizeof(C)<<std::endl;//4
	std::cout<<"sizeof D="<<sizeof(D)<<std::endl;//4
	std::cout<<"sizeof E="<<sizeof(E)<<std::endl;//4
	std::cout<<"sizeof F="<<sizeof(F)<<std::endl;//8


	/*
	内联函数和宏的差别是什么？
	内联函数和普通函数相比可以加快程序的运行的速度，因为不需要中断调用，
	在编译的时候内联函数可以直接被镶嵌到目标代码中。而宏只是一个简单的替换。
	内联函数要做参数类型检查，这是内联函数跟宏相比的优势。
	inline是指嵌入代码，就是在调用函数的地方不是跳转，而是把代码直接写到那里去。
	inline一般用于：一个函数不断被重复调用； 函数只有简单的几行，且函数内不包含for,while,switch语句

	inline fac(float nIndex) { return nIndex * nIndex;} //没有写返回值的
	printf("bb=%d", fac(8));   //调用时就是执行 printf("bb=%d", 8*8);
	*/



}

void testPointerBase1()
{
	/*
	一个数据对象的内存地址称为该数据对象的指针。
	指针可以表示各种数据对象，如简单变量、数组、数组元素、结构体、函数。
	包括 常量指针，数组指针，函数指针，this指针，指针传值，指向指针的指针。
	*/
	/*
	指针和引用的差别？
	1、非空区别。在任何情况下都不能使用指向空值的引用。一个引用必须总是指向某些对象。
	因此如果你使用一个变量并让它指向一个对象，但是该变量在某些时候也可能不指
	向任何对象，这时你应该把变量声明为指针，因为这样你可以赋空值给该变量。相反，如果
	变量肯定指向一个对象，例如你的设计不允许变量为空，这时你就可以把变量声明为引用。
	不存在指向空值的引用这个事实意味着使用引用的代码效率比使用指针要高。
	2、合法性区别。在使用引用之前不需要测试它的合法性。相反，指针则应该总是被测试，防止其为空。
	3、可修改区别。指针可以被重新赋值以指向另一个不同的对象。但是引用则总是指向在初始化时被指定的对象，
	以后不能改变，但是指定的对象其内容可以改变。
	4、应用区别。 使用指针：一，考虑到存在不指向任何对象的可能，可以设置指针为空。
	二，需要能够在不同的时刻指向不同的对象，改变指针的指向。
	如果总是指向一个对象并且一旦指向一个对象后就不会改变指向，那么应该使用引用。
	*/
}

void testMemoryMalloc()
{
	float *p = NULL;
	while(1)
	{
		p = new float[10000000];
		std::cout<<"eat memory"<<std::endl;
		if ( p == NULL )
		{
			exit(1);
		}
	}
}

void testPointerSubtractionPointer()
{
	/*
	加法 Addition 
	减法 Subtraction 
	乘法 Multiplication 
	除法 Division	
	*/


	int a[3];
	a[0] = 0;
	a[1] = 1;
	a[2] = 2;
	int *p, *q;
	p = a;//p = a[0]
	std::cout<<p<<'\n';
	std::cout<<*p<<'\n';
	q=&a[2];
	std::cout<<q<<'\n';
	std::cout<<*q<<'\n';
	std::cout<<a[q - p]<<'\n';
	std::cout<<a[*q - *p]<<'\n';

	/*
	p的实际地址 0x22FF70
	q的实际地址 0x22FF78
	0x22FF78 - 0x22FF70 = 0x000008
	q-p的实际运算是  （q的地址值(0x22FF78) - p的地址值(0x22FF70)) / (sizeof(int)) = 2

	*/
}

void testConstPointerConst()
{
	//函数指针
	//void (*f) ();
	//函数返回指针
	//void* f();
	//const 指针
	//const int* p;
	//指向const的指针
	//int* const p;
	//指向const的const 指针
	//const int* const;

	/*
	“常量指针”和“指针常量”这两个概念。
	其实简单一点讲，“常量指针”所指向的地址上的数据是常量，
	而“指针常量”所指向的地址是常量，地址上面的数据是可以变化的。
	char *str1={"Hello"};
	char *str2={"Hello World"};
	char * const ptr1 =str1 ;
	char szStrOne[] =  {"aaaaaa"};//栈
	//指针常量－－指针本身是常量，指向的地址不可以变化,但是指向的地址所对应的内容可以变化
	ptr1 =szStrOne; //错误 因为这是一个常量指针，改变指向的地址了

	*ptr1 ='A';// 正确 因为指向的地址的内容是可以变化的


	const char *ptrTmp2 = str1;
	//常量指针－－指向字符串常量，所指向的字符串内容不能变，但是指向的地址可以变化
	ptrTmp2=szStrOne;// 正确 因为指向的地址是可以变化的
	*ptrTmp2='A';// 错误 因为指向的地址是内容是不可以变化的


	相信从上面四个简单的例子可以看出他们不一样的地方把，在这里要请大家注意一下的地方是：

	指针常量的申明：const 放在* 和指针名之间 Type * const pointer ;

	常量指针的申明：const放在类型说明符之前 const Type *pointer ;
	*/

	char *str1={"Hello"};//常量区
	char *str2={"Hello World"};
	char szStrOne[] =  {"aaaaaa"};//栈
	char * const ptr1 =szStrOne ;
	//指针常量－－指针本身是常量，指向的地址不可以变化,但是指向的地址所对应的内容可以变化
	*ptr1 ='A';// 正确 因为指向的地址的内容是可以变化的
	printf("%c \n",*ptr1);

}


void testFunPointerTest1()
{
	/*
	Write in words the data type of the identifier involved in the following definitions.
	1. float(**def)[10];
	def是个二级指针，它指向的是一个一维数组的指针，数组的元素都是float.
	2.double*(*gh)[10];
	gh是一个指针，它指向一个一维数组，数组元素都是double*
	3.double(*f[10])();
	f是一个数组，f有10个元素，元素都是函数的指针，指向的函数类型是没有参数且返回double的函数。
	4.int*((*b)[10]);
	就跟"int*(*b)[10]" 是一样的，是一维数组的指针，
	b是一个指针，它指向一个一维数组，数组元素都是double*
	5. Long (*fun)(int)
	函数指针，指向的函数类型是参数为int,返回long的函数。
	6.int(*(F)(int, int))(int)
	F是一个函数的指针，指向的函数的类型是有两个int参数并且返回一个函数指针的函数，
	返回的函数指针指向有一个int参数并且返回int的函数。
	*/
	{
		int v[2][10] = {{1,2,3,4,5,6,7,8,9,10},{11,12,13,14,15,16,17,18,19,20}};
		int (*a)[10] = v;//数组指针 a是一个指针，指向一个10个元素的数组，数组元素为int
		/*
		a+1表明a指针向后移动  1*sizeof(数组大小)   40Byte
		*a+1 仅针对这一行向后移动4个字节，
		*/

		std::cout<<"**a = "<<**a<<std::endl;//1
		std::cout<<"**(a+1) = "<<**(a+1)<<std::endl;//11
		std::cout<<"*(*a+1) = "<<*(*a+1)<<std::endl;//2
		std::cout<<"*(a[0]+1) = "<<*(a[0]+1)<<std::endl;//2
		std::cout<<"*(a[1]) = "<<*(a[1])<<std::endl;//11
	}
	/*
	int (*ptr)[] 是一个指向整型数组的指针。
	int *ptr[] 是指针数组， ptr[]里面存的是地址。它指向位置的值就是*ptr[0], *ptr[1]
	int *(ptr[]) 和 int *ptr[] 相同
	int ptr[] 是一个整型数组
	*/

	/*
	int *a[] 是指针数组 a是指针数组，是指一个数组里面装着指针
	int (*a)[] 是一个指向整型数组的指针。
	*/

	{
		static int a[2] = {1, 2};
		int *ptr[5];//指针数组
		int p = 5;
		int p2 = 6;
		int *page = NULL;
		int *page2 = NULL;
		page = &p;
		page2 = &p2;
		ptr[0] = &p;
		ptr[1] = page2;
		std::cout<<"*ptr[0] = "<<*ptr[0]<<std::endl;//5
		std::cout<<"*page = "<<*page<<std::endl;//5
		std::cout<<"*ptr[1] = "<<*ptr[1]<<std::endl;//6

		//测试用二维数组
		int Test[2][3] = {{1,2,3},{4,5,6}};
		//测试用一维数组
		int Test2[3] = {1,2,3};
		page = &p;
		page2 = &p2;
		ptr[0] = &p;
		ptr[1] = page2;
		//int (*A)[3] = &Test[1];
		//数组指针
		int (*AA) [3];
		int (*BB) [3];
		AA = &Test[1];
		BB = &Test2;
		std::cout<<"*page = "<<*page<<std::endl;//5
		std::cout<<"(*AA)[0] = "<<(*AA)[0]<<std::endl;//4
		std::cout<<"(*AA)[1] = "<<(*AA)[1]<<std::endl;//5
		std::cout<<"(*AA)[2] = "<<(*AA)[2]<<std::endl;//6
		std::cout<<"(*BB)[3] = "<<(*BB)[3]<<std::endl;//-858993460
	}

}

void testPointerTypes()
{
	/*
	如果该面试者没有为这次面试做好准备，那么他又能为什么做好准备呢？
	*/
	//一个整型数
	//int a;//An interger
	//一个指向整型数的指针
	//int *a;//A pointer to an integer
	//一个指向指针的指针，它指向的指针是指向一个整型数
	//int **a;//A pointer to a pointer to an integer
	//一个有10个整型数的数组
	//int a[10];//An array of 10 integers
	//一个有10个指针的数组，该指针是指向一个整型数的
	//int *a[10];//An array of 10 pointers to integers
	//一个指向有10个整型数数组的指针
	//int (*a)[10];//A pointer to an array of 10 integers
	//一个指向函数的指针，该函数有一个整型参数并返回一个整型数
	//int (*a)(int);//A pointer to a function that takes an integer argument and returns an interger
	//一个有10个指针的数组，该指针指向一个函数，该函数有一个整型参数并返回一个整型数
	//int (*a[10])(int);//An array of 10 pointers to functions that take an integer argument
	//return an integer

	/*
	数组名本身就是指针，再加一个&,就变成了双指针，这里的双指针就是指二维数组，
	加1，就是数组整体加一行，ptr指向a的第6个元素
	*/
}

void test_TestConstMutable()
{
	RunTest_CTestConstMutable runTest;
	RunTest_CTestConstMutable runTest2(runTest);
	runTest2 = runTest;
	runTest.do_Test();


}

void test_struct_Test()
{
	struct Test
	{
		Test(int) 
		{
	
		}
		
		Test()
		{

		}

		void fun()
		{

		}
	};

	Test a(1);
	a.fun();
	//Test b();//error
	//b.fun();//error C2228: left of '.fun' must have class/struct/union
	

}

void test_convert_type_printf()
{
	/*
	5 int  4Byte
	%f   double 8Byte  stack内存访问越界
	*/
	printf("%f\n", 5);//0.000000
	printf("%d\n", 5.01);//1889785610 一个大数

	/*
	static_cast
	const_cast 去除const属性
	dynamic_cast   不是强制转换，可能返回NULL
	reinterpret_cast
	*/

	int firstNumber = 2;
	int secondNumber = 1;
	double resultR = static_cast<double>(firstNumber)/secondNumber;

	class CTestB
	{
	public:
		int m_iNum;
	};
	CTestB b0;
	b0.m_iNum = 100;
	const CTestB b1 = b0;//
	//b1.m_iNum = 100;//编译失败， m_iNum是常量对象，不能对它进行修改//error C3892: 'b1' : you cannot assign to a variable that is const
	const_cast<CTestB&>(b1).m_iNum = 200;//ok
	//编译器隐式执行任何类型的转换都可由static_cast显示完成
	int n = 9;
	double d = static_cast<double>(n);


}

void test_Virtual_fun_class()
{
	class A
	{
	public:
		//虚函数 动态机制
		virtual void foo()
		{
			std::cout<<"A foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"A pp"<<std::endl;
		}
	};

	class B : public A
	{
	public:
		void foo()
		{
			std::cout<<"B foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"B pp"<<std::endl;
		}
		void FunctionB()
		{
			std::cout<<"B FunctionB"<<std::endl;
		}
	};

	B b;
	A* pa = &b;
	pa->foo();//由于存在多态，因此调用B::foo()
	pa->pp();//调用A::pp()
	(dynamic_cast<B*>(pa))->FunctionB();
}

void test_pointer_int()
{
	int *pa = NULL;//0x00 00 00 00
	int *pb = pa + 15;//15 * sizeof(int) = 15 * 4 = 60   0x3C
	printf("\n %x \n", pb);//0x00 00 00 3C
}

void test_const_volatile_type()
{
	/*
	const意味着 只读

	const int a;//a是一个常整型数 不可修改值的整型数
	int const a;//a是一个常整型数 不可修改值的整型数
	const int* a;//a是一个指向常整型数的指针 整型数不可修改，指针可修改
	int* const a;//a是一个指向整型数的常指针  整型数可修改，指针不可修改
	int const* a const;//a是一个指向常整型数的常指针  整型数不可修改，指针不可修改
	*/

	/*
	关键字volatile
	一个定义为volatile的变量是说这变量可能会被意想不到的改变，
	这样，编译器就不会去假设这个变量的值了。精确的说，就是，
	优化器在用到这个变量时必须每次都小心地重新读取这个变量的值，
	而不是使用保存在寄存器里的备份。
	例子：
	->并行设备的硬件寄存器(如 状态寄存器).
	->一个中断服务子程序中会访问到的非自动变量(Non-automatic variables)
	->多线程应用中被几个任务共享的变量
	*/
	/*
	一个参数可以既是const又是volatile的，一个例子就是只读的状态寄存器。
	它是volatile,因为它可能被意想不到的改变；
	它是const的，因为程序不应该试图去修改它。
	一个指针可以是volatile,一个例子是当一个中断服务子程序修改一个指向一个buffer的指针时
	*/

	/*
	要求设置一绝对地址为 0x000067a9 的整型变量的值为0x0000aa66;
	
	int* ptr = NULL;
	ptr = (int *)0x000067a9;//typecast一个整型数强制转换为一个指针
	*ptr = 0x0x0000aa66;

	*(int* const)(0x000067a9) = 0x0000aa66;
	*/
		
	/*
	关键字static的作用是什么？
	在C语言中，static的关键字至少有下列作用：
	->函数体内static变量的作用范围为该函数体，不同于auto变量，该变量的内存只被分配一次，因此其值在下次调用时仍维持上次的值。
	->在模块内的static全局变量可以被模块内所有函数访问，但不能被模块外其他函数访问。
	->在模块内的static函数只可被这一模块内的其他函数调用，这个函数的使用范围被限制在声明它的模块内。
	->在类中的static成员变量属于整个类所拥有，对类的所有对象只有一份拷贝。
	->在类中的static成员函数属于整个类所拥有，这个函数不接收this指针，因而只能访问类的static成员变量
	*/

	/*
	static的作用主要有以下3个：
	1、扩展生存期；
	2、限制作用域；
	3、唯一性；
	*/
}

void test_Little_endian_Big_endian()
{
	/*
	Little_endian 小尾
	0x12 34 56 78
	内存地址   存放的内容
	0x4000     0x78
	0x4001     0x56
	0x4002     0x34
	0x4003     0x12

	Big_endian  大尾
	0x12 34 56 78
	内存地址   存放的内容
	0x4000     0x12
	0x4001     0x34
	0x4002     0x56
	0x4003     0x78
	*/
}


void test_dynamic_cast()
{
	class ClassA
	{
	public:
		//1
		virtual void foo()
		{
			std::cout<<"ClassA foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"ClassA pp"<<std::endl;
		}
	};

	class ClassB : public ClassA
	{
	public:
		void foo()
		{
			std::cout<<"ClassB foo"<<std::endl;
		}
		void pp()
		{
			std::cout<<"ClassB pp"<<std::endl;
		}
		void FunctionB()
		{
			std::cout<<"Excute FunctionB"<<std::endl;
		}
	};

	ClassA a;//use CLASSB b;
	ClassA* pa = &a;
	pa->foo();
	pa->pp();
	ClassB* pB = NULL;
	//2
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->FunctionB();
	pB = (dynamic_cast<ClassB*>(pa));//->FunctionB();
	pB->FunctionB();//ok   "Excute FunctionB"   not use any memberdata or virtual fun, not use this pointor
	/*因为FunctionB和pp的函数未使用任何成员数据，也不是虚函数，不需要this指针，也不需要动态绑定，可以正常运行 */
	//4
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->pp();
	pB = (dynamic_cast<ClassB*>(pa));//->pp();
	pB->pp();//ok   "ClassB pp"
	(*pa).foo();//"ClassA foo"

	//3
	pB = NULL;
	//pB = (dynamic_cast<ClassB*>(pa))->foo();
	pB = (dynamic_cast<ClassB*>(pa));
	pB->foo();//error   vitrual table


}//test_dynamic_cast


//page 180
int main(int agrc, char** argv)
{

	// 	testAddress();
	// 	testDuiQi();
	// 	testSizeofClass();
	// 	testOperator();
	// 	testSizeofClassTest2();
	// 	testFunStringArray();
	// 	testFunSizeofClassTest3();
	//	testPointerSubtractionPointer();
	//	testConstPointerConst();
	//testFunPointerTest1();
	//test_TestConstMutable();
	//test_convert_type_printf();
	//test_pointer_int();
	test_dynamic_cast();

	return 0;
}




