#ifndef __CLASS_STOCK_DATA_DB_ACTOR_H__
#define __CLASS_STOCK_DATA_DB_ACTOR_H__

#include <QtCore/QObject>
#include <QtCore/QDate>
#include <QtCore/QList>
#include "TcpComProtocol.h"


class CYahuoHistoryReqAck;
class CFileDBOperHelper;
class CSqliteDbOperHelper;
class CStockMinTimeMaxTime;
class CHistoryData;
class CSymbolUseManager;

class CStockDataDBActor : public QObject
{
    Q_OBJECT

public:
    CStockDataDBActor(const QString& strSymbolUse, QObject *parent = 0);
	virtual ~CStockDataDBActor();
signals:

public slots:
public:
	void saveData(const QString& strHistoryData);
	void getStockMinTimeMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet);
	int selectData(const QString & strFrom, const QString & strTo, QList<CHistoryData*>& lstData );
	void updateFailedCount( const QString& strSymbolUse);
	int select_TABLE_SYMBOLUSE_MANAGER(CSymbolUseManager** ppData);

private:
	void _Update_SymbolUseManager();
private:
	QString m_strSymbolUse;
private:
	CYahuoHistoryReqAck* m_pYahuoHistoryReqAck;
private:
	CFileDBOperHelper* m_pFileDBOperHelper;
	CSqliteDbOperHelper* m_pSqliteDbOperHelper;
};


#endif//__CLASS_STOCK_DATA_DB_ACTOR_H__
