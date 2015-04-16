#ifndef  __DEF__CLASS__BOUNDING_RECT_AREAS_HH__
#define  __DEF__CLASS__BOUNDING_RECT_AREAS_HH__


#include "CommonDef.h"
#include <QtCore/QRectF>
#include "BoundingRect.h"

class CBoundingRectAreas 
{
public:
	CBoundingRectAreas(QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight);
	virtual ~CBoundingRectAreas();
public:
	int type() const;
	EProjectClassType getClassType() const;
	void resetRectDraw(QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight);
	CBoundingRect::EBoundingRectType checkInWhichArea(QPointF pointPos);
private:
	bool _CheckInRect(QPointF pointPos, CBoundingRect* pRectArea);
	void _ResetAllRectAreas();
private:
	QRectF m_rectDrawInScenePos;
	qreal m_nBoundingRectWidth;
	qreal m_nBoundingRectHeight;
	qreal m_nBoundingRectWidthHalf;
	qreal m_nBoundingRectHeightHalf;
private:
	CBoundingRect* m_pRectLeftMiddleArea;//1
	CBoundingRect* m_pRectLeftBottomArea;//2
	CBoundingRect* m_pRectMiddleBottomArea;//3
	CBoundingRect* m_pRectRightBottomArea;//4
	CBoundingRect* m_pRectRightMiddleArea;//5
	CBoundingRect* m_pRectRightTopArea;//6
	CBoundingRect* m_pRectMiddleTopArea;//7
	CBoundingRect* m_pRectLeftTopArea;//8
	CBoundingRect* m_pRectInsideArea;//9	RectAreaBoundingType_InSide
	//10 RectAreaBoundingType_OutSide
	
private:
	EProjectClassType m_nClassType;


};

#endif // __DEF__CLASS__BOUNDING_RECT_AREAS_HH__














