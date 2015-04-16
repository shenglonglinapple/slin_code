#ifndef IQUERYADAPTER_H
#define IQUERYADAPTER_H


#include "core/DataAccess/src/DataAccessCommonData.h"

NS_BEGIN(TA_Base_Core)

class IQueryAdapter
{
public:
	typedef   std::map<std::string, int>               MapColumNameIndexT;
	typedef   std::map<std::string, int>::iterator     MapColumNameIndexIterT;
	typedef   std::map<std::string, int>::value_type   MapColumNameIndexValueT;

public:
	IQueryAdapter()
	{
		return;
	}
	virtual ~IQueryAdapter() 
	{
		return;
	}

	virtual bool hasMore() = 0;
		
	virtual void fetchData( int numColumns, DbDataRowBuffers& data, long lMaxRows ) = 0;
		
	virtual bool cleanQuery() = 0;
		
	virtual bool isActive( unsigned long ulMaxTimeoutInSecs ) = 0;

public:
	virtual int getLstColumnName(MapColumNameIndexT& mapColumNameIndex) = 0;



};  // end of class IQueryAdapter

NS_END(TA_Base_Core)  // end of namespace TA_Base_Core

#endif  /// IQUERYADAPTER_H









