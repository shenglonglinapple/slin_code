#ifndef __CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__
#define __CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "MyBar.h"

class CHistoryDataRequest;
class CDataHistoryQuotes;

class CDataHistoryQuotesManager
{ 
public:
	static CDataHistoryQuotesManager& getInstance();
	static void removeInstance();

private:
	static CDataHistoryQuotesManager* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataHistoryQuotesManager(); 
	virtual ~CDataHistoryQuotesManager(); 

public:
	void addReqest(unsigned int nReqID, const CHistoryDataRequest* pReqest);
	void onHistoryDataDownloaded( unsigned int requestID, CMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);

private:
	void _RemoveReq( unsigned int requestID );
	void _FreeData_MapRequest();
	void _FreeData_MapHistoryQuotes();
private:
	QMutex m_mutex_MapRequest;
	QMap<unsigned int, CHistoryDataRequest*> m_MapRequest;//ReqID Data

	QMutex m_mutex_MapHistoryQuotes;
	QMap<unsigned int, CDataHistoryQuotes*> m_MapHistoryQuotes;//InstrumentID  Data

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__



