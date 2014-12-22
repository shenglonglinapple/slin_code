#ifndef __CLASS_YAHUO_REALTIME_REQACK_H__
#define __CLASS_YAHUO_REALTIME_REQACK_H__

#include <list>
#include "YahuoReqAck.h"
class CYahuoRealTimeReqAck 
{
public:
	CYahuoRealTimeReqAck();
	virtual ~CYahuoRealTimeReqAck();
public:
	std::string getLatestQuotesCsv( const std::string &instruments, std::list<YahuoReqAck::QuoteType> quoteTypes);
	std::string getLatestQuotesCsv( const std::string &instruments, const std::string &quoteTypes);
public:
	void test_CYahuoRealTimeReqAck();
};


#endif //__CLASS_YAHUO_REALTIME_REQACK_H__
