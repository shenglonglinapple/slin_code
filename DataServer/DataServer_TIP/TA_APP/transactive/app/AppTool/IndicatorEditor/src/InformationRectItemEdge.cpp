#include "InformationRectItemEdge.h"
#include <math.h>
#include <QtGui/QtGui>
#include "InformationBase.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

static const double DEF_VALUE_Pi = 3.14159265358979323846264338327950288419717;
static const double DEF_VALUE_TwoPi = 2.0 * DEF_VALUE_Pi;
static const qreal DEF_VALUE_fArrowSize = 8;




CInformationRectItemEdge::CInformationRectItemEdge( 
	CInformationBase* sourceNode, 
	CInformationBase* destNode,
	EEdgeType nEdgeType,
	QGraphicsItem* parent,
	QGraphicsScene* scene
)
:QGraphicsObject(parent)
{

	m_nClassType = ClassType_CInformationRectItemEdge;

	m_fArrowSize = DEF_VALUE_fArrowSize;
	m_pSourceNodeRef = NULL;
	m_pDestNodeRef = NULL;
	m_fWidthPenLine = 2;

	m_ItemColor = Qt::blue;
	m_PenLine = QPen(m_ItemColor, m_fWidthPenLine, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
	m_PenLineBounding = QPen(Qt::red, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin);
	m_PenLine.setColor(m_ItemColor);
	m_PenLineBounding.setColor(Qt::red);

	m_nEdgeType = nEdgeType;
	m_pSourceNodeRef = sourceNode;
	m_pDestNodeRef = destNode;

	m_pCurrentCursor = new QCursor();
	m_bMouseLeftButtonDown = false;	
	m_bMouseInShap = false;
	m_fAngle = 0;

	//setAcceptedMouseButtons(0);
	adjustEdgeLocation();

	setZValue(0);
	setAcceptsHoverEvents(true);
	setAcceptDrops(true);
	setFlags(QGraphicsItem::ItemIsSelectable);


	_CreateActions();
	_CreateConnect();
}


CInformationRectItemEdge::~CInformationRectItemEdge()
{
	m_pSourceNodeRef = NULL;
	m_pDestNodeRef = NULL;
}




CInformationBase* CInformationRectItemEdge::getSourceNode() const
{
    return m_pSourceNodeRef;
}

CInformationBase *CInformationRectItemEdge::getDestNode() const
{
    return m_pDestNodeRef;
}



void CInformationRectItemEdge::adjustEdgeLocation()
{
    if (NULL == m_pSourceNodeRef || NULL == m_pDestNodeRef)
	{
        return;
	}

	m_pointSource = m_pSourceNodeRef->getPointRectRightMiddle();


	switch (m_nEdgeType)
	{
	case EdgeType_Source_Middle_To_Dest_Top:
		{
			m_pointDest = m_pDestNodeRef->getPointRectLeftTopMiddle();
			break;
		}
	case EdgeType_Source_Middle_To_Dest_Middle:
		{
			m_pointDest = m_pDestNodeRef->getPointRectLeftMiddle();
			break;
		}		
	case EdgeType_Source_Middle_To_Dest_Bottom:
		{
			m_pointDest = m_pDestNodeRef->getPointRectLeftBottomMiddle();
			break;
		}
	default:
		m_pointDest = m_pDestNodeRef->getPointRectLeftMiddle();
		break;
	}



	m_LineSourceDest = QLineF(m_pointSource, m_pointDest);
	if (qFuzzyCompare(m_LineSourceDest.length(), qreal(0.)))
	{
		return;
	}

	// Draw the arrows
	m_fAngle = ::acos(m_LineSourceDest.dx() / m_LineSourceDest.length());
	if (m_LineSourceDest.dy() >= 0)
	{
		m_fAngle = DEF_VALUE_TwoPi - m_fAngle;
	}

	m_pointSourceArrowP1 = m_pointSource + QPointF(sin(m_fAngle + DEF_VALUE_Pi / 3) * m_fArrowSize, cos(m_fAngle + DEF_VALUE_Pi / 3) * m_fArrowSize);
	m_pointSourceArrowP2 = m_pointSource + QPointF(sin(m_fAngle + DEF_VALUE_Pi - DEF_VALUE_Pi / 3) * m_fArrowSize, cos(m_fAngle + DEF_VALUE_Pi - DEF_VALUE_Pi / 3) * m_fArrowSize);
	m_pointDestArrowP1 = m_pointDest + QPointF(sin(m_fAngle - DEF_VALUE_Pi / 3) * m_fArrowSize, cos(m_fAngle - DEF_VALUE_Pi / 3) * m_fArrowSize);
	m_pointDestArrowP2 = m_pointDest + QPointF(sin(m_fAngle - DEF_VALUE_Pi + DEF_VALUE_Pi / 3) * m_fArrowSize, cos(m_fAngle - DEF_VALUE_Pi + DEF_VALUE_Pi / 3) * m_fArrowSize);

	m_PolygonBounding = (QPolygonF() << m_LineSourceDest.p1() << m_pointSourceArrowP1 << m_pointDestArrowP1 << m_LineSourceDest.p2() << m_pointDestArrowP2 << m_pointSourceArrowP2);



	//notification  shape change
	prepareGeometryChange();
}

QRectF CInformationRectItemEdge::boundingRect() const
{
    if (NULL == m_pSourceNodeRef || NULL == m_pDestNodeRef)
	{
		return QRectF();
	}
	
	qreal extra = (m_fWidthPenLine + m_fArrowSize) / 2.0;
	QSizeF sizeRect = QSizeF(m_pointDest.x() - m_pointSource.x(), m_pointDest.y() - m_pointSource.y());

	return QRectF(m_pointSource, sizeRect).normalized().adjusted(-extra, -extra, extra, extra);
}


QPainterPath CInformationRectItemEdge::shape() const
{
	//QPainterPath是一个绘图操作的容器
	//mouse in area
	QPainterPath path;
	path.addPolygon(m_PolygonBounding);// void addPolygon(const QPolygonF &polygon);
	return path;
}


void CInformationRectItemEdge::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{

	if (!m_pSourceNodeRef || !m_pDestNodeRef)
	{
		return;
	}

	if (true == m_bMouseInShap || true == m_bMouseLeftButtonDown)
	{
		painter->setPen(m_PenLineBounding);
		painter->drawPolygon(m_PolygonBounding);

	}

	// Draw the line itself

	m_PenLine.setColor(m_ItemColor);
	painter->setPen(m_PenLine);

	painter->drawLine(m_LineSourceDest);

	painter->setBrush(m_ItemColor);//设置画刷颜色

	//painter->drawPolygon(QPolygonF() << m_LineSourceDest.p1() << m_pointSourceArrowP1 << m_pointSourceArrowP2);
	painter->drawPolygon(QPolygonF() << m_LineSourceDest.p2() << m_pointDestArrowP1 << m_pointDestArrowP2);

}




void CInformationRectItemEdge::hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();

	m_bMouseInShap = true;
	m_pCurrentCursor->setShape(Qt::PointingHandCursor);
	this->setCursor(*m_pCurrentCursor);
	

	this->update();
	QGraphicsItem::hoverEnterEvent(pEvent);
}

