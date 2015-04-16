#ifndef   __CLASS_MYSQL_CONNECTION_HH__
#define	  __CLASS_MYSQL_CONNECTION_HH__

#include "core/DataAccess/src/DataAccessCommonData.h"

#include "core/DataAccess/src/IDbConnection.h"


NS_BEGIN(sql)
class Driver;
class Statement;
class Connection;
NS_END(sql)

NS_BEGIN(TA_Base_Core)

class IQueryAdapter;   // forward declare
class CAWorkTime;

class MysqlConnection : public IDbConnection
{
public:
	/**
	* MysqlConnection
	* 
	* Sole constructor that stores the database connection details and 
	* allocates handles to perform transactions with the database.
	* Note: this method can be unsuccessful, so checkIsValid() should be 
	* called afterwards to check that construction was successful.
	* 
	* @param connectionStr databaseName:userName:password:hostName
	* @param databaseName  the name of the database to connect to
	* @param userName      the name of the user for the session
	* @param password      the name of the password for the session
	* @param hostName      the name of the host that the database is on
	*/
	MysqlConnection(sql::Driver* pDriver, const CDbStatusItem& objDbStatusItem);

	/**
	* ~MysqlConnection
	* 
	* Sole standard destructor. Frees the handles allocated in the constructor.
	*/
	~MysqlConnection();


	/**
	* getConnectionString
	*
	* Returns the connection string for this OCIConnection.
	*
	* @return std::string  the connection string in the form
	*                      databaseName:userName:password:hostName
	*/
	std::string getConnectionString() const;

	/**
	* open
	*
	* Starts a new session with the database if there is not one already 
	* running.
	*
	* @exception DBException Thrown if there is an OCI error.
	*/
	void open();
		
	bool isOpen();
		
		
	/**
	* exec
	*
	* Executes the given statement on the database.  This method
	* handles both queries (e.g. "SELECT...") and non-queries (e.g."INSERT...")
	*
	* @param statement    the statement to execute
	* @param isQuery      a bool that is true if the statement is a query
	* @param numColumns   the number of columns to retrieve
	* @param bindType     the type of binding required
	* @exception DBException Thrown if there is an OCI error.
    */
	void exec( const SQLStatement& rSqlObj, IQueryAdapter*& pIQueryAdapter, bool isQuery = false, int prefetch = FETCH_MAX_ROWS);


	/**
	* incrementExecutionCount
	*
	* Increment the count of threads that are using this connection right now.
	* Note: The count does not include threads that have this connection open, 
	* but are not executing on it right now.
	*/
	void incrementExecutionCount();
		
        
	/**
	* decrementExecutionCount
	*
	* Decrement the count of threads that are using this connection right now.
	* Note: The count does not include threads that have this connection open,
	* but are not executing on it right now.
	*/
	void decrementExecutionCount();
		
	/**
	* getExecutionCount
	*
	* Get the count of threads that are using this connection right now.
	* Note: The count does not include threads that have this connection open,
	* but are not executing on it right now.
	*/
	int getExecutionCount() { return m_nExecutionCount; };
	
	/**
	* isConnectionInUse
	*
	* Checks if the connection is still being used.  This involves checking
	* if the execution count is non-zero or if there are any statements 
	* that have more data to be fetched.  Note: this only returns true
	* if there is a thread that is partway through a transaction on this
	* connection - not just if they have an open link to this connection.
	*
	* @return bool     True if the connection is being used at the moment.
	*                  False otherwise.
	*/
//	bool isConnectionInUse();

	//static void cleanUpQuery(ocl::OraQuery*& Query);
    void cleanQuery( IQueryAdapter*& pQueryAdapter );

	bool isHealth();

	bool isAnyQueryActive( unsigned long ulMaxTimeoutInSecs );

	void setConStatus(bool bIsHealth);
private:
	CDbStatusItem* m_pDbStatusItem;
	/**
	* createConnection
	* 
	* creates the underlying framework to support a session
	*/
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


	// use map for faster find method
	TA_Base_Core::ReEntrantThreadLockable m_LockMapActiveQuery;// Enables thread guarding
	std::map<IQueryAdapter*, long> m_mapActiveQuery;


	// The count of threads that are using this connection right now.
	// The count does not include threads that have this connection open,
	// but are not executing on it right now (ie. m_usageCount)	
	TA_Base_Core::ReEntrantThreadLockable m_LockExecutionCount;// Enables thread guarding
	unsigned long m_nExecutionCount;
};

NS_END(TA_Base_Core)

#endif /// __CLASS_MYSQL_CONNECTION_HH__











