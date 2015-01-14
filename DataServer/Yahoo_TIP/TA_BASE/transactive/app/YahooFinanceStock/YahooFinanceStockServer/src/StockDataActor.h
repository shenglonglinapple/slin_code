#ifndef __CLASS_STOCK_DATA_ACTOR_H__
#define __CLASS_STOCK_DATA_ACTOR_H__

#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtCore/QList>
#include "TcpComProtocol.h"

class CStockDataDBActor;
class CStockMinTimeMaxTime;
class CHistoryData;

class CStockDataActor : public QObject
{
	Q_OBJECT
public:
	CStockDataActor(QObject* parent=0);
	virtual ~CStockDataActor();
public:
	QString  m_strSymbolUse;//m_strSymbol+m_strSymbolExtern
public:
	void setValue(const QString& strSymbol,	const QString& strSymbolExtern);
public:
	void saveData(const QString& strHistoryData);
	void getStockMinTimeMaxTime( const QString& strSymbolUse, CStockMinTimeMaxTime** ppValueGet);
	int selectData(const QString & strFrom, const QString & strTo, QList<CHistoryData*>& lstData );

public:
	void logInfo( const QString& fileName, qint32 lineNumber );
private:
	CStockDataDBActor* m_pStockDataDBActor;
};


#endif //__CLASS_STOCK_DATA_ACTOR_H__
