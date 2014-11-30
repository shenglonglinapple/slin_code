#ifndef __CLASS_INSTRUMENT_BAR_INFO_REQUEST_H__
#define __CLASS_INSTRUMENT_BAR_INFO_REQUEST_H__ 


#include "CFDServerCommonData.h"
#include "BarCalculator.h"

QT_BEGIN_NAMESPACE


class CInstrumentBarInfoRequest
{
public:
	CInstrumentBarInfoRequest(void);	
	~CInstrumentBarInfoRequest(void);

public:
	CInstrumentBarInfoRequest& operator=(const CInstrumentBarInfoRequest& cfdRequest);

public:
	void logInfo(const std::string& strLogInfo);
	void getLstBarTime(std::list<int>& lstBarTime);
	void setValueByCfg();
private:
	void _AddBarTimeNormal();

public:
	//c://Hisdata   20131220
	std::string m_strHistoryDataDirectory;

	//C://SaveData//SaveDataBar   3320.BAR
	std::string m_strSaveDataDirectoryBAR;

	//C://SaveData//SaveDataTIK   3320.TIK
	std::string m_strSaveDataDirectoryTIK;

	time_t m_nStartTime;
	DbServerType m_nDBType;

	AutoRunType m_nAutoRun;
	/*2014-02-02 02:00:01  just need 02:00:01*/
	std::string m_strAutoRunTime24Clock;

public:
	//c://Hisdata//20131220
	std::string m_strCurrentAnalierFileName;	
	
private:
	std::list<int>   m_lstBarTime;
};


QT_END_NAMESPACE


#endif // __CLASS_INSTRUMENT_BAR_INFO_REQUEST_H__









