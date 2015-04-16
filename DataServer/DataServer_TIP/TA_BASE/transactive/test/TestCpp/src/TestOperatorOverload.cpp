#include "TestOperatorOverload.h"

CTestOperatorOverload::CTestOperatorOverload()
{

}

CTestOperatorOverload::CTestOperatorOverload( double shibuValue, double xubuValue )
{
	shibu = shibuValue;
	xubu = xubuValue;
}

CTestOperatorOverload::~CTestOperatorOverload()
{

}

inline CTestOperatorOverload CTestOperatorOverload::operator+( const CTestOperatorOverload& object )
{
	return CTestOperatorOverload(shibu + object.shibu, xubu + object.xubu);
}

inline CTestOperatorOverload CTestOperatorOverload::operator-( const CTestOperatorOverload& object )
{
	return CTestOperatorOverload(shibu - object.shibu, xubu - object.xubu);
}

inline CTestOperatorOverload CTestOperatorOverload::operator*( const CTestOperatorOverload& object )
{
	return CTestOperatorOverload(shibu * object.shibu - xubu * object.xubu, shibu * object.shibu + xubu * object.xubu);
}

inline CTestOperatorOverload CTestOperatorOverload::operator/( const CTestOperatorOverload& object )
{
	return CTestOperatorOverload(
		(shibu * object.shibu + xubu * object.xubu)/(object.shibu * object.shibu + object.xubu * object.xubu), 
		(xubu * object.shibu - shibu * object.xubu)/(object.shibu * object.shibu + object.xubu * object.xubu));

}

void do_print( const CTestOperatorOverload& object )
{
	if (object.xubu < 0)
	{
		std::cout<<object.shibu<<object.xubu<<'i';
	}
	else
	{
		std::cout<<object.shibu<<'+'<<object.xubu<<'i';
	}
}


/*


void do_Test()
{
CTestOperatorOverload c1(1.0, 2.0);
CTestOperatorOverload c2(3.0, 4.0);
CTestOperatorOverload c3;

c3 = c1 + c2;
do_print(c3);

++c1;//这是一元操作
c1++;//这是二元操作
}
*/














