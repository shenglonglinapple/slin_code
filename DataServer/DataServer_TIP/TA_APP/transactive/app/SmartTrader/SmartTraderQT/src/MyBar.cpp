#include "MyBar.h"

#include "HistoryData.h"
#include "QtTimeHelper.h"

CMyBarTypeHeler::CMyBarTypeHeler()
{

}

CMyBarTypeHeler::~CMyBarTypeHeler()
{

}


std::string CMyBarTypeHeler::getString_BarType( enum EMyBarType nBarType )
{
	std::string strRes;

	switch (nBarType)
	{
	case FIVE_SECOND:
		strRes = "FIVE_SECOND";
		break;
	case TEN_SECOND:
		strRes = "TEN_SECOND";
		break;
	case FIFTEEN_SECEOND:
		strRes = "FIFTEEN_SECEOND";
		break;
	case THIRTY_SECOND:
		strRes = "THIRTY_SECOND";
		break;
	case MINUTE:
		strRes = "MINUTE";
		break;
	case FIVE_MINUTE:
		strRes = "FIVE_MINUTE";
		break;
	case FIFTEEN_MINUTE:
		strRes = "FIFTEEN_MINUTE";
		break;
	case THIRTY_MINUTE:
		strRes = "THIRTY_MINUTE";
		break;
	case ONE_HOUR:
		strRes = "ONE_HOUR";
		break;
	case DAY:
		strRes = "DAY";
		break;
	case WEEK:
		strRes = "WEEK";
		break;
	case MONTH:
		strRes = "MONTH";
		break;
	case YEAR:
		strRes = "YEAR";
		break;
	default:
		strRes = "UNKNOWN";
		break;
	}//switch

	return strRes;
}

enum EMyBarType CMyBarTypeHeler::getBarTypeByString(const std::string& strBarType )
{
	std::string strTemp;
	enum EMyBarType nBarType = FIVE_SECOND;

	strTemp = "FIVE_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = FIVE_SECOND;
		return nBarType;
	}

	strTemp = "TEN_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = TEN_SECOND;
		return nBarType;
	}

	strTemp = "FIFTEEN_SECEOND";
	if (strBarType == strTemp)
	{
		nBarType = FIFTEEN_SECEOND;
		return nBarType;
	}



	strTemp = "THIRTY_SECOND";
	if (strBarType == strTemp)
	{
		nBarType = THIRTY_SECOND;
		return nBarType;
	}

	strTemp = "MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = MINUTE;
		return nBarType;
	}


	strTemp = "FIVE_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = FIVE_MINUTE;
		return nBarType;
	}

	strTemp = "FIFTEEN_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = FIFTEEN_MINUTE;
		return nBarType;
	}


	strTemp = "THIRTY_MINUTE";
	if (strBarType == strTemp)
	{
		nBarType = THIRTY_MINUTE;
		return nBarType;
	}

	strTemp = "ONE_HOUR";
	if (strBarType == strTemp)
	{
		nBarType = ONE_HOUR;
		return nBarType;
	}


	strTemp = "DAY";
	if (strBarType == strTemp)
	{
		nBarType = DAY;
		return nBarType;
	}

	strTemp = "WEEK";
	if (strBarType == strTemp)
	{
		nBarType = WEEK;
		return nBarType;
	}

	strTemp = "MONTH";
	if (strBarType == strTemp)
	{
		nBarType = MONTH;
		return nBarType;
	}

	strTemp = "YEAR";
	if (strBarType == strTemp)
	{
		nBarType = YEAR;
		return nBarType;
	}


	return nBarType;
}


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CMyBar::CMyBar()
{

}

CMyBar::~CMyBar()
{

}

void CMyBar::setValue( const CHistoryData* pHistoryData )
{
	CQtTimeHelper timeHelper;
	this->timestamp = (unsigned int)timeHelper.strToDateTime_Qt(pHistoryData->m_strDate.toStdString());
	this->open = pHistoryData->m_strOpen.toDouble();
	this->high = pHistoryData->m_strHigh.toDouble();
	this->low = pHistoryData->m_strLow.toDouble();
	this->close = pHistoryData->m_strClose.toDouble();
	this->volume = pHistoryData->m_strVolume.toDouble();

}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
CMyBarsPtrHelper::CMyBarsPtrHelper()
{

}

CMyBarsPtrHelper::~CMyBarsPtrHelper()
{

}

CMyBarsPtr CMyBarsPtrHelper::convertValue( const std::list<CHistoryData*>& lstHistoryData )
{
	CMyBar MyBarData;

	CMyBarsPtr pMyBars(new CMyBars());  

	std::list<CHistoryData*>::const_iterator constIterLst;

	constIterLst = lstHistoryData.begin();
	while (constIterLst != lstHistoryData.end())
	{
		MyBarData.setValue(*constIterLst);
		pMyBars->insert(MyBarData);
		constIterLst++;
	}//while

	return pMyBars;
}
