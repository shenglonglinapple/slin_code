#include <QtGui>

#include "RectItem.h"


static const qreal DEF_VALUE_InfomationRectItem_X = 100;
static const qreal DEF_VALUE_InfomationRectItem_Y = 300;
static const qreal DEF_VALUE_InfomationRectItem_Width = 150;
static const qreal DEF_VALUE_InfomationRectItem_Height = 150;



//! [0]
//ColorItem::ColorItem(): color(qrand() % 256, qrand() % 256, qrand() % 256)
CRectItem::CRectItem( QGraphicsItem *parent /*= 0*/, QGraphicsScene *scene /*= 0*/ )
:QGraphicsItem(parent, scene)
{
	int nColorR = qrand() % 256;
	int nColorG = qrand() % 256;
	int nColorB = qrand() % 256;

	m_pSceneRef = scene;
	m_nColor.setRgb(nColorR, nColorG, nColorB);
// 
// 	setToolTip(QString("QColor(%1, %2, %3)\n%4")
// 		.arg(m_nColor.red()).arg(m_nColor.green()).arg(m_nColor.blue())
// 		.arg("Click and drag this color onto the robot!"));

	setToolTip(QString("%1").arg("Click and drag this Item"));
	setCursor(Qt::OpenHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptDrops(true);
	//setDragDropMode(QAbstractItemView::DragOnly);//这里设置此空间之支持向外拖拽功能(即只能从此控件向别的控件拖拽操作,而不支持别的控件向此控件拖拽)


	m_nBoundingRectWidthHalf = 4;
	m_nBoundingRectHeightHalf = 4;
	m_nBoundingRectWidth = m_nBoundingRectWidthHalf * 2;
	m_nBoundingRectHeight = m_nBoundingRectHeightHalf * 2;

	m_rectDrawInScenePos = QRectF(DEF_VALUE_InfomationRectItem_X, DEF_VALUE_InfomationRectItem_Y, 
		DEF_VALUE_InfomationRectItem_Width, DEF_VALUE_InfomationRectItem_Height);

	m_rectOutSideBoundingInScenePos.setLeft(m_rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_rectOutSideBoundingInScenePos.setTop(m_rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_rectOutSideBoundingInScenePos.setWidth(m_rectDrawInScenePos.width() + m_nBoundingRectWidth);
	m_rectOutSideBoundingInScenePos.setHeight(m_rectDrawInScenePos.height() + m_nBoundingRectHeight);


}

//! [0]

//! [1]
QRectF CRectItem::boundingRect() const
{
	return m_rectOutSideBoundingInScenePos;
}
//! [1]

//! [2]
void CRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

// 	painter->setPen(Qt::NoPen);
// 	painter->setBrush(Qt::darkGray);
// 	painter->drawEllipse(-12, -12, 30, 30);

	//painter->setPen(QPen(Qt::black, 1));
	//painter->setBrush(QBrush(m_nColor));
	//painter->drawRect(m_rectDrawInScenePos);

	painter->setPen(QPen(m_nColor, 1));
	painter->drawRect(m_rectDrawInScenePos);
}
//! [2]

//! [3]
void CRectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::ClosedHandCursor);
}
//! [3]

//! [5]
void CRectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
	QPoint pointStart = event->screenPos();
	QPoint pointEnd = event->buttonDownScreenPos(Qt::LeftButton);
	QLineF lineStarEnd(pointStart, pointEnd);
	qreal nLineLength = lineStarEnd.length();
	qreal nLineMinLength = QApplication::startDragDistance();

	//if (QLineF(event->screenPos(), event->buttonDownScreenPos(Qt::LeftButton)).length() < QApplication::startDragDistance())
	if (nLineLength < nLineMinLength)
	{
		return;
	}

	QPointF pointMouse = event->scenePos();
	QPoint pointHot(pointMouse.x() - m_rectDrawInScenePos.x(),  pointMouse.y() - m_rectDrawInScenePos.y());

	QDrag* drag = new QDrag(event->widget());
	QMimeData* mime = new QMimeData();
	QString strText;
	strText = QString("#%1%2%3").arg(m_nColor.red(), 2, 16, QLatin1Char('0'))
		.arg(m_nColor.green(), 2, 16, QLatin1Char('0'))
		.arg(m_nColor.blue(), 2, 16, QLatin1Char('0'));


	drag->setMimeData(mime);

	mime->setColorData(m_nColor);
	mime->setText(strText);
	QString strXValue = QString("%1").arg(pointHot.x());
	QString strYValue = QString("%1").arg(pointHot.y());
	mime->setData("xValue", QByteArray(strXValue.toStdString().c_str()));
	mime->setData("yValue", QByteArray(strYValue.toStdString().c_str()));

	QPixmap pixmap(m_rectOutSideBoundingInScenePos.width(), m_rectOutSideBoundingInScenePos.height());
	pixmap.fill(Qt::white);

	QPainter painter(&pixmap);
	//painter.translate(15, 15);
	//painter.translate(m_rectOutSideBoundingInScenePos.x(), m_rectOutSideBoundingInScenePos.y());
	painter.setRenderHint(QPainter::Antialiasing);
// 	painter.setPen(QPen(Qt::black, 1));
// 	painter.setBrush(QBrush(m_nColor));
	painter.setPen(QPen(m_nColor, 1));
	painter.drawRect(QRectF(0, 0, m_rectDrawInScenePos.width(), m_rectDrawInScenePos.height()));
	painter.end();

	pixmap.setMask(pixmap.createHeuristicMask());

	drag->setPixmap(pixmap);
	drag->setHotSpot(QPoint(pointHot));
	//drag->setHotSpot(QPoint(0,0));

	//drag->exec();
	drag->exec(Qt::MoveAction);
	setCursor(Qt::OpenHandCursor);
	//m_pSceneRef->update();
	this->scene()->update();
}
//! [8]

//! [4]
void CRectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}



void CRectItem::setColor( QColor nColorValue )
{
	m_nColor = nColorValue;
	update();
}


void CRectItem::setItemPos( QPointF pointValue )
{
	QRectF rect;
	rect.setX(pointValue.x());
	rect.setY(pointValue.y());
	rect.setWidth(m_rectDrawInScenePos.width());
	rect.setHeight(m_rectDrawInScenePos.height());
	m_rectDrawInScenePos = rect;

	m_rectOutSideBoundingInScenePos.setLeft(m_rectDrawInScenePos.left() - m_nBoundingRectWidthHalf);
	m_rectOutSideBoundingInScenePos.setTop(m_rectDrawInScenePos.top() - m_nBoundingRectHeightHalf);
	m_rectOutSideBoundingInScenePos.setWidth(m_rectDrawInScenePos.width() + m_nBoundingRectWidth);
	m_rectOutSideBoundingInScenePos.setHeight(m_rectDrawInScenePos.height() + m_nBoundingRectHeight);

	prepareGeometryChange();
	update();
}

//! [4]
