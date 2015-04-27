#include "BoundingRectAreas.h"
#include "BoundingRect.h"


CBoundingRectAreas::CBoundingRectAreas(QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight )
{
	m_nClassType = ClassType_CBoundingRectAreas;

	m_rectDrawInScenePos = rectDraw;
	m_nBoundingRectWidth = nBoundingRectWidth;
	m_nBoundingRectHeight = nBoundingRectHeight;

	m_pRectLeftMiddleArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_LeftMiddle);
	m_pRectLeftBottomArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_LeftBottom);
	m_pRectMiddleBottomArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_MiddleBottom);
	m_pRectRightBottomArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_RightBottom);
	m_pRectRightMiddleArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_RightMiddle);
	m_pRectRightTopArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_RightTop);
	m_pRectMiddleTopArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_MiddleTop);
	m_pRectLeftTopArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_LeftTop);
	m_pRectInsideArea = new CBoundingRect(CBoundingRect::RectAreaBoundingType_InSide);
	
	_ResetAllRectAreas();
}

CBoundingRectAreas::~CBoundingRectAreas()
{
	if (NULL != m_pRectLeftMiddleArea)
	{
		delete m_pRectLeftMiddleArea;
		m_pRectLeftMiddleArea = NULL;
	}

	if (NULL != m_pRectLeftBottomArea)
	{
		delete m_pRectLeftBottomArea;
		m_pRectLeftBottomArea = NULL;
	}

	if (NULL != m_pRectMiddleBottomArea)
	{
		delete m_pRectMiddleBottomArea;
		m_pRectMiddleBottomArea = NULL;
	}

	if (NULL != m_pRectRightBottomArea)
	{
		delete m_pRectRightBottomArea;
		m_pRectRightBottomArea = NULL;
	}

	if (NULL != m_pRectRightMiddleArea)
	{
		delete m_pRectRightMiddleArea;
		m_pRectRightMiddleArea = NULL;
	}

	if (NULL != m_pRectRightTopArea)
	{
		delete m_pRectRightTopArea;
		m_pRectRightTopArea = NULL;
	}

	if (NULL != m_pRectMiddleTopArea)
	{
		delete m_pRectMiddleTopArea;
		m_pRectMiddleTopArea = NULL;
	}

	if (NULL != m_pRectLeftTopArea)
	{
		delete m_pRectLeftTopArea;
		m_pRectLeftTopArea = NULL;
	}

	if (NULL != m_pRectInsideArea)
	{
		delete m_pRectInsideArea;
		m_pRectInsideArea = NULL;
	}


}



void CBoundingRectAreas::_ResetAllRectAreas()
{
	QRectF rectDrawInScenePos;
	rectDrawInScenePos = m_rectDrawInScenePos;
	//rectDrawInScenePos = getRectInScene(m_scenePos, m_rectDraw);


	m_nBoundingRectWidthHalf = m_nBoundingRectWidth / 2;
	m_nBoundingRectHeightHalf = m_nBoundingRectHeight / 2;

	//1 RectAreaBoundingType_LeftMiddle
	m_pRectLeftMiddleArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_LeftMiddle);
	m_pRectLeftMiddleArea->setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_pRectLeftMiddleArea->setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_pRectLeftMiddleArea->setWidth(m_nBoundingRectWidth);
	m_pRectLeftMiddleArea->setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);


	//2 RectAreaBoundingType_LeftBottom
	m_pRectLeftBottomArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_LeftBottom);
	m_pRectLeftBottomArea->setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_pRectLeftBottomArea->setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_pRectLeftBottomArea->setWidth(m_nBoundingRectWidth);
	m_pRectLeftBottomArea->setHeight(m_nBoundingRectHeight);

	//3 RectAreaBoundingType_MiddleBottom
	m_pRectMiddleBottomArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_MiddleBottom);
	m_pRectMiddleBottomArea->setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_pRectMiddleBottomArea->setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_pRectMiddleBottomArea->setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_pRectMiddleBottomArea->setHeight(m_nBoundingRectHeight);

	//4 RectAreaBoundingType_RightBottom
	m_pRectRightBottomArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_RightBottom);
	m_pRectRightBottomArea->setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_pRectRightBottomArea->setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_pRectRightBottomArea->setWidth(m_nBoundingRectWidth);
	m_pRectRightBottomArea->setHeight(m_nBoundingRectHeight);


	//5 RectAreaBoundingType_RightMiddle
	m_pRectRightMiddleArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_RightMiddle);
	m_pRectRightMiddleArea->setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_pRectRightMiddleArea->setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_pRectRightMiddleArea->setWidth(m_nBoundingRectWidth);
	m_pRectRightMiddleArea->setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);

	//6 RectAreaBoundingType_RightTop
	m_pRectRightTopArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_RightTop);
	m_pRectRightTopArea->setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_pRectRightTopArea->setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_pRectRightTopArea->setWidth(m_nBoundingRectWidth);
	m_pRectRightTopArea->setHeight(m_nBoundingRectHeight);


	//7 RectAreaBoundingType_MiddleTop
	m_pRectMiddleTopArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_MiddleTop);
	m_pRectMiddleTopArea->setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_pRectMiddleTopArea->setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_pRectMiddleTopArea->setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_pRectMiddleTopArea->setHeight(m_nBoundingRectHeight);

	//8 RectAreaBoundingType_LeftTop
	m_pRectLeftTopArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_LeftTop);
	m_pRectLeftTopArea->setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_pRectLeftTopArea->setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_pRectLeftTopArea->setWidth(m_nBoundingRectWidth);
	m_pRectLeftTopArea->setHeight(m_nBoundingRectHeight);

	//9 RectAreaBoundingType_Inside
	m_pRectInsideArea->setRectAreaBoundingType(CBoundingRect::RectAreaBoundingType_InSide);
	m_pRectInsideArea->setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_pRectInsideArea->setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_pRectInsideArea->setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_pRectInsideArea->setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);

	//10 CRectAreaBounding::RectAreaBoundingType_OutSide
	
}




