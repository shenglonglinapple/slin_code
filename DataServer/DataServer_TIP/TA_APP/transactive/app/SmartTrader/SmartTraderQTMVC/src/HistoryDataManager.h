#ifndef  __CLASS__HISTORY_DATA_MANAGER_H__
#define  __CLASS__HISTORY_DATA_MANAGER_H__

#include <iostream>
#include "HistoryDataRequest.h"
#include "HistoryDataACK.h"

class CHistoryDataManager
{
public:
	CHistoryDataManager();
	~CHistoryDataManager();
public:
	CHistoryDataRequest* m_pHistoryRequest;
	CHistoryDataACK* m_pHistoryACK;
public:
	int getBarType();
	unsigned int getTimeFrom();
	unsigned int getTimeTo();
public:
	void setInstrumentID(unsigned int nInstrumentID);
	unsigned int getInstrumentID();
private:
	unsigned int m_nInstrumentID;
};

#endif// __CLASS__MY_BAR_SUMARY_H__



