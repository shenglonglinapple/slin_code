#ifndef __CLASS_UI_COMMON_H__
#define __CLASS_UI_COMMON_H__

#include <QtCore/QString>

class CUiCommon
{
public:
	CUiCommon();
	~CUiCommon();
public:
	enum ESplitRectType 
	{
		SplitRectType_TopLeft = 0,
		SplitRectType_Top = 1, 
		SplitRectType_TopRight = 2,
		SplitRectType_Left = 3, 
		SplitRectType_Client = 4, 
		SplitRectType_Right = 5, 
		SplitRectType_BottomLeft = 6, 
		SplitRectType_Bottom = 7, 
		SplitRectType_BottomRight = 8,

		SplitRectType_NULL
	};
public:
	static QString getString(ESplitRectType nValue);
	static ESplitRectType getIntValue(int nValue);

};//class CUiCommon
#endif // __CLASS_UI_COMMON_H__
