#ifndef   __CLASS_QT_DB_CONNECTION_HH__
#define	  __CLASS_QT_DB_CONNECTION_HH__


#include <QtSql/QtSql>
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QDir>
#include <QtCore/QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>


class IQueryAdapter;   // forward declare
class CAWorkTime;

class MysqlConnection : public IDbConnection
{
public:
	MysqlConnection(sql::Driver* pDriver, const CDbStatusItem& objDbStatusItem);
	~MysqlConnection();
	std::string getConnectionString() const;
	void open();	
	bool isOpen();
	void exec( const CSQLData& sqlData, IQueryAdapter*& pIQueryAdapter, bool isQuery = false, int prefetch = FETCH_MAX_ROWS);
	void incrementExecutionCount();
	void decrementExecutionCount();
	int getExecutionCount() { return m_nExecutionCount; };
    void cleanQuery( IQueryAdapter*& pQueryAdapter );
	bool isHealth();
	bool isAnyQueryActive( unsigned long ulMaxTimeoutInSecs );
	void setConStatus(bool bIsHealth);
private:
	CDbStatusItem* m_pDbStatusItem;
	void _CreateConnection();	
	void _GetSQL(std::string& strSql, const SQLStatement& rSqlObj);
	void _CleanAllQuery();
	void _Close();
	bool _CheckAnyNotQueryActive( unsigned long ulMaxTimeoutInSecs );
private:
	// Enables thread guarding
	TA_Base_Core::ReEntrantThreadLockable m_lockConnection;
	sql::Driver*     m_pDriver;
	sql::Connection* m_pConnection;


private:
	//this connection is last created time
	CAWorkTime*   m_pWorkTimeConnecion;
	//this connection exe one sql time
	CAWorkTime*   m_pWorkTimeUsingConnecion;
	//this connection is last exe time
	CAWorkTime*   m_pWorkTimeNotUsingConnecion;
	bool m_bIsHealth;
private:
	TA_Base_Core::ReEntrantThreadLockable m_LockMapActiveQuery;// Enables thread guarding
	std::map<IQueryAdapter*, long> m_mapActiveQuery;

	TA_Base_Core::ReEntrantThreadLockable m_LockExecutionCount;// Enables thread guarding
	unsigned long m_nExecutionCount;
};



#endif /// __CLASS_QT_DB_CONNECTION_HH__











