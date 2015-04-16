#ifndef __I_DB_DATA_OPER_HH__
#define __I_DB_DATA_OPER_HH__


#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/DataAccessException.h"
#include <map>

NS_BEGIN(TA_Base_Core)

class IDbDataOper
{
public:
	typedef   std::map<std::string, int>               MapColumNameIndexT;
	typedef   std::map<std::string, int>::iterator     MapColumNameIndexIterT;
	typedef   std::map<std::string, int>::value_type   MapColumNameIndexValueT;

public:
	IDbDataOper()
	{
		return;
	}

	virtual ~IDbDataOper() 
	{
		return;
	}
public:
	virtual std::string getStringData(const int rowIndex, const std::string& fieldName, const std::string defaultValue = "") = 0;
public:
	virtual void fetchData(int nFetchNum = FETCH_MAX_ROWS) = 0;


};//IData

NS_END(TA_Base_Core)

#endif /// __I_DATA_HH__


