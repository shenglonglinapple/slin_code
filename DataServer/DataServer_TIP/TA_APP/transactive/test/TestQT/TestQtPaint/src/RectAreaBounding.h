#ifndef  __DEF__CLASS__RECT_AREA_BOUNDING_HH__
#define  __DEF__CLASS__RECT_AREA_BOUNDING_HH__



#include <QtCore/QRectF>



class CRectAreaBounding : public QRectF
{
public:
	enum RectAreaBoundingType
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
	CRectAreaBounding();
    CRectAreaBounding(RectAreaBoundingType nType);
	virtual ~CRectAreaBounding();

public:
	RectAreaBoundingType getRectAreaBoundingType();
	void setRectAreaBoundingType(RectAreaBoundingType nType);

private:
	RectAreaBoundingType m_nType;
};

#endif // __DEF__CLASS__RECT_AREA_BOUNDING_HH__














