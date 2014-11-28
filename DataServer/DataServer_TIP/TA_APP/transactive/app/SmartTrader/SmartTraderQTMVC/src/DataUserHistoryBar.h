#ifndef __CLASS_DATA_USER_HISTORY_BAR_HH__
#define __CLASS_DATA_USER_HISTORY_BAR_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "Account.h"
#include "Bar.h"

class CProjectLogHelper;
class CHistoryDataManager;
class CProjectUtilityFun;
class CSmartTraderClient;


class CDataUserHistoryBar
{ 
public:
	static CDataUserHistoryBar& getInstance();
	static void removeInstance();

private:
	static CDataUserHistoryBar* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserHistoryBar(); 
	virtual ~CDataUserHistoryBar(); 
private:
	void _Init();
	void _UniInit();
	void _FreeOldData(unsigned int nInstrumentID);

public:
	void createRequest_Time( unsigned int nInstrumentID, enum BarType nBarType, time_t timeFrom, time_t timeTo, CSmartTraderClient* pMyTradeClient);
	void createRequest_NumberSubscribe( unsigned int nInstrumentID, enum BarType nBarType, int nBarCount, bool bSubscribe, CSmartTraderClient* pMyTradeClient);
	void createRequest_NumberTimeSubscribe( unsigned int nInstrumentID, enum BarType nBarType, unsigned int nTimeFrom, int nBarCount, bool bSubscribe, CSmartTraderClient* pMyTradeClient);

public:
	void onBarDataUpdate( const BarSummary &barData );
	void onHistoryDataDownloaded( unsigned int requestID, BarsPtr bars, unsigned int& nGetInstrumentID);
	CHistoryDataManager* findByInstrumentID(unsigned int nInstrumentID);
private:
	QMutex m_mutexForMapHistoryData;
	QMap<unsigned int, CHistoryDataManager*> m_MapHistoryData;//instrumentID

private:
	CProjectLogHelper* m_pProjectLogHelper;
	CProjectUtilityFun* m_pProjectUtilityFun;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_USER_HISTORY_BAR_HH__



