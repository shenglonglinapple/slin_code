#ifndef __CLASS_MY_BAR_HH__
#define __CLASS_MY_BAR_HH__

//#pragma once
#include <set>
#include <list>
#include <map>
#include <memory>
#include <string>
#include "Bar.h"

class CHistoryData;


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class CMyBarTypeHeler
{
public:
	CMyBarTypeHeler();
	virtual ~CMyBarTypeHeler();
public:
	std::string getString_BarType(enum BarType nBarType);
	enum BarType getBarTypeByString(const std::string& strBarType );

};



class CMyBarsPtrHelper
{
public:
	CMyBarsPtrHelper();
	virtual ~CMyBarsPtrHelper();
public:
	BarsPtr convertValue(const std::list<CHistoryData*>& lstHistoryData);

};

#endif//__CLASS_MY_BAR_HH__

