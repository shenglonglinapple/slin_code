#include "InformationRectItem.h"
#include "CommonData.h"
#include "BoundingRectAreas.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE



CInformationRectItem::CInformationRectItem(const QRectF& rect, QGraphicsItem *parent, QGraphicsScene* scene)
:QGraphicsObject(parent)
{
	int nZIndex = 0;
	this->setZValue(nZIndex);

	m_nClassType = ClassType_CInformationRectItem;

	//rect
	m_rectDrawInScenePos = rect;
	m_nBoundingRectWidthHalf = 8;
	m_nBoundingRectHeightHalf = 8;
	m_nBoundingRectWidth = m_nBoundingRectWidthHalf * 2;
	m_nBoundingRectHeight = m_nBoundingRectHeightHalf * 2;
	m_pRectAreaBoundingAreas = new CBoundingRectAreas(m_rectDrawInScenePos, m_nBoundingRectWidth, m_nBoundingRectHeight);

	
	//text
	m_strTextTop = "strTextTop";
	m_strTextBottom = "strTextBottom";	

	//
	m_pCurrentCursor = NULL;
	m_pCurrentCursor = new QCursor();
	m_bMouseLeftButtonDown = false;	
	m_nMouseMoveType = CBoundingRect::RectAreaBoundingType_OutSide;

	//
	setZValue(0);
	setAcceptsHoverEvents(true);
	setAcceptDrops(true);
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

	_ResetRect(m_rectDrawInScenePos);
}



CInformationRectItem::~CInformationRectItem()
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


void CInformationRectItem::_ResetRect(QRectF rectDraw)
{
	m_rectDrawInScenePos = rectDraw;

	_ResetPoints();
	_ResetAreas();
	//_ResetAllEdge();
	adjustAllPos();

	prepareGeometryChange();

	update(boundingRect());
	
}

QRectF CInformationRectItem::boundingRect() const
{
	return m_rectOutSideBoundingInScenePos;
}

QPainterPath CInformationRectItem::shape()const
{
	//mouse in area
	QPainterPath path;
	//path.addRect(m_rectDraw);
	path.addRect(m_rectOutSideBoundingInScenePos);
	return path;
}

void CInformationRectItem::paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget)
{
 	Q_UNUSED(option);
 	Q_UNUSED(widget);

	painter->drawRect(m_rectDrawInScenePos);
	painter->drawLine(m_lineMiddle);

	painter->drawText(m_rectInSideTopPartInScenePos, m_strTextTop);
	painter->drawText(m_rectInSideBottomPartInScenePos, m_strTextBottom);


	/*draw bounding*/
	
	QPen m_PenLineBounding = QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
	painter->setPen(m_PenLineBounding);
	painter->drawRect(m_rectOutSideBoundingInScenePos);
	painter->drawRect(m_rectInSideBoundingInScenePos);
	

}



void CInformationRectItem::hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsItem::hoverEnterEvent(pEvent);
}

void CInformationRectItem::hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();
	_SetCursorShape(pointCurrent, m_pCurrentCursor);
	this->setCursor(*m_pCurrentCursor);
	this->update();
	QGraphicsItem::hoverMoveEvent(pEvent);
}

