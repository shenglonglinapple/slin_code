#ifndef  __DEF__CLASS__BOUNDING_RECT_HH__
#define  __DEF__CLASS__BOUNDING_RECT_HH__

#include "CommonDef.h"

#include <QtCore/QRectF>

class CBoundingRect : public QRectF
{
public:
	enum EBoundingRectType
	{
		RectAreaBoundingType_Begin = 0,
		RectAreaBoundingType_LeftMiddle = 1,
		RectAreaBoundingType_LeftBottom,
		RectAreaBoundingType_MiddleBottom,
		RectAreaBoundingType_RightBottom,
		RectAreaBoundingType_RightMiddle,
		RectAreaBoundingType_RightTop,
		RectAreaBoundingType_MiddleTop,
		RectAreaBoundingType_LeftTop,
		RectAreaBoundingType_InSide,
		RectAreaBoundingType_OutSide,
		RectAreaBoundingType_End
	};

public:
    CBoundingRect(EBoundingRectType nType);
	virtual ~CBoundingRect();

public:
	int type() const;
	EProjectClassType getClassType() const;
	EBoundingRectType getRectAreaBoundingType();
	void setRectAreaBoundingType(EBoundingRectType nType);

private:
	EBoundingRectType m_nType;
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__BOUNDING_RECT_HH__














