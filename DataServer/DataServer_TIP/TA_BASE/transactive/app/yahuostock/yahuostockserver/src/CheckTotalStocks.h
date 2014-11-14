#ifndef __CLASS_CHECK_TOTAL_STOCKS_H__
#define __CLASS_CHECK_TOTAL_STOCKS_H__

#include <map>
#include <boost/thread.hpp>


class CStockData;

class CCheckTotalStocks 
{
private:
	enum workState
	{
		WorkState_Begin,
		WorkState_End
	};
private:
	//strSymbolUse  CStockData
	typedef std::map<std::string, CStockData*>                      MapStockDataItemT;
	typedef std::map<std::string, CStockData*>::iterator            MapStockDataItemIterT;
	typedef std::map<std::string, CStockData*>::value_type          MapStockDataItemValueTypeT;

public:
	CCheckTotalStocks();
	virtual ~CCheckTotalStocks();
public:
	void do_check();
private:
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
	void _FreeData_MapStockDataItemT_Total();
	void _FreeData_MapStockDataItemT_Good();
	void _FreeData_MapStockDataItemT_Bad();
	void _LoadData_MapStockDataItemT_Total();
	void _CheckTotalData();
	void _PrintBadData();
	int _Test_YahuoHistoryReqAck(const std::string& strSymbolUse);
private:
	workState  m_nWorkState;

	boost::mutex m_mutexMapStockDataItemT_Total;
	MapStockDataItemT m_MapStockDataItemT_Total;

	boost::mutex m_mutexMapStockDataItemT_Good;
	MapStockDataItemT m_MapStockDataItemT_Good;

	boost::mutex m_mutexMapStockDataItemT_Bad;
	MapStockDataItemT m_MapStockDataItemT_Bad;

};


#endif //__CLASS_YAHUO_HISTORY_REQACK_H__
