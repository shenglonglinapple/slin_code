#ifndef  __CLASS__HISTORY_DATA_MANAGER_H__
#define  __CLASS__HISTORY_DATA_MANAGER_H__

#include <iostream>
#include "HistoryDataRequest.h"
#include "HistoryDataACK.h"

class CHistoryQutoes
{
public:
	CHistoryQutoes();
	~CHistoryQutoes();
public:
	CHistoryDataRequest* m_pHistoryRequest;
	CHistoryDataACK* m_pHistoryACK;
public:
	void setHistoryDataRequest(const CHistoryDataRequest* pReq);
	int getBarType();
	unsigned int getTimeFrom();
	unsigned int getTimeTo();
public:
	void setInstrumentID(unsigned int nInstrumentID);
	unsigned int getInstrumentID();
public:
	unsigned int m_nInstrumentID;
	unsigned int m_nRequestID;
};

#endif// __CLASS__MY_BAR_SUMARY_H__



