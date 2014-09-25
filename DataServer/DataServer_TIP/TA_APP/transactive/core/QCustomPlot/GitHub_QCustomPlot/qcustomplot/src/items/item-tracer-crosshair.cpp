#include "item-tracer-crosshair.h"

#include "../painter.h"
#include "../core.h"
#include "../plottables/plottable-graph.h"



QCPItemTracerCrossHair::QCPItemTracerCrossHair(QCustomPlot *parentPlot) :
QCPAbstractItem(parentPlot)
{
	m_linef_Horizontal = QLineF(0, 0, 0, 0);
	m_bShowHorizontalLine = false;
	m_str_Horizontal_bottom.clear();
	m_str_Horizontal_top.clear();
	m_pointf_Horizontal_bottom = QPointF(0, 0);
	m_pointf_Horizontal_top = QPointF(0, 0);

	m_linef_Vertical = QLineF(0, 0, 0, 0);
	m_bShowVerticalLine = false;
	m_str_Vertical_left.clear();
	m_str_Vertical_right.clear();
	m_pointf_Vertical_left = QPointF(0, 0);
	m_pointf_Vertical_right = QPointF(0, 0);


	setBrush(Qt::NoBrush);
	setSelectedBrush(Qt::NoBrush);
	setPen(QPen(Qt::black));
	//setSelectedPen(QPen(Qt::blue, 2));
	setSelectedPen(QPen(Qt::black));
	setStyle(tsCrosshair);
	setCenterPos(QPointF(0, 0));
}

QCPItemTracerCrossHair::~QCPItemTracerCrossHair()
{
}

/*!
Sets the pen that will be used to draw the line of the tracer

\see setSelectedPen, setBrush
*/
void QCPItemTracerCrossHair::setPen(const QPen &pen)
{
	mPen = pen;
}

/*!
Sets the pen that will be used to draw the line of the tracer when selected

\see setPen, setSelected
*/
void QCPItemTracerCrossHair::setSelectedPen(const QPen &pen)
{
	mSelectedPen = pen;
}

/*!
Sets the brush that will be used to draw any fills of the tracer

\see setSelectedBrush, setPen
*/
void QCPItemTracerCrossHair::setBrush(const QBrush &brush)
{
	mBrush = brush;
}

/*!
Sets the brush that will be used to draw any fills of the tracer, when selected.

\see setBrush, setSelected
*/
void QCPItemTracerCrossHair::setSelectedBrush(const QBrush &brush)
{
	mSelectedBrush = brush;
}



/*!
Sets the style/visual appearance of the tracer.

If you only want to use the tracer \a position as an anchor for other items, set \a style to
\ref tsNone.
*/
void QCPItemTracerCrossHair::setStyle(QCPItemTracerCrossHair::TracerStyle style)
{
	mStyle = style;
}




/* inherits documentation from base class */
double QCPItemTracerCrossHair::selectTest(const QPointF &pos, bool onlySelectable, QVariant *details) const
{
	Q_UNUSED(details)
		if (onlySelectable && !mSelectable)
			return -1;

	QPointF center(m_pointf_center);

	QRect clip = clipRect();
	switch (mStyle)
	{
	case tsNone: 
		return -1;
	case tsCrosshair:
		{
			return qSqrt(qMin(distSqrToLine(QPointF(clip.left(), center.y()), QPointF(clip.right(), center.y()), pos),
				distSqrToLine(QPointF(center.x(), clip.top()), QPointF(center.x(), clip.bottom()), pos)));
		}
	}
	return -1;
}

