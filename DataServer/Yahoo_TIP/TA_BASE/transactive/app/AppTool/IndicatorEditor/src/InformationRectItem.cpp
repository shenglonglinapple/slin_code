#include "InformationRectItem.h"
#include "CommonData.h"
#include "BoundingRectAreas.h"
#include "InformationRectItemEdge.h"
#include "InformationBase.h"
#include "InformationTextItem.h"

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
	m_nBoundingRectWidthHalf = 4;
	m_nBoundingRectHeightHalf = 4;
	m_nBoundingRectWidth = m_nBoundingRectWidthHalf * 2;
	m_nBoundingRectHeight = m_nBoundingRectHeightHalf * 2;
	m_pRectAreaBoundingAreas = new CBoundingRectAreas(m_rectDrawInScenePos, m_nBoundingRectWidth, m_nBoundingRectHeight);
	
	//text
	m_strTextTop = "strTextTop";
	m_pTextTop = new CInformationTextItem(this, NULL, CInformationTextItem::TextItemType_Context);
	m_pTextTop->setHtml(m_strTextTop);
	m_pTextTop->setZValue(nZIndex - 3);
	m_pTextTop->setAcceptDrops(false);
	m_pTextTop->setFlag(QGraphicsItem::ItemIsMovable, false);

	

	m_strTextBottom = "strTextBottom";
	m_pTextBottom = new CInformationTextItem(this, NULL, CInformationTextItem::TextItemType_Context);
	m_pTextBottom->setHtml(m_strTextBottom);
	m_pTextBottom->setZValue(nZIndex - 4);
	m_pTextBottom->setAcceptDrops(false);
	m_pTextBottom->setFlag(QGraphicsItem::ItemIsMovable, false);


	//
	m_pCurrentCursor = NULL;
	m_pCurrentCursor = new QCursor();
	m_bMouseLeftButtonDown = false;	
	m_nMouseMoveType = CBoundingRect::RectAreaBoundingType_OutSide;

	//
	//setZValue(0);
	setAcceptsHoverEvents(true);
	setAcceptDrops(true);
	setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable);

	_ResetRect(m_rectDrawInScenePos);

	m_LineColor = Qt::black;
	m_PenLine = QPen(m_LineColor, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	m_PenLine.setColor(m_LineColor);
	_CreateActions();
	_CreateConnect();
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

	m_PenLine.setColor(m_LineColor);
	painter->setPen(m_PenLine);
// 	painter->setPen(Qt::NoPen);
// 	painter->setBrush(Qt::darkGray);
	painter->drawRect(m_rectDrawInScenePos);
	painter->drawLine(m_lineMiddle);

	//painter->drawText(m_rectInSideTopPartInScenePos, m_strTextTop);
	//painter->drawText(m_rectInSideBottomPartInScenePos, m_strTextBottom);


	/*draw bounding*/
	/*
	QPen m_PenLineBounding = QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
	painter->setPen(m_PenLineBounding);
	painter->drawRect(m_rectOutSideBoundingInScenePos);
	painter->drawRect(m_rectInSideBoundingInScenePos);
	*/

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

	//m_pGraphicsRectItem->setRect(m_rectDrawInScenePos);

	//line
	m_lineMiddle.setP1(m_pointRectLeftMiddle);
	m_lineMiddle.setP2(m_pointRectRightMiddle);
	//m_pGraphicsLineItem->setLine(m_lineMiddle);


	//text top
	m_pointTextTop.setX(m_rectInSideBoundingInScenePos.x());
	m_pointTextTop.setY(m_rectInSideBoundingInScenePos.y());
	m_nTextTopWidth = m_rectInSideBoundingInScenePos.width();
	m_pTextTop->setPos(m_pointTextTop);
	m_pTextTop->setTextWidth(m_nTextTopWidth);
	//m_pTextTop->adjustSize();

	m_pointTextBottom.setX(m_rectInSideBoundingInScenePos.x());
	m_pointTextBottom.setY(m_pointRectLeftMiddle.y() + m_nBoundingRectHeightHalf);
	m_nTextBottomWidth = m_nTextTopWidth;
	m_pTextBottom->setPos(m_pointTextBottom);
	m_pTextBottom->setTextWidth(m_nTextBottomWidth);
	//m_pTextBottom->adjustSize();
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
	m_pTextTop->setHtml(m_strTextTop);
	_ResetRect(m_rectDrawInScenePos);
}

void CInformationRectItem::setBottomText( const QString& strValue )
{
	m_strTextBottom = strValue;
	m_pTextBottom->setHtml(m_strTextBottom);
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



EProjectClassType CInformationRectItem::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}

