#ifndef __CLASS_STOCK_DATA_ACTOR_H__
#define __CLASS_STOCK_DATA_ACTOR_H__

#include <QtCore/QObject>
#include <QtCore/QString>
#include "TcpComProtocol.h"

class CStockDataDBActor;

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

public:
	void logInfo( const QString& fileName, qint32 lineNumber );
private:
	CStockDataDBActor* m_pStockDataDBActor;
};


#endif //__CLASS_STOCK_DATA_ACTOR_H__
