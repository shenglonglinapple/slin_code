#ifndef __CLASS_REQ_DATA_HH__
#define __CLASS_REQ_DATA_HH__

#include <string>
#include "MyBar.h"

enum EReqType
{
	EReqType_Begin,
	EReqType_DownLoadStockID,
	EReqType_SubscribeMarketData,
	EReqType_UnSubscribeMarketData,
	EReqType_DownloadHistoryData,
	EReqType_End,
};



class CReqData
{
public:
	CReqData();
	virtual ~CReqData(void);
public:
	void setAutoRequestID();
	void setRequestID(unsigned int nRequestID);
	unsigned int getRequestID();
public:
	void setReqType(EReqType nReqType);
	EReqType getReqType();
public:
	void setInstrumentCode(const std::string& strInstrumentCode);
	std::string getInstrumentCode();
public:
	void setMyBarType(BarType nMyBarType);
	BarType getMyBarType();
	void setTimeFrom(const std::string& strTimeFrom);
	std::string getTimeFrom();
	void setTimeTo(const std::string& strTimeTo);
	std::string getTimeTo();
private:
	unsigned int m_nRequestID;
private:
	EReqType m_nReqType;
private:
	std::string m_strInstrumentCode;//"000001.SS"
private:
	std::string m_strTimeFrom;
	std::string m_strTimeTo;
private:
	BarType m_nMyBarType;
};



#endif//__CLASS_REQ_DATA_HH__