int CInformationRectItem::type() const
{
	return m_nClassType;
}

CInformationRectItemEdge::EEdgeType CInformationRectItem::checkEdgeType( QPointF pointPos )
{
	CInformationRectItemEdge::EEdgeType nEdgeType = CInformationRectItemEdge::EEdgeType_Begin;

	
	if (false == m_rectDrawInScenePos.contains(pointPos))
	{
		nEdgeType = CInformationRectItemEdge::EEdgeType_Begin;
		return nEdgeType;
	}

	if (pointPos.y() < m_pointRectLeftMiddle.y())
	{
		nEdgeType = CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top;
	}
	else
	{
		nEdgeType = CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom;

	}

	return nEdgeType;
	
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
	Qt::ItemSelectionMode nModeValue = Qt::IntersectsItemShape;
	EProjectClassType nClassType = ClassType_Begin;
	QList<QGraphicsItem *> lstCollidingItems;
	QGraphicsItem* pItem = NULL;
	QList<QGraphicsItem *>::Iterator iterLst;
	int nRectItemCount = 0;
	int nTextItemCount = 0;

	nModeValue = Qt::IntersectsItemShape;
	lstCollidingItems = this->collidingItems(nModeValue);

	iterLst = lstCollidingItems.begin();
	while (iterLst != lstCollidingItems.end())
	{
		pItem = NULL;
		nClassType = ClassType_Begin;
		pItem = (*iterLst);
		nClassType = (EProjectClassType)(pItem->type());

		if (ClassType_CInfomationItemInEditor == nClassType)
		{
			nRectItemCount++;
		}
		if (ClassType_CInformationTextItem == nClassType)
		{
			nTextItemCount++;
		}

		iterLst++;
	}

	if (nTextItemCount > 2)
	{
		bIsColliding = true;
	}

	if (nRectItemCount >= 1)
	{
		bIsColliding = true;
	}


	return bIsColliding;
	
}



void CInformationRectItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
	CBoundingRect::EBoundingRectType nMouseInWhichArea = CBoundingRect::RectAreaBoundingType_OutSide;
	QMenu menu;
	m_pEventScreenPos = event->scenePos();

	nMouseInWhichArea = m_pRectAreaBoundingAreas->checkInWhichArea(m_pEventScreenPos);

	if (CBoundingRect::RectAreaBoundingType_LeftMiddle == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_LeftBottom == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_MiddleBottom == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_RightBottom == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_RightMiddle == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_RightTop == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_MiddleTop == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_LeftTop == nMouseInWhichArea
		|| CBoundingRect::RectAreaBoundingType_InSide == nMouseInWhichArea		
		)
	{

		m_pEventScreenPos.setX(m_pEventScreenPos.x() + 50);

		//menu.addAction(m_pActionSetFont);
		menu.addAction(m_pActionSetColour);
		menu.exec(event->screenPos());
	}






}

void CInformationRectItem::_CreateActions()
{
	m_pActionSetFont = new QAction(QObject::tr("SetFont"), this);
	//m_pActionSetFont->setCheckable(true);
	//connect(m_pActionBlod, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	m_pActionSetColour = new QAction(QObject::tr("SetColour"), this);
	//m_pActionSetColour->setCheckable(true);
}

void CInformationRectItem::_CreateConnect()
{

	connect(m_pActionSetFont, SIGNAL(triggered()), this, SLOT(slotSetFont()));
	connect(m_pActionSetColour, SIGNAL(triggered()), this, SLOT(slotSetColor()));

}

void CInformationRectItem::slotSetFont()
{
	/*
	//m_pEventScreenPos
	bool bTriggerOK = false;
	m_ItemFont = QFontDialog::getFont(
		&bTriggerOK,
		this->font(),
		NULL,
		QObject::tr("fontDialog"));

	if (bTriggerOK)
	{
		this->setFont(m_ItemFont);
	}
	this->adjustSize();

	*/
}

void CInformationRectItem::slotSetColor()
{
	QColor colorValue;

	colorValue = QColorDialog::getColor(
		m_LineColor, 
		NULL, 
		QObject::tr("ColorDialog"));

	if (colorValue.isValid())
	{
		m_LineColor = colorValue;
	}
}

void CInformationRectItem::SetLineColor(const QColor& colorValue)
{	
	m_LineColor = colorValue;
}

CInformationTextItem* CInformationRectItem::getTopTextHandle()
{
	return m_pTextTop;
}

CInformationTextItem* CInformationRectItem::getBottomTextHandle()
{
	return m_pTextBottom;
}


//QT_END_NAMESPACE






