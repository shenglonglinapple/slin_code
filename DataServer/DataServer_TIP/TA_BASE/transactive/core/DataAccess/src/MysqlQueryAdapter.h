#ifndef MYSQLQUERYADAPTER_H
#define MYSQLQUERYADAPTER_H

#include "core/threads/src/ReEntrantThreadLockable.h"

#include "IQueryAdapter.h"

NS_BEGIN(sql)

class ResultSet;

NS_END(sql)


NS_BEGIN(TA_Base_Core)

class CAWorkTime;

class MysqlQueryAdapter : public IQueryAdapter
{
public:
	MysqlQueryAdapter( sql::ResultSet* pQuery );
	~MysqlQueryAdapter();
	
    bool hasMore();
	
    void fetchData( int numColumns, DbDataRowBuffers& data, long lMaxRows );
	
    bool cleanQuery();
	
	bool isActive( unsigned long ulMaxTimeoutInSecs );
	
	int getLstColumnName(MapColumNameIndexT& mapColumNameIndex);


private:
	void _FillDataBuffer( int numColumns, DbDataRowBuffers& data, long lMaxRows );
    void _UpdateLatestActionTime();

private:
    // Disable default constructor, copy constructor, operator =
    MysqlQueryAdapter();
    const MysqlQueryAdapter& operator=( const MysqlQueryAdapter& refSrc );
    MysqlQueryAdapter( const MysqlQueryAdapter& refSrc );
private:    
	sql::ResultSet*                       m_pQuery;
	int m_bHaveDoMoveFirst;
	TA_Base_Core::ReEntrantThreadLockable m_queryLock;
	CAWorkTime*							  m_pWorkTimeQueryAction;
};

NS_END(TA_Base_Core)


#endif /// MYSQLQUERYADAPTER_H











