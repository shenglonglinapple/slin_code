#ifndef __CLASS_MY_BAR_HH__
#define __CLASS_MY_BAR_HH__

//#pragma once
#include <set>
#include <list>
#include <map>
#include <memory>
#include <string>

class CHistoryData;


enum EMyBarType 
{
	FIVE_SECOND = 5,
	TEN_SECOND = 10,
	FIFTEEN_SECEOND = 15,
	THIRTY_SECOND = 30,
	MINUTE = 60,
	FIVE_MINUTE = 5 * MINUTE,
	FIFTEEN_MINUTE = 15 * MINUTE,
	THIRTY_MINUTE = 30 * MINUTE,
	ONE_HOUR = 60 * MINUTE,
	DAY = ONE_HOUR * 24,
	WEEK = DAY * 7,
	MONTH = DAY * 30,
	YEAR = DAY * 365
};

class CMyBar
{
public:
	CMyBar();
	~CMyBar();
public:
	/// Lowest price within the time span
	double low;

	/// Highest price within the time span
	double high;

	/// First traded price within the time span
	double open;

	/// Last traded price within the time span
	double close;

	/// Total volume within the time span
	double volume;

	/// Time of the bar
	unsigned int timestamp;
};

inline bool operator<(const CMyBar& lhs, const CMyBar &rhs) 
{
	return lhs.timestamp < rhs.timestamp;
}


typedef std::set<CMyBar> setMyBars;
typedef std::auto_ptr<setMyBars> pSetMyBarsPtr;

class  CMyBarSummary
{
public:
	CMyBarSummary();
	~CMyBarSummary();
public:
	unsigned int instrumentID;
	std::map<int, CMyBar> bars; //bars indexed by interval
};

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

class CMyBarTypeHeler
{
public:
	CMyBarTypeHeler();
	virtual ~CMyBarTypeHeler();
public:
	std::string getString_BarType(enum EMyBarType nBarType);
	enum EMyBarType getBarTypeByString(const std::string& strBarType );

};



class CMyBarsPtrHelper
{
public:
	CMyBarsPtrHelper();
	virtual ~CMyBarsPtrHelper();
public:
	pSetMyBarsPtr convertValue(const std::list<CHistoryData*>& lstHistoryData);

};

#endif//__CLASS_MY_BAR_HH__

