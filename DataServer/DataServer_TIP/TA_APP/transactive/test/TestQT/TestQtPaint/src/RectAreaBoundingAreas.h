#ifndef  __DEF__CLASS__RECT_AREA_BOUNDING_AREAS_HH__
#define  __DEF__CLASS__RECT_AREA_BOUNDING_AREAS_HH__



#include <QtCore/QRectF>


#include "RectAreaBounding.h"

class CRectAreaBoundingAreas 
{
public:
	CRectAreaBoundingAreas(QPointF scenePos, QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight);
	virtual ~CRectAreaBoundingAreas();
public:
	void resetRectDraw(QPointF scenePos, QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight);
	CRectAreaBounding::RectAreaBoundingType checkInWhichArea(QPointF pointPos);
private:
	bool _CheckInRect(QPointF pointPos, CRectAreaBounding nRectArea);
	void _ResetEightRectAreas();
private:
	QPointF m_scenePos;
	QRectF m_rectDraw;
	qreal m_nBoundingRectWidth;
	qreal m_nBoundingRectHeight;
	qreal m_nBoundingRectWidthHalf;
	qreal m_nBoundingRectHeightHalf;
private:
	CRectAreaBounding m_rectLeftMiddleArea;//1
	CRectAreaBounding m_rectLeftBottomArea;//2
	CRectAreaBounding m_rectMiddleBottomArea;//3
	CRectAreaBounding m_rectRightBottomArea;//4
	CRectAreaBounding m_rectRightMiddleArea;//5
	CRectAreaBounding m_rectRightTopArea;//6
	CRectAreaBounding m_rectMiddleTopArea;//7
	CRectAreaBounding m_rectLeftTopArea;//8
	CRectAreaBounding m_rectInsideArea;//9	RectAreaBoundingType_InSide
	//10 RectAreaBoundingType_OutSide
	 

};

#endif // __DEF__CLASS__RECT_AREA_BOUNDING_AREAS_HH__














