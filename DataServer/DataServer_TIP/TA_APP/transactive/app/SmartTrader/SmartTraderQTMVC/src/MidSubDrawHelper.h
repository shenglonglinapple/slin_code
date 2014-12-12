#ifndef  __CLASS__MID_SUB_DAW_HELPER_H__
#define  __CLASS__MID_SUB_DAW_HELPER_H__

#include <iostream>


class CHistoryQutoes;
class QCustomPlot;
class QCPAxisRect;
class CProjectLogHelper;

class CMidSubDrawHelper
{
public:
	CMidSubDrawHelper();
	~CMidSubDrawHelper();
public:
	void drawHistoryBarData(CHistoryQutoes* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect);
	void drawHistoryVolumeData(CHistoryQutoes* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect);
public:
	unsigned int getBottomTimeFrom();
	unsigned int getBottomTimeTo();

public:
	unsigned int m_nBottomTimeFrom;
	unsigned int m_nBottomTimeTo;
private:
	CProjectLogHelper* m_pProjectLogHelper;
};

#endif// __CLASS__MID_SUB_DAW_HELPER_H__



