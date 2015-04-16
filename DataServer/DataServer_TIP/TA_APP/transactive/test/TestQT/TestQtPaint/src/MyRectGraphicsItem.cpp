#include "MyRectGraphicsItem.h"

#include "RectAreaBoundingAreas.h"

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;


CMyRectGraphicsItem::CMyRectGraphicsItem()
{
	std::string strLogInfo;
	//
	m_rectDraw = QRectF(-50, -50, 100, 100);
	m_nBoundingRectWidthHalf = 8;
	m_nBoundingRectHeightHalf = 8;
	m_nBoundingRectWidth = m_nBoundingRectWidthHalf * 2;
	m_nBoundingRectHeight = m_nBoundingRectHeightHalf * 2;
	m_pRectAreaBoundingAreas = NULL;
	m_pRectAreaBoundingAreas = new CRectAreaBoundingAreas(this->scenePos(), m_rectDraw, m_nBoundingRectWidth, m_nBoundingRectHeight);
	_ResetAreas();

	//
	m_pCurrentCursor = NULL;
	m_pCurrentCursor = new QCursor();
	m_bMouseLeftButtonDown=false;	
	m_nMouseMoveType = CRectAreaBounding::RectAreaBoundingType_OutSide;

	//
	setZValue(0);
	setAcceptsHoverEvents(true);
	setAcceptDrops(true);
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);


}

CMyRectGraphicsItem::~CMyRectGraphicsItem()
{

	if (NULL != m_pRectAreaBoundingAreas)
	{
		delete m_pRectAreaBoundingAreas;
		m_pRectAreaBoundingAreas = NULL;
	}

	if (NULL != m_pCurrentCursor)
	{
		delete m_pCurrentCursor;
		m_pCurrentCursor = NULL;
	}
}


void CMyRectGraphicsItem::_ResetRect(QRectF rectDraw)
{
	m_rectDraw = rectDraw;
	_ResetAreas();

	update(boundingRect());
}

QRectF CMyRectGraphicsItem::boundingRect() const
{
	return m_rectBounding;
}

QPainterPath CMyRectGraphicsItem::shape()const
{
	//mouse in area
	QPainterPath path;
	//path.addRect(m_rectDraw);
	path.addRect(m_rectBounding);
	return path;
}

void CMyRectGraphicsItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->drawRect(m_rectDraw);

}

void CMyRectGraphicsItem::hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsItem::hoverEnterEvent(pEvent);
}

void CMyRectGraphicsItem::hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsItem::hoverMoveEvent(pEvent);
}

