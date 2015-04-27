#ifndef  __DEF__CLASS__INFORMATION_RECT_ITEM_HH__
#define  __DEF__CLASS__INFORMATION_RECT_ITEM_HH__

#include <QtCore/QList>
#include <QtCore/QPointF>
#include <QtCore/QRectF>
#include <QtCore/QLineF>

#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsLineItem>
#include <QtGui/QGraphicsTextItem>
#include <QtGui/QGraphicsObject>
#include <QtGui/QGraphicsWidget>

#include <QtGui/QCursor>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneHoverEvent>
#include <QtGui/QGraphicsSceneMouseEvent>

#include "CommonDef.h"
#include "BoundingRectAreas.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CInformationRectItem : public QGraphicsObject
{
public:
    CInformationRectItem(const QRectF& rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	virtual ~CInformationRectItem();
public:
    QRectF boundingRect()const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainterPath shape()const;
public:
	EProjectClassType getClassType() const;
	int type() const;
public:
	virtual void adjustAllPos();
public:
	void setItemPos(QPointF point);
	void setItemRect(QRectF rect);

	QPointF getItemPos();
	qreal getItemWidth();
	qreal getItemHeight();

	QPointF getPointRectLeftTopMiddle();
	QPointF getPointRectLeftMiddle();
	QPointF getPointRectLeftBottomMiddle();
	QPointF getPointRectRightMiddle();
public:
	void setTopText(const QString& strValue);
	void setBottomText(const QString& strValue);

	QPixmap image() const;
public:
	bool isColliding();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent);
private:
	void _ResetRect(QRectF rectDraw);
	void _ResetPoints();
	void _ResetAreas();
	void _SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor);
	QRectF _GetRectAfterMove(QPointF pointMove);
private:
    bool m_bMouseLeftButtonDown;
    QCursor* m_pCurrentCursor;
    QPointF m_pointBeginMouseLeftButtonDown;
    QPointF m_pointEndMouseLeftButtonDown;
	CBoundingRect::EBoundingRectType m_nMouseMoveType;

private:
	//rect
	qreal  m_nBoundingRectWidthHalf;
	qreal  m_nBoundingRectHeightHalf;
	qreal  m_nBoundingRectWidth;
	qreal  m_nBoundingRectHeight;
	QRectF m_rectDrawInScenePos;
	QRectF m_rectOutSideBoundingInScenePos;
	QRectF m_rectInSideBoundingInScenePos;
	QRectF m_rectInSideTopPartInScenePos;
	QRectF m_rectInSideBottomPartInScenePos;
	//QGraphicsRectItem* m_pGraphicsRectItem;
	CBoundingRectAreas* m_pRectAreaBoundingAreas;

	QPointF m_pointRectLeftTopMiddle;
	QPointF m_pointRectLeftMiddle;
	QPointF m_pointRectLeftBottomMiddle;
	QPointF m_pointRectBottomMiddle;
	QPointF m_pointRectRightMiddle;
	QPointF m_pointRectTopMiddle;
private:
	//line
	QLineF m_lineMiddle;
	//QGraphicsLineItem* m_pGraphicsLineItem;

private:
	QString m_strTextTop;
	//QGraphicsTextItem* m_pTextTop;
	QPointF m_pointTextTop;
	qreal m_nTextTopWidth;

	QString m_strTextBottom;
	//QGraphicsTextItem* m_pTextBottom;
	QPointF m_pointTextBottom;
	qreal m_nTextBottomWidth;

private:
	 EProjectClassType m_nClassType;
};

//QT_END_NAMESPACE

#endif // __DEF__CLASS__INFORMATION_RECT_ITEM_HH__














