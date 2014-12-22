#ifndef __CLASS_REQ_DATA_HH__
#define __CLASS_REQ_DATA_HH__

#include <string>
#include <QtCore/QString>
#include "MyBar.h"

enum EReqType
{
	EReqType_Begin,
	EReqType_DownLoadStockID,
	EReqType_SubscribeMarketData,
	EReqType_UnSubscribeMarketData,
	EReqType_DownloadHistoryData,
	EReqType_BUYMARKET,
	EReqType_SELLMARKET,
	EReqType_End,
};



class CReqData
{
public:
	CReqData();
	virtual ~CReqData(void);
public:
	void setAutoRequestUUID();
	QString getRequestUUID();
public:
	void setReqType(EReqType nReqType);
	EReqType getReqType();
public:
	void setInstrumentCode(const std::string& strInstrumentCode);
	std::string getInstrumentCode();
public:
	void setMyBarType(EMyBarType nMyBarType);
	EMyBarType getMyBarType();
	void setTimeFrom(const std::string& strTimeFrom);
	std::string getTimeFrom();
	void setTimeTo(const std::string& strTimeTo);
	std::string getTimeTo();
public:
	void setVolume(int nVolume);
	int getVolume();
private:
	QString m_strRequestUUID;
private:
	EReqType m_nReqType;
private:
	std::string m_strInstrumentCode;//"000001.SS"
private:
	std::string m_strTimeFrom;
	std::string m_strTimeTo;
private:
	EMyBarType m_nMyBarType;
private:
	int m_nVolume;
};



#endif//__CLASS_REQ_DATA_HH__

