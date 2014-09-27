#ifndef  __CLASS__MID_SUB_DAW_HELPER_H__
#define  __CLASS__MID_SUB_DAW_HELPER_H__

#include <iostream>


class CHistoryDataManager;
class QCustomPlot;
class QCPAxisRect;

class CMidSubDrawHelper
{
public:
	CMidSubDrawHelper();
	~CMidSubDrawHelper();
public:
	void drawHistoryBarData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect);
	void drawHistoryVolumeData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot, QCPAxisRect* pRect);
public:

};

#endif// __CLASS__MID_SUB_DAW_HELPER_H__