void CInformationRectItemEdge::hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	//mouse move around the rect
	QPointF pointCurrent = pEvent->scenePos();


	this->update();
	QGraphicsItem::hoverMoveEvent(pEvent);
}


void CInformationRectItemEdge::hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent)
{
	m_bMouseInShap = false;

	m_pCurrentCursor->setShape(Qt::ArrowCursor);
	this->setCursor(*m_pCurrentCursor);

	this->update();
	QGraphicsItem::hoverLeaveEvent(pEvent);
}

void CInformationRectItemEdge::mousePressEvent(QGraphicsSceneMouseEvent* pEvent)
{
	if (pEvent->button() == Qt::LeftButton)
	{
		m_bMouseLeftButtonDown = true;

		m_pCurrentCursor->setShape(Qt::PointingHandCursor);
		this->setCursor(*m_pCurrentCursor);

		m_pointBeginMouseLeftButtonDown = pEvent->scenePos();
	}

	this->update();

	QGraphicsItem::mousePressEvent(pEvent);
}

void CInformationRectItemEdge::mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent)
{
	QRectF rectAfterMove;
	QPointF pointMove;

	if (false == m_bMouseLeftButtonDown)
	{
		update();
		QGraphicsItem::mouseMoveEvent(pEvent);
		return;
	}

	m_pointEndMouseLeftButtonDown = pEvent->scenePos();
	pointMove = m_pointEndMouseLeftButtonDown - m_pointBeginMouseLeftButtonDown;
	m_pointBeginMouseLeftButtonDown = m_pointEndMouseLeftButtonDown;


}

void CInformationRectItemEdge::mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent)
{
	m_bMouseLeftButtonDown = false;
	update();
	QGraphicsItem::mouseReleaseEvent(pEvent);
}

EProjectClassType CInformationRectItemEdge::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CInformationRectItemEdge::type() const
{
	return m_nClassType;
}

void CInformationRectItemEdge::contextMenuEvent( QGraphicsSceneContextMenuEvent* event )
{
	QMenu menu;
	m_pEventScreenPos = event->screenPos();
	m_pEventScreenPos.setX(m_pEventScreenPos.x() + 50);

	//menu.addAction(m_pActionSetFont);
	menu.addAction(m_pActionSetColour);
	menu.exec(event->screenPos());
}

void CInformationRectItemEdge::_CreateActions()
{
	m_pActionSetFont = new QAction(QObject::tr("SetFont"), this);
	//m_pActionSetFont->setCheckable(true);

	m_pActionSetColour = new QAction(QObject::tr("SetColour"), this);
	//m_pActionSetColour->setCheckable(true);
}

void CInformationRectItemEdge::_CreateConnect()
{
	connect(m_pActionSetFont, SIGNAL(triggered()), this, SLOT(slotSetFont()));
	connect(m_pActionSetColour, SIGNAL(triggered()), this, SLOT(slotSetColor()));

}

void CInformationRectItemEdge::slotSetFont()
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
		//this->setFont(m_ItemFont);
	}
	//this->adjustSize();
	*/
}

void CInformationRectItemEdge::slotSetColor()
{
	QColor colorValue;

	colorValue = QColorDialog::getColor(
		m_ItemColor, 
		NULL, 
		QObject::tr("ColorDialog"));

	if (colorValue.isValid())
	{
		m_ItemColor = colorValue;
	}
}

//QT_END_NAMESPACE




