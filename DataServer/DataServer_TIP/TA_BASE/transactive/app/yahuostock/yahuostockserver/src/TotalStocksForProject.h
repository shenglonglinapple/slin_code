#ifndef __CLASS_TOTAL_STOCKS_FOR_PROJECT_H__
#define __CLASS_TOTAL_STOCKS_FOR_PROJECT_H__

#include <map>
#include <boost/thread.hpp>


class CStockData;

class CTotalStocksForProject
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
	CTotalStocksForProject();
	virtual ~CTotalStocksForProject();
public:
	void do_init_data();

private:
	void _LoadData_MapStockDataItemT_Good();
	void _FreeData_MapStockDataItemT_Good();
	void _LoadData_MapStockDataItemT_UnKnown();
	void _FreeData_MapStockDataItemT_UnKnown();
	void _LoadData_MapStockDataItemT_Bad();
	void _FreeData_MapStockDataItemT_Bad();
	void _FreeData_MapStockDataItemT(MapStockDataItemT& mapStockData);
	
private:
	workState  m_nWorkState;

	boost::mutex m_mutexMapStockDataItemT_Good;
	MapStockDataItemT m_MapStockDataItemT_Good;


	boost::mutex m_mutexMapStockDataItemT_UnKnown;
	MapStockDataItemT m_MapStockDataItemT_UnKnown;

	boost::mutex m_mutexMapStockDataItemT_Bad;
	MapStockDataItemT m_MapStockDataItemT_Bad;

};


#endif //__CLASS_TOTAL_STOCKS_FOR_PROJECT_H__
