#ifndef  __DEF__CLASS__RECT_ITEM_IN_BOX_HH__
#define  __DEF__CLASS__RECT_ITEM_IN_BOX_HH__

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
#include "InformationRectItemEdge.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CInformationTextItem;

class CRectItemInBox : public QGraphicsObject
{
	Q_OBJECT

public:
    CRectItemInBox(const QRectF& rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	virtual ~CRectItemInBox();

public slots:
	void slotSetFont();
	void slotSetColor();
public:
    QRectF boundingRect()const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainterPath shape()const;
public:
	EProjectClassType getClassType() const;
	int type() const;

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

	CInformationRectItemEdge::EEdgeType checkEdgeType(QPointF pointPos);
public:
	bool isColliding();
protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent);
private:
	void _ResetRect(QRectF rectDraw);
	void _ResetRectNotUpdate(QRectF rectDraw);
	void _ResetPoints();
	void _ResetAreas();
	void _SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor);
private:
	void _CreateActions();
	void _CreateConnect();
private:
	QAction* m_pActionSetFont;
	QAction* m_pActionSetColour;
	QPointF m_pEventScreenPos;
private:
	QColor m_LineColor;
	QFont m_TextFontTop;
	QColor m_TextColorTop;
	QFont m_TextFontBottom;
	QColor m_TextColorBottom;
	QPen m_PenLine;

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
	CInformationTextItem* m_pTextTop;
	QPointF m_pointTextTop;
	qreal m_nTextTopWidth;

	QString m_strTextBottom;
	CInformationTextItem* m_pTextBottom;
	QPointF m_pointTextBottom;
	qreal m_nTextBottomWidth;

private:
	 EProjectClassType m_nClassType;

};

//QT_END_NAMESPACE

#endif // __DEF__CLASS__RECT_ITEM_IN_BOX_HH__














