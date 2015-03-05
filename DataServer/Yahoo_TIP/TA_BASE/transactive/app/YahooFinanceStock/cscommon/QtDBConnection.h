#ifndef   __CLASS_QT_DB_CONNECTION_HH__
#define	  __CLASS_QT_DB_CONNECTION_HH__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include <QtSql/QtSql>
#include <QtCore/QChar>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

#include "IDbConnection.h"

class IQueryAdapter;   // forward declare
class CAWorkTime;
class CDbStatusItem;

class CQtDBConnection : public IDbConnection
{
public:
	CQtDBConnection(const CDbStatusItem* pDbStatusItem);
	~CQtDBConnection();
public:
	bool isAnyQueryActive( unsigned long ulMaxTimeoutInSecs );
	QString getConnectionString() const;
	void open();
	bool isOpen();
	qint32 execQuery(const CSQLData& sqlData, IQueryAdapter*& pQueryAdapter);
	qint32 execModify( const CSQLData& sqlData );	
	qint32 execModifyBatch( const CSQLData& sqlData, const QList<QVariantList*>& LstData);

	qint32 commitTransaction();
	qint32 startTransaction();
	void incrementExecutionCount();
	void decrementExecutionCount();
	qint32 getExecutionCount();
	bool isHealth();
	void setConStatus(bool bIsHealth);
	void cleanQuery( IQueryAdapter*& pQueryAdapter );
private:
	void _CreateConnection();	
	void _CleanAllQuery();
	void _Close();
	bool _CheckAnyNotQueryActive( qint32 ulMaxTimeoutInSecs );
	QString _GetSQL(const CSQLData& sqlData);

private:
	QMutex m_lockConnection;
	QSqlDatabase* m_pConnection;
	CDbStatusItem* m_pDbStatusItem;

private:
	//this connection is last created time
	CAWorkTime*   m_pWorkTimeConnecion;
	//this connection exe one sql time
	CAWorkTime*   m_pWorkTimeUsingConnecion;
	//this connection is last exe time
	CAWorkTime*   m_pWorkTimeNotUsingConnecion;
	bool m_bIsHealth;
private:
	QMutex m_LockMapActiveQuery;// Enables thread guarding
	QMap<QString, IQueryAdapter*> m_mapActiveQuery;//CTcpComProtocol::getUUID()  

	QMutex m_LockExecutionCount;// Enables thread guarding
	qint32 m_nExecutionCount;
};



#endif /// __CLASS_QT_DB_CONNECTION_HH__











