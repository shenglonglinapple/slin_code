#ifndef __CLASS_DATA_USER_TRADE_HH__
#define __CLASS_DATA_USER_TRADE_HH__

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>


class CQtTimeHelper;
class CItemUserTrade;
class CItemUserTradeHelper;
class CUserTradeInfo;


class CDataUserTrade 
{ 
public:
	static CDataUserTrade& getInstance();
	static void removeInstance();

private:
	static CDataUserTrade* m_pInstance;
	static QMutex m_mutexInstance;
private: 
	CDataUserTrade(); 
	virtual ~CDataUserTrade(); 
public:
	void appendOrUpdate(CUserTradeInfo* pData);
public:
	CItemUserTrade* getRootItem();
	CUserTradeInfo* findNode(const QString& strTradeUUID);

private:
	void _FreeData();
	void addNode(const CUserTradeInfo* pData );
	void updateNode(const CUserTradeInfo* pData );
private:
	QMutex m_mutexForMapData;
	QMap<QString, CUserTradeInfo*> m_MapData;//strTradeUUID

	QMutex m_mutexForRoot;
	CItemUserTrade* m_pItem_Root;
	CItemUserTradeHelper* m_pItemDataHelper;
private:
	CQtTimeHelper* m_pQtTimeHelper;
}; 


//QT_END_NAMESPACE



#endif//__CLASS_DATA_USER_TRADE_HH__



