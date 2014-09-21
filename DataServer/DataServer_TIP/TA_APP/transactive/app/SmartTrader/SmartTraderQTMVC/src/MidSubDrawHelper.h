#ifndef  __CLASS__MID_SUB_DAW_HELPER_H__
#define  __CLASS__MID_SUB_DAW_HELPER_H__

#include <iostream>


class CHistoryDataManager;
class QCustomPlot;

class CMidSubDrawHelper
{
public:
	CMidSubDrawHelper();
	~CMidSubDrawHelper();
public:
	void drawHistoryBarData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot);
	void drawHistoryVolumeData(CHistoryDataManager* pHistoryDataManager, QCustomPlot* pCustomPlot);
public:

};

#endif// __CLASS__MID_SUB_DAW_HELPER_H__



