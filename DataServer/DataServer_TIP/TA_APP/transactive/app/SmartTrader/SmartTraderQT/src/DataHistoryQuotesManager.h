#ifndef __CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__
#define __CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "MyBar.h"

class CHistoryDataRequest;

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
private:
	CHistoryDataRequest* _TryGetReq(unsigned int requestID);
	void _RemoveReq( unsigned int requestID );
private:
	QMutex m_mutex_MapRequest;
	QMap<unsigned int, CHistoryDataRequest*> m_MapRequest;


}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_HISTORY_QUOTES_MANAGER_HH__



