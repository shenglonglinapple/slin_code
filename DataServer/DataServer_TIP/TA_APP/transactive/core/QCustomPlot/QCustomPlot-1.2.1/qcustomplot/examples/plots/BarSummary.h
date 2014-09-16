#ifndef  __DEF_CLASS_BAR_SUMMARY_HH__
#define  __DEF_CLASS_BAR_SUMMARY_HH__

#include <iostream>
#include <map>
#include "Bar.h"

class BarSumary
{
public:
	BarSumary();
	~BarSumary();
public:
	unsigned int instrumentID;
	std::map<int, Bar> bars; //bars indexed by interval
};

#endif// __DEF_CLASS_BAR_SUMMARY_HH__



