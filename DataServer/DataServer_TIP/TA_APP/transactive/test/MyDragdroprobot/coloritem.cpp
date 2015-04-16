#include <QtGui>

#include "coloritem.h"

//! [0]
//ColorItem::ColorItem(): color(qrand() % 256, qrand() % 256, qrand() % 256)
ColorItem::ColorItem()
{
	int nColorR = qrand() % 256;
	int nColorG = qrand() % 256;
	int nColorB = qrand() % 256;

	m_nColor.setRgb(nColorR, nColorG, nColorB);

	setToolTip(QString("QColor(%1, %2, %3)\n%4")
		.arg(m_nColor.red()).arg(m_nColor.green()).arg(m_nColor.blue())
		.arg("Click and drag this color onto the robot!"));
	setCursor(Qt::OpenHandCursor);
	setAcceptedMouseButtons(Qt::LeftButton);
	setAcceptDrops(true);

}
//! [0]

//! [1]
QRectF ColorItem::boundingRect() const
{
	return QRectF(-15.5, -15.5, 34, 34);
}
//! [1]

//! [2]
void ColorItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
	Q_UNUSED(option);
	Q_UNUSED(widget);

	painter->setPen(Qt::NoPen);
	painter->setBrush(Qt::darkGray);
	painter->drawEllipse(-12, -12, 30, 30);

	painter->setPen(QPen(Qt::black, 1));
	painter->setBrush(QBrush(m_nColor));
	painter->drawEllipse(-15, -15, 30, 30);
}
//! [2]

//! [3]
void ColorItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::ClosedHandCursor);
}
//! [3]

//! [5]
void ColorItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
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

	QDrag* drag = new QDrag(event->widget());
	QMimeData* mime = new QMimeData();
	QString strText;
	strText = QString("#%1%2%3").arg(m_nColor.red(), 2, 16, QLatin1Char('0'))
		.arg(m_nColor.green(), 2, 16, QLatin1Char('0'))
		.arg(m_nColor.blue(), 2, 16, QLatin1Char('0'));


	drag->setMimeData(mime);

	mime->setColorData(m_nColor);
	mime->setText(strText);

	QPixmap pixmap(34, 34);
	pixmap.fill(Qt::white);

	QPainter painter(&pixmap);
	painter.translate(15, 15);
	painter.setRenderHint(QPainter::Antialiasing);
	this->paint(&painter, 0, 0);
	painter.end();

	pixmap.setMask(pixmap.createHeuristicMask());

	drag->setPixmap(pixmap);
	drag->setHotSpot(QPoint(15, 20));

	drag->exec();
	setCursor(Qt::OpenHandCursor);
}
//! [8]

//! [4]
void ColorItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
	setCursor(Qt::OpenHandCursor);
}


void ColorItem::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
	if (event->mimeData()->hasColor()) 
	{
		event->setAccepted(true);
		m_bDragOver = true;
		update();
	} 
	else 
	{
		event->setAccepted(false);
	}
}
//! [1]

//! [2]
void ColorItem::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	Q_UNUSED(event);
	m_bDragOver = false;
	update();
}
//! [2]

//! [3]
void ColorItem::dropEvent(QGraphicsSceneDragDropEvent *event)
{
	m_bDragOver = false;
	if (event->mimeData()->hasColor())
	{
		m_nDragColor = qvariant_cast<QColor>(event->mimeData()->colorData());
		m_nColor = m_nDragColor;
	}
	update();
}

void ColorItem::setColor( QColor nColorValue )
{
	m_nColor = nColorValue;
	update();
}

//! [4]