void CMyRectGraphicsItem::_SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor)
{
	m_nMouseMoveType = CRectAreaBounding::RectAreaBoundingType_OutSide;

	m_nMouseMoveType = m_pRectAreaBoundingAreas->checkInWhichArea(pointCurrent);

	switch (m_nMouseMoveType)
	{
	case CRectAreaBounding::RectAreaBoundingType_LeftMiddle:
		pCurrentCursor->setShape(Qt::SizeHorCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_LeftBottom:
		pCurrentCursor->setShape(Qt::SizeBDiagCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_MiddleBottom:
		pCurrentCursor->setShape(Qt::SizeVerCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_RightBottom:
		pCurrentCursor->setShape(Qt::SizeFDiagCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_RightMiddle:
		pCurrentCursor->setShape(Qt::SizeHorCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_RightTop:
		pCurrentCursor->setShape(Qt::SizeBDiagCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_MiddleTop:
		pCurrentCursor->setShape(Qt::SizeVerCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_LeftTop:
		pCurrentCursor->setShape(Qt::SizeFDiagCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_InSide:
		pCurrentCursor->setShape(Qt::SizeAllCursor);
		break;
	case CRectAreaBounding::RectAreaBoundingType_OutSide:
		pCurrentCursor->setShape(Qt::ArrowCursor);
		break;
	default:		
		pCurrentCursor->setShape(Qt::ArrowCursor);
		break;
	}


}

void CMyRectGraphicsItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	m_pCurrentCursor->setShape(Qt::ArrowCursor);
	m_bMouseLeftButtonDown = false;
	this->setCursor(*m_pCurrentCursor);
	update();
	QGraphicsItem::hoverLeaveEvent(pEvent);
}

void CMyRectGraphicsItem::mousePressEvent(QGraphicsSceneMouseEvent* pEvent)
{
	if(pEvent->button() == Qt::LeftButton)
	{
		m_pointBeginMouseLeftButtonDown = pEvent->scenePos();
		m_bMouseLeftButtonDown = true;
	}

	update();

	QGraphicsItem::mousePressEvent(pEvent);
}

void CMyRectGraphicsItem::mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent)
{

	if (false == m_bMouseLeftButtonDown)
	{
		update();
		QGraphicsItem::mouseMoveEvent(pEvent);
		return;
	}

	QRectF temRect = m_rectDraw;
	QPointF pointEndDifBegin;
	m_pointEndMouseLeftButtonDown = pEvent->scenePos();
	pointEndDifBegin = m_pointEndMouseLeftButtonDown - m_pointBeginMouseLeftButtonDown;
	m_pointBeginMouseLeftButtonDown = m_pointEndMouseLeftButtonDown;

	
	switch(m_nMouseMoveType)
	{
	case CRectAreaBounding::RectAreaBoundingType_LeftMiddle:
		{
			temRect = QRectF(
				m_rectDraw.left() + pointEndDifBegin.x(), 
				m_rectDraw.top(), 
				m_rectDraw.width() - pointEndDifBegin.x(), 
				m_rectDraw.height()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_LeftBottom:
		{
			temRect = QRectF(
				m_rectDraw.left() + pointEndDifBegin.x(), 
				m_rectDraw.top(), 
				m_rectDraw.width() - pointEndDifBegin.x(), 
				m_rectDraw.height() + pointEndDifBegin.y()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_MiddleBottom:
		{
			temRect = QRectF(
				m_rectDraw.left(), 
				m_rectDraw.top(), 
				m_rectDraw.width(), 
				m_rectDraw.height() + pointEndDifBegin.y()
				);

			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_RightBottom:
		{
			temRect = QRectF(
				m_rectDraw.left(), 
				m_rectDraw.top(), 
				m_rectDraw.width() + pointEndDifBegin.x(), 
				m_rectDraw.height() + pointEndDifBegin.y()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_RightMiddle:
		{
			temRect = QRectF(
				m_rectDraw.left(), 
				m_rectDraw.top(), 
				m_rectDraw.width() + pointEndDifBegin.x(), 
				m_rectDraw.height()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_RightTop:
		{
			temRect = QRectF(
				m_rectDraw.left(), 
				m_rectDraw.top() + pointEndDifBegin.y(), 
				m_rectDraw.width()+ pointEndDifBegin.x(), 
				m_rectDraw.height() - pointEndDifBegin.y()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_MiddleTop:
		{
			temRect = QRectF(
				m_rectDraw.left(), 
				m_rectDraw.top() + pointEndDifBegin.y(), 
				m_rectDraw.width(), 
				m_rectDraw.height() - pointEndDifBegin.y()
				);
			break;
		}
	case CRectAreaBounding::RectAreaBoundingType_LeftTop:
		{
			temRect = QRectF(
				m_rectDraw.left() + pointEndDifBegin.x(), 
				m_rectDraw.top() + pointEndDifBegin.y(), 
				m_rectDraw.width() - pointEndDifBegin.x(), 
				m_rectDraw.height() - pointEndDifBegin.y()
				);
			break;
		}
	default:
		break;
	}


	_ResetRect(temRect);
	update(boundingRect());
	//this->moveBy(0, 0);


}

void CMyRectGraphicsItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent)
{
 	m_bMouseLeftButtonDown = false;
 	update();
 	QGraphicsItem::mouseReleaseEvent(pEvent);
}


void CMyRectGraphicsItem::_ResetAreas()
{
 	m_rectBounding.setLeft(m_rectDraw.left() - m_nBoundingRectWidthHalf);
 	m_rectBounding.setTop(m_rectDraw.top() - m_nBoundingRectHeightHalf);
 	m_rectBounding.setWidth(m_rectDraw.width() + m_nBoundingRectWidth);
 	m_rectBounding.setHeight(m_rectDraw.height() + m_nBoundingRectHeight);

	m_pRectAreaBoundingAreas->resetRectDraw(this->scenePos(), m_rectDraw, 
		m_nBoundingRectWidth, m_nBoundingRectHeight);
	prepareGeometryChange();
}


void CMyRectGraphicsItem::_LogPointF(const std::string& strLogInfo, QPointF pointTmp)
{
	LOG_DEBUG<<"_LogPointF strLogInfo="<<strLogInfo
		<<" "<<"point.x()="<<pointTmp.x()
		<<" "<<"point.y()="<<pointTmp.y();
}


void CMyRectGraphicsItem::_LogRectF(const std::string& strLogInfo, QRectF rectTmp)
{
	LOG_DEBUG<<"_LogPointF strLogInfo="<<strLogInfo
		<<" "<<"rect.left()="<<rectTmp.left()
		<<" "<<"rect.top()="<<rectTmp.top()
		<<" "<<"rect.right()="<<rectTmp.right()
		<<" "<<"rect.bottom()="<<rectTmp.bottom();
}

