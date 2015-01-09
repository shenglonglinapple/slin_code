#ifndef __CLASS_STOCK_DATA_DB_ACTOR_H__
#define __CLASS_STOCK_DATA_DB_ACTOR_H__

#include <QtCore/QObject>
#include <QtCore/QDate>
#include "TcpComProtocol.h"


class CRequestYahuoDataHelper;
class CYahuoHistoryReqAck;
class CFileDBOperHelper;
class CSqliteDbOperHelper;

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

private:
	QString m_strSymbolUse;
private:
	CYahuoHistoryReqAck* m_pYahuoHistoryReqAck;
	CRequestYahuoDataHelper* m_pRequestYahuoDataHelper;
private:
	CFileDBOperHelper* m_pFileDBOperHelper;
	CSqliteDbOperHelper* m_pSqliteDbOperHelper;
};


#endif//__CLASS_STOCK_DATA_DB_ACTOR_H__
