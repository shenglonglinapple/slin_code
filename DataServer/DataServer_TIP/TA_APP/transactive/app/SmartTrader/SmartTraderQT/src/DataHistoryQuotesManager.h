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
	void addReqest(QString strReqID, const CHistoryDataRequest* pReqest);
	void onHistoryDataDownloaded( QString requestID, pSetMyBarsPtr bars );
	void onBarDataUpdate(const CMyBarSummary &barData);

private:
	void _RemoveReq( QString strReqID );
	void _FreeData_MapRequest();
	void _FreeData_MapHistoryQuotes();
private:
	QMutex m_mutex_MapRequest;
	QMap<QString, CHistoryDataRequest*> m_MapRequest;//ReqID Data

	QMutex m_mutex_MapHistoryQuotes;
	QMap<unsigned int, CDataHistoryQuotes*> m_MapHistoryQuotes;//InstrumentID  Data

}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__