void CInformationRectItem::_SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor)
{
	m_nMouseMoveType = CBoundingRect::RectAreaBoundingType_OutSide;

	m_nMouseMoveType = m_pRectAreaBoundingAreas->checkInWhichArea(pointCurrent);

	switch (m_nMouseMoveType)
	{
	case CBoundingRect::RectAreaBoundingType_LeftMiddle:
		pCurrentCursor->setShape(Qt::SizeHorCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_LeftBottom:
		pCurrentCursor->setShape(Qt::SizeBDiagCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_MiddleBottom:
		pCurrentCursor->setShape(Qt::SizeVerCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_RightBottom:
		pCurrentCursor->setShape(Qt::SizeFDiagCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_RightMiddle:
		pCurrentCursor->setShape(Qt::SizeHorCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_RightTop:
		pCurrentCursor->setShape(Qt::SizeBDiagCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_MiddleTop:
		pCurrentCursor->setShape(Qt::SizeVerCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_LeftTop:
		pCurrentCursor->setShape(Qt::SizeFDiagCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_InSide:
		pCurrentCursor->setShape(Qt::OpenHandCursor);
		break;
	case CBoundingRect::RectAreaBoundingType_OutSide:
		pCurrentCursor->setShape(Qt::ArrowCursor);
		break;
	default:		
		pCurrentCursor->setShape(Qt::ArrowCursor);
		break;
	}


}

void CInformationRectItem::hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	m_pCurrentCursor->setShape(Qt::ArrowCursor);
	m_bMouseLeftButtonDown = false;
	this->setCursor(*m_pCurrentCursor);
	update();
	QGraphicsItem::hoverLeaveEvent(pEvent);
}

void CInformationRectItem::mousePressEvent(QGraphicsSceneMouseEvent* pEvent)
{
	if(pEvent->button() == Qt::LeftButton)
	{
		m_pCurrentCursor->setShape(Qt::ClosedHandCursor);
		this->setCursor(*m_pCurrentCursor);

		m_pointBeginMouseLeftButtonDown = pEvent->scenePos();
		m_bMouseLeftButtonDown = true;
	}

	update();

	QGraphicsItem::mousePressEvent(pEvent);
}

void CInformationRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent)
{
	QRectF rectAfterMove;
	QPointF pointMove;
	QRectF rectDrawInScenePosOld = m_rectDrawInScenePos;

	if (false == m_bMouseLeftButtonDown)
	{
		update();
		QGraphicsItem::mouseMoveEvent(pEvent);
		return;
	}

	m_pointEndMouseLeftButtonDown = pEvent->scenePos();
	pointMove = m_pointEndMouseLeftButtonDown - m_pointBeginMouseLeftButtonDown;
	m_pointBeginMouseLeftButtonDown = m_pointEndMouseLeftButtonDown;

	rectAfterMove = _GetRectAfterMove(pointMove);

	_ResetRect(rectAfterMove);

	if (true == isColliding())
	{
		m_rectDrawInScenePos = rectDrawInScenePosOld;
		_ResetRect(m_rectDrawInScenePos);
		return;
	}

}

void CInformationRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent)
{
 	m_bMouseLeftButtonDown = false;
 	update();
 	QGraphicsItem::mouseReleaseEvent(pEvent);
}

void CInformationRectItem::_ResetPoints()
{
	QRectF rectDrawInScenePos;

	rectDrawInScenePos = m_rectDrawInScenePos;
	
	m_pointRectLeftTopMiddle.setX(rectDrawInScenePos.left());
	m_pointRectLeftTopMiddle.setY(rectDrawInScenePos.top() + (rectDrawInScenePos.height() / 4));

	m_pointRectLeftMiddle.setX(rectDrawInScenePos.left());
	m_pointRectLeftMiddle.setY(rectDrawInScenePos.top() + (rectDrawInScenePos.height() / 2));

	m_pointRectLeftBottomMiddle.setX(rectDrawInScenePos.left());
	m_pointRectLeftBottomMiddle.setY(m_pointRectLeftMiddle.y() + (rectDrawInScenePos.height() / 4));

	m_pointRectBottomMiddle.setX(rectDrawInScenePos.left() + (rectDrawInScenePos.width() / 2));
	m_pointRectBottomMiddle.setY(rectDrawInScenePos.bottom());
	m_pointRectRightMiddle.setX(rectDrawInScenePos.right());
	m_pointRectRightMiddle.setY(m_pointRectLeftMiddle.y());
	m_pointRectTopMiddle.setX(m_pointRectBottomMiddle.x());
	m_pointRectTopMiddle.setY(rectDrawInScenePos.top());
} 

void CInformationRectItem::_ResetAreas()
{
	//rect
	QRectF rectDrawInScenePos;
	rectDrawInScenePos = m_rectDrawInScenePos;

	m_rectInSideBoundingInScenePos.setLeft(rectDrawInScenePos.left() + m_nBoundingRectWidthHalf);
	m_rectInSideBoundingInScenePos.setTop(rectDrawInScenePos.top() + m_nBoundingRectHeightHalf);
	m_rectInSideBoundingInScenePos.setWidth(rectDrawInScenePos.width() - m_nBoundingRectWidth);
	m_rectInSideBoundingInScenePos.setHeight(rectDrawInScenePos.height() - m_nBoundingRectHeight);

	m_rectInSideTopPartInScenePos.setLeft(m_rectInSideBoundingInScenePos.left());
	m_rectInSideTopPartInScenePos.setTop(m_rectInSideBoundingInScenePos.top());
	m_rectInSideTopPartInScenePos.setWidth(m_rectInSideBoundingInScenePos.width());
	m_rectInSideTopPartInScenePos.setHeight((m_rectInSideBoundingInScenePos.height() / 2));


	m_rectInSideBottomPartInScenePos.setLeft(m_rectInSideBoundingInScenePos.left());
	m_rectInSideBottomPartInScenePos.setTop(m_rectInSideBoundingInScenePos.top() + (m_rectInSideBoundingInScenePos.height() / 2) + m_nBoundingRectHeightHalf);
	m_rectInSideBottomPartInScenePos.setWidth(m_rectInSideBoundingInScenePos.width());
	m_rectInSideBottomPartInScenePos.setHeight((m_rectInSideBoundingInScenePos.height() / 2));

 	m_rectOutSideBoundingInScenePos.setLeft(rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
 	m_rectOutSideBoundingInScenePos.setTop(rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
 	m_rectOutSideBoundingInScenePos.setWidth(rectDrawInScenePos.width() + m_nBoundingRectWidth);
 	m_rectOutSideBoundingInScenePos.setHeight(rectDrawInScenePos.height() + m_nBoundingRectHeight);

	m_pRectAreaBoundingAreas->resetRectDraw(rectDrawInScenePos, m_nBoundingRectWidth, m_nBoundingRectHeight);


	//line
	m_lineMiddle.setP1(m_pointRectLeftMiddle);
	m_lineMiddle.setP2(m_pointRectRightMiddle);

	//text top
	m_pointTextTop.setX(m_rectInSideBoundingInScenePos.x());
	m_pointTextTop.setY(m_rectInSideBoundingInScenePos.y());
	m_nTextTopWidth = m_rectInSideBoundingInScenePos.width();

	m_pointTextBottom.setX(m_rectInSideBoundingInScenePos.x());
	m_pointTextBottom.setY(m_pointRectLeftMiddle.y() + m_nBoundingRectHeightHalf);
	m_nTextBottomWidth = m_nTextTopWidth;

}








QRectF CInformationRectItem::_GetRectAfterMove(QPointF pointMove)
{
	QRectF rectAfterMove;
	QRectF rectDrawInScenePos;
	rectDrawInScenePos = m_rectDrawInScenePos;
	rectAfterMove = rectDrawInScenePos;

	switch(m_nMouseMoveType)
	{
	case CBoundingRect::RectAreaBoundingType_LeftMiddle:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left() + pointMove.x(), 
				rectDrawInScenePos.top(), 
				rectDrawInScenePos.width() - pointMove.x(), 
				rectDrawInScenePos.height()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_LeftBottom:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left() + pointMove.x(), 
				rectDrawInScenePos.top(), 
				rectDrawInScenePos.width() - pointMove.x(), 
				rectDrawInScenePos.height() + pointMove.y()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_MiddleBottom:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left(), 
				rectDrawInScenePos.top(), 
				rectDrawInScenePos.width(), 
				rectDrawInScenePos.height() + pointMove.y()
				);

			break;
		}
	case CBoundingRect::RectAreaBoundingType_RightBottom:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left(), 
				rectDrawInScenePos.top(), 
				rectDrawInScenePos.width() + pointMove.x(), 
				rectDrawInScenePos.height() + pointMove.y()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_RightMiddle:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left(), 
				rectDrawInScenePos.top(), 
				rectDrawInScenePos.width() + pointMove.x(), 
				rectDrawInScenePos.height()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_RightTop:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left(), 
				rectDrawInScenePos.top() + pointMove.y(), 
				rectDrawInScenePos.width()+ pointMove.x(), 
				rectDrawInScenePos.height() - pointMove.y()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_MiddleTop:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left(), 
				rectDrawInScenePos.top() + pointMove.y(), 
				rectDrawInScenePos.width(), 
				rectDrawInScenePos.height() - pointMove.y()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_LeftTop:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left() + pointMove.x(), 
				rectDrawInScenePos.top() + pointMove.y(), 
				rectDrawInScenePos.width() - pointMove.x(), 
				rectDrawInScenePos.height() - pointMove.y()
				);
			break;
		}
	case CBoundingRect::RectAreaBoundingType_InSide:
		{
			rectAfterMove = QRectF(
				rectDrawInScenePos.left() + pointMove.x(), 
				rectDrawInScenePos.top() + pointMove.y(), 
				rectDrawInScenePos.width(), 
				rectDrawInScenePos.height()
				);
			break;
		}
	default:
		break;
	}

	return rectAfterMove;

}

void CInformationRectItem::setTopText( const QString& strValue )
{
	m_strTextTop = strValue;
	//m_pTextTop->setHtml(m_strTextTop);
	_ResetRect(m_rectDrawInScenePos);
}

void CInformationRectItem::setBottomText( const QString& strValue )
{
	m_strTextBottom = strValue;
	//m_pTextBottom->setHtml(m_strTextBottom);
	_ResetRect(m_rectDrawInScenePos);
}



QPointF CInformationRectItem::getPointRectLeftTopMiddle()
{
	return m_pointRectLeftTopMiddle;
}
QPointF CInformationRectItem::getPointRectLeftMiddle()
{
	return m_pointRectLeftMiddle;
}
QPointF CInformationRectItem::getPointRectLeftBottomMiddle()
{
	return m_pointRectLeftBottomMiddle;
}

QPointF CInformationRectItem::getPointRectRightMiddle()
{
	return m_pointRectRightMiddle;
}


QPointF CInformationRectItem::getItemPos()
{
	QPointF point;

	point.setX(m_rectDrawInScenePos.x());
	point.setY(m_rectDrawInScenePos.y());

	return point;

}

void CInformationRectItem::setItemPos( QPointF point )
{
	QRectF rect;
	rect.setX(point.x());
	rect.setY(point.y());
	rect.setWidth(m_rectDrawInScenePos.width());
	rect.setHeight(m_rectDrawInScenePos.height());
	m_rectDrawInScenePos = rect;
	_ResetRect(m_rectDrawInScenePos);
}

void CInformationRectItem::setItemRect( QRectF rect )
{
	m_rectDrawInScenePos = rect;
	_ResetRect(m_rectDrawInScenePos);
}

qreal CInformationRectItem::getItemWidth()
{
	qreal nWidth = 0;

	nWidth = m_rectDrawInScenePos.width();

	return nWidth;
}
qreal CInformationRectItem::getItemHeight()
{
	qreal nHeight = 0;

	nHeight = m_rectDrawInScenePos.height();

	return nHeight;
}



QPixmap CInformationRectItem::image() const
{
	QPixmap pixmap(250, 250);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	QPen pen(Qt::black, 2);
	QPointF pointTextTop;
	QPointF pointTextBottom;

	pointTextTop = m_pointRectLeftTopMiddle;
	pointTextTop.setX(m_pointRectLeftTopMiddle.x() + m_nTextTopWidth / 10);
	pointTextBottom = m_pointRectLeftBottomMiddle;
	pointTextBottom.setX(m_pointRectLeftBottomMiddle.x() + m_nTextTopWidth / 10);

	painter.setPen(pen);
	//painter.translate(125, 125);
	painter.translate(0, 0);
	//painter.drawRect(m_rectDrawInScenePos);
	painter.drawLine(m_lineMiddle);
	painter.drawText(pointTextTop, m_strTextTop);
	painter.drawText(pointTextBottom, m_strTextBottom);

	return pixmap;
}

EProjectClassType CInformationRectItem::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}

int CInformationRectItem::type() const
{
	return m_nClassType;
}



void CInformationRectItem::adjustAllPos()
{
	int nDebug = 0;
	//use children's adjustAllPos
}




//¼ì²âÊÇ·ñÓÐÅö×²
bool CInformationRectItem::isColliding() 
{
	bool bIsColliding = false;
	QGraphicsScene* pSceneRef = NULL;
	QList<QGraphicsItem *> item_list;
	QGraphicsItem* item = NULL;


	Qt::ItemSelectionMode mode = Qt::IntersectsItemShape;

	mode = Qt::IntersectsItemShape;
	//mode = Qt::ContainsItemShape;
	item_list = this->collidingItems(mode);
	//if(item->collidingItems().count() > 1)

	if (item_list.count() > 1)
	{
		bIsColliding = true;
	}

	return bIsColliding;
	
}


//QT_END_NAMESPACE






