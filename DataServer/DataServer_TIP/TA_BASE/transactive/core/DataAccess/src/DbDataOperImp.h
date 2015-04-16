#ifndef _CLASS_DB_DATA_OPER_IMP_H__
#define _CLASS_DB_DATA_OPER_IMP_H__

#include "core/DataAccess/src/DataAccessCommonData.h"
#include "core/DataAccess/src/IDbDataOper.h"

NS_BEGIN(TA_Base_Core)

class CDbStatusItem;
class IQueryAdapter;

class CDbDataOperImp : public IDbDataOper
{
public:
	CDbDataOperImp(CDbStatusItem* pDbStatusItem, IQueryAdapter* pQueryAdapter);
	virtual ~CDbDataOperImp();
public:
	void fetchData(int nFetchNum = FETCH_MAX_ROWS);
	std::string getStringData(const int rowIndex, const std::string& fieldName, const std::string defaultValue = "");
private:
	std::string _GetStringData(const int rowIndex, const std::string& fieldName);

private:
	CDbStatusItem* m_pDbStatusItem;
	IQueryAdapter* m_pQueryAdapter;
	MapColumNameIndexT m_MapColumnName;
	int m_nColumnNameCount;
	DbDataRowBuffers m_lstDbDataRowBuffers;

};//class CDbDataOperImp

NS_END(TA_Base_Core)

#endif //_CLASS_DB_DATA_OPER_IMP_H__