/* inherits documentation from base class */
void QCPItemTracerCrossHair::draw(QCPPainter *painter)
{
	if (mStyle == tsNone)
	{
		return;
	}
	painter->setPen(mainPen());
	painter->setBrush(mainBrush());

	switch (mStyle)
	{
	case tsCrosshair:
		{
			if (m_bShowVerticalLine)
			{
				painter->drawLine(m_linef_Vertical);
			}
			if (m_bShowHorizontalLine)
			{
				painter->drawLine(m_linef_Horizontal);
			}

 			painter->drawText(m_pointf_Horizontal_top, m_str_Horizontal_top);
 			painter->drawText(m_pointf_Horizontal_bottom, m_str_Horizontal_bottom);
 			painter->drawText(m_pointf_Vertical_left, m_str_Vertical_left);
 			painter->drawText(m_pointf_Vertical_right, m_str_Vertical_right);

// 			painter->drawText(100, 100, m_str_Horizontal_top);
// 			painter->drawText(200, 200, m_str_Horizontal_bottom);
// 			painter->drawText(300, 300, m_str_Vertical_left);
// 			painter->drawText(400, 400, m_str_Vertical_right);
			break;
		}
	default:
		return;
	}
}

/*! \internal

Returns the pen that should be used for drawing lines. Returns mPen when the item is not selected
and mSelectedPen when it is.
*/
QPen QCPItemTracerCrossHair::mainPen() const
{
	return mSelected ? mSelectedPen : mPen;
}

/*! \internal

Returns the brush that should be used for drawing fills of the item. Returns mBrush when the item
is not selected and mSelectedBrush when it is.
*/
QBrush QCPItemTracerCrossHair::mainBrush() const
{
	return mSelected ? mSelectedBrush : mBrush;
}

void QCPItemTracerCrossHair::setCenterPos( const QPointF& posf )
{
	m_pointf_center = posf;
	_UpdateItemInfo();
}

void QCPItemTracerCrossHair::_UpdateItemInfo()
{
	QPointF center(m_pointf_center);
	QRect clip = clipRect();
	

	if (center.x() > clip.left() && center.x() < clip.right())
	{
		m_bShowHorizontalLine = true;
		m_linef_Horizontal = QLineF(center.x(), clip.bottom(), center.x(), clip.top());
		m_pointf_Horizontal_bottom = m_linef_Horizontal.p1();
		m_pointf_Horizontal_top = m_linef_Horizontal.p2();
	}
	else
	{
		m_bShowHorizontalLine = false;
		m_linef_Horizontal = QLineF(clip.topLeft(), clip.topRight());
		m_pointf_Horizontal_bottom = QPointF(0, 0);
		m_pointf_Horizontal_top = QPointF(0, 0);
	}

	//
	if (center.y() > clip.top() && center.y() < clip.bottom())
	{
		m_bShowVerticalLine = true;
		m_linef_Vertical = QLineF(clip.left(), center.y(), clip.right(), center.y());
		m_pointf_Vertical_left = m_linef_Vertical.p1();
		m_pointf_Vertical_right = m_linef_Vertical.p2();

	}
	else
	{
		m_bShowVerticalLine = false;
		m_linef_Vertical = QLineF(clip.topLeft(), clip.bottomLeft());
		m_pointf_Vertical_left = QPointF(0, 0);
		m_pointf_Vertical_right = QPointF(0, 0);
	}


	m_str_Horizontal_bottom = "Horizontal_bottom";
	m_str_Horizontal_top = "Horizontal_top";
	m_str_Vertical_left = "Vertical_left";
	m_str_Vertical_right = "Vertical_right";


	m_pointf_Horizontal_bottom.setX(m_pointf_Horizontal_bottom.x() + 5);
	m_pointf_Horizontal_bottom.setY(m_pointf_Horizontal_bottom.y() - 20);
	m_pointf_Horizontal_top.setX(m_pointf_Horizontal_top.x() + 5);
	m_pointf_Horizontal_top.setY(m_pointf_Horizontal_top.y() - 20);
	m_pointf_Vertical_left.setX(m_pointf_Vertical_left.x() + 5);
	m_pointf_Vertical_left.setY(m_pointf_Vertical_left.y() - 20);
	m_pointf_Vertical_right.setX(m_pointf_Vertical_right.x() + 5);
	m_pointf_Vertical_right.setY(m_pointf_Vertical_right.y() - 20);


}