void CBoundingRectAreas::resetRectDraw(QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight )
{
	m_rectDrawInScenePos = rectDraw;
	m_nBoundingRectWidth = nBoundingRectWidth;
	m_nBoundingRectHeight = nBoundingRectHeight;
	_ResetAllRectAreas();
}

CBoundingRect::EBoundingRectType CBoundingRectAreas::checkInWhichArea( QPointF pointPos )
{
	CBoundingRect::EBoundingRectType nRectAreaType = CBoundingRect::RectAreaBoundingType_OutSide;

	//1
	if (_CheckInRect(pointPos, m_pRectLeftMiddleArea))
	{
		nRectAreaType = m_pRectLeftMiddleArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//2
	if (_CheckInRect(pointPos, m_pRectLeftBottomArea))
	{
		nRectAreaType = m_pRectLeftBottomArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//3
	if (_CheckInRect(pointPos, m_pRectMiddleBottomArea))
	{
		nRectAreaType = m_pRectMiddleBottomArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//4
	if (_CheckInRect(pointPos, m_pRectRightBottomArea))
	{
		nRectAreaType = m_pRectRightBottomArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//5
	if (_CheckInRect(pointPos, m_pRectRightMiddleArea))
	{
		nRectAreaType = m_pRectRightMiddleArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//6
	if (_CheckInRect(pointPos, m_pRectRightTopArea))
	{
		nRectAreaType = m_pRectRightTopArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//7
	if (_CheckInRect(pointPos, m_pRectMiddleTopArea))
	{
		nRectAreaType = m_pRectMiddleTopArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//8
	if (_CheckInRect(pointPos, m_pRectLeftTopArea))
	{
		nRectAreaType = m_pRectLeftTopArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	//9
	if (_CheckInRect(pointPos, m_pRectInsideArea))
	{
		nRectAreaType = m_pRectInsideArea->getRectAreaBoundingType();
		return nRectAreaType;
	}

	return nRectAreaType;
}

bool CBoundingRectAreas::_CheckInRect( QPointF pointPos, CBoundingRect* pRectArea )
{
	bool bCheckInRectRes = false;

	/*
	if  (
		( (pointPos.x() >= nRectArea.left()) && (pointPos.x() <= nRectArea.right()) )
		&& ( (pointPos.y() >= nRectArea.top()) && (pointPos.y() <= nRectArea.bottom()) )
		)
	{
		bCheckInRectRes = true;
	}
	*/

	if (pRectArea->contains(pointPos))
	{
		bCheckInRectRes = true;
	}

	return bCheckInRectRes;
}


EProjectClassType CBoundingRectAreas::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CBoundingRectAreas::type() const
{
	return m_nClassType;
}


/*
QRectF CRectAreaBoundingAreas::getRectInScene(QPointF scenePos, QRectF rectDraw)
{
QRectF rectDrawInScenePos;
rectDrawInScenePos.setTopLeft(scenePos + QPointF(rectDraw.x(), rectDraw.y()));
rectDrawInScenePos.setBottomLeft(scenePos + QPointF(rectDraw.x(), rectDraw.y() + rectDraw.height()));
rectDrawInScenePos.setTopRight(scenePos + QPointF(rectDraw.x() + rectDraw.width(), rectDraw.y()));
rectDrawInScenePos.setBottomRight(scenePos + QPointF(rectDraw.x() + rectDraw.width(), rectDraw.y()  + rectDraw.height()));
return rectDrawInScenePos;
}
*/
