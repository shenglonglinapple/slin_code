#include "RectAreaBoundingAreas.h"

CRectAreaBoundingAreas::CRectAreaBoundingAreas( QPointF scenePos, QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight )
{
	m_scenePos = scenePos;
	m_rectDraw = rectDraw;
	m_nBoundingRectWidth = nBoundingRectWidth;
	m_nBoundingRectHeight = nBoundingRectHeight;
	_ResetEightRectAreas();
}

CRectAreaBoundingAreas::~CRectAreaBoundingAreas()
{

}

void CRectAreaBoundingAreas::_ResetEightRectAreas()
{
	QRectF rectDrawInScenePos;
	rectDrawInScenePos.setTopLeft(m_scenePos + QPointF(m_rectDraw.x(), m_rectDraw.y()));
	rectDrawInScenePos.setBottomLeft(m_scenePos + QPointF(m_rectDraw.x(), m_rectDraw.y() + m_rectDraw.height()));
	rectDrawInScenePos.setTopRight(m_scenePos + QPointF(m_rectDraw.x() + m_rectDraw.width(), m_rectDraw.y()));
	rectDrawInScenePos.setBottomRight(m_scenePos + QPointF(m_rectDraw.x() + m_rectDraw.width(), m_rectDraw.y()  + m_rectDraw.height()));

	m_nBoundingRectWidthHalf = m_nBoundingRectWidth / 2;
	m_nBoundingRectHeightHalf = m_nBoundingRectHeight / 2;

	//1 RectAreaBoundingType_LeftMiddle
	m_rectLeftMiddleArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_LeftMiddle);
	m_rectLeftMiddleArea.setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_rectLeftMiddleArea.setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_rectLeftMiddleArea.setWidth(m_nBoundingRectWidth);
	m_rectLeftMiddleArea.setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);


	//2 RectAreaBoundingType_LeftBottom
	m_rectLeftBottomArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_LeftBottom);
	m_rectLeftBottomArea.setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_rectLeftBottomArea.setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_rectLeftBottomArea.setWidth(m_nBoundingRectWidth);
	m_rectLeftBottomArea.setHeight(m_nBoundingRectHeight);

	//3 RectAreaBoundingType_MiddleBottom
	m_rectMiddleBottomArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_MiddleBottom);
	m_rectMiddleBottomArea.setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_rectMiddleBottomArea.setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_rectMiddleBottomArea.setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_rectMiddleBottomArea.setHeight(m_nBoundingRectHeight);

	//4 RectAreaBoundingType_RightBottom
	m_rectRightBottomArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_RightBottom);
	m_rectRightBottomArea.setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_rectRightBottomArea.setY(rectDrawInScenePos.bottom() - m_nBoundingRectHeightHalf);
	m_rectRightBottomArea.setWidth(m_nBoundingRectWidth);
	m_rectRightBottomArea.setHeight(m_nBoundingRectHeight);


	//5 RectAreaBoundingType_RightMiddle
	m_rectRightMiddleArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_RightMiddle);
	m_rectRightMiddleArea.setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_rectRightMiddleArea.setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_rectRightMiddleArea.setWidth(m_nBoundingRectWidth);
	m_rectRightMiddleArea.setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);

	//6 RectAreaBoundingType_RightTop
	m_rectRightTopArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_RightTop);
	m_rectRightTopArea.setX(rectDrawInScenePos.right() - m_nBoundingRectWidthHalf);
	m_rectRightTopArea.setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_rectRightTopArea.setWidth(m_nBoundingRectWidth);
	m_rectRightTopArea.setHeight(m_nBoundingRectHeight);


	//7 RectAreaBoundingType_MiddleTop
	m_rectMiddleTopArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_MiddleTop);
	m_rectMiddleTopArea.setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_rectMiddleTopArea.setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_rectMiddleTopArea.setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_rectMiddleTopArea.setHeight(m_nBoundingRectHeight);

	//8 RectAreaBoundingType_LeftTop
	m_rectLeftTopArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_LeftTop);
	m_rectLeftTopArea.setX(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_rectLeftTopArea.setY(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_rectLeftTopArea.setWidth(m_nBoundingRectWidth);
	m_rectLeftTopArea.setHeight(m_nBoundingRectHeight);

	//9 RectAreaBoundingType_Inside
	m_rectInsideArea.setRectAreaBoundingType(CRectAreaBounding::RectAreaBoundingType_InSide);
	m_rectInsideArea.setX(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_rectInsideArea.setY(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_rectInsideArea.setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_rectInsideArea.setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);

	//10 CRectAreaBounding::RectAreaBoundingType_OutSide
	
}




void CRectAreaBoundingAreas::resetRectDraw( QPointF scenePos, QRectF rectDraw, qreal nBoundingRectWidth, qreal nBoundingRectHeight )
{
	m_scenePos = scenePos;
	m_rectDraw = rectDraw;
	m_nBoundingRectWidth = nBoundingRectWidth;
	m_nBoundingRectHeight = nBoundingRectHeight;
	_ResetEightRectAreas();
}

CRectAreaBounding::RectAreaBoundingType CRectAreaBoundingAreas::checkInWhichArea( QPointF pointPos )
{
	CRectAreaBounding::RectAreaBoundingType nRectAreaType = CRectAreaBounding::RectAreaBoundingType_OutSide;

	//1
	if (_CheckInRect(pointPos, m_rectLeftMiddleArea))
	{
		nRectAreaType = m_rectLeftMiddleArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//2
	if (_CheckInRect(pointPos, m_rectLeftBottomArea))
	{
		nRectAreaType = m_rectLeftBottomArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//3
	if (_CheckInRect(pointPos, m_rectMiddleBottomArea))
	{
		nRectAreaType = m_rectMiddleBottomArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//4
	if (_CheckInRect(pointPos, m_rectRightBottomArea))
	{
		nRectAreaType = m_rectRightBottomArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//5
	if (_CheckInRect(pointPos, m_rectRightMiddleArea))
	{
		nRectAreaType = m_rectRightMiddleArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//6
	if (_CheckInRect(pointPos, m_rectRightTopArea))
	{
		nRectAreaType = m_rectRightTopArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//7
	if (_CheckInRect(pointPos, m_rectMiddleTopArea))
	{
		nRectAreaType = m_rectMiddleTopArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//8
	if (_CheckInRect(pointPos, m_rectLeftTopArea))
	{
		nRectAreaType = m_rectLeftTopArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	//9
	if (_CheckInRect(pointPos, m_rectInsideArea))
	{
		nRectAreaType = m_rectInsideArea.getRectAreaBoundingType();
		return nRectAreaType;
	}

	return nRectAreaType;
}

bool CRectAreaBoundingAreas::_CheckInRect( QPointF pointPos, CRectAreaBounding nRectArea )
{
	bool bCheckInRectRes = false;

	if  (
		( (pointPos.x() >= nRectArea.left()) && (pointPos.x() <= nRectArea.right()) )
		&& ( (pointPos.y() >= nRectArea.top()) && (pointPos.y() <= nRectArea.bottom()) )
		)
	{
		bCheckInRectRes = true;
	}

	return bCheckInRectRes;
}
