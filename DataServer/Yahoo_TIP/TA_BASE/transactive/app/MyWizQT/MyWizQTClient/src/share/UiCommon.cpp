#include "share/UiCommon.h"

static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_TopLeft = "SplitRectType_TopLeft";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Top = "SplitRectType_Top";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_TopRight = "SplitRectType_TopRight";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Left = "SplitRectType_Left";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Client = "SplitRectType_Client";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Right = "SplitRectType_Right";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_BottomLeft = "SplitRectType_BottomLeft";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Bottom = "SplitRectType_Bottom";
static const char*  DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_BottomRight = "SplitRectType_BottomRight";


CUiCommon::CUiCommon()
{

}

CUiCommon::~CUiCommon()
{

}

QString CUiCommon::getString( ESplitRectType nValue )
{
	QString strValue;

	switch (nValue)
	{
	case CUiCommon::SplitRectType_TopLeft:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_TopLeft;
		break;
	case CUiCommon::SplitRectType_Top:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Top;
		break;
	case CUiCommon::SplitRectType_TopRight:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_TopRight;
		break;
	case CUiCommon::SplitRectType_Left:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Left;
		break;
	case CUiCommon::SplitRectType_Client:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Right;
		break;
	case CUiCommon::SplitRectType_Right:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_BottomLeft;
		break;
	case CUiCommon::SplitRectType_BottomLeft:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_TopLeft;
		break;
	case CUiCommon::SplitRectType_Bottom:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_Bottom;
		break;
	case CUiCommon::SplitRectType_BottomRight:
		strValue = DEF_VALUE_CUiCommon_ESplitRectType_SplitRectType_BottomRight;
		break;
	default:
		strValue = "unknow";
		break;
	}//switch

	return strValue;
}

CUiCommon::ESplitRectType CUiCommon::getIntValue( int nValue )
{
	CUiCommon::ESplitRectType nType = SplitRectType_NULL;
	if (nValue < 0 || nValue > SplitRectType_NULL)
	{
		nType = SplitRectType_NULL;
		return nType;
	}
	nType = (CUiCommon::ESplitRectType)nValue;
	return nType;
}
