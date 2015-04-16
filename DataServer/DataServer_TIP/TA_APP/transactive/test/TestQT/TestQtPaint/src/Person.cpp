#include <iostream>
#include "Person.h"


struct CPersonData  // 定义私有数据成员类型
{
	std::string mszName; // 姓名
	bool mbSex;    // 性别
	int mnAge;     // 年龄
};

// constructor
CPerson::CPerson ()
{
	d = new CPersonData;
};

// destructor
CPerson::~CPerson ()
{
	delete d;
};

void CPerson::setAge(const int age)
{
	if (age != d->mnAge)
		d->mnAge = age;
}

int CPerson::getAge()
{
	return d->mnAge;
}