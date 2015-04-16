#ifndef  __DEF__CLASS__MY_RECT_GRAPHICS_ITEM_HH__
#define  __DEF__CLASS__MY_RECT_GRAPHICS_ITEM_HH__


#include <QtCore/QTimer>
#include <QtCore/QRectF>

#include <QtGui/QCursor>
#include <QtGui/QPainter>
#include <QtGui/QPainterPath>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsSceneHoverEvent>
#include <QtGui/QGraphicsSceneMouseEvent>


#include <QtGui/QGraphicsObject>
#include <QtGui/QGraphicsWidget>

#include "RectAreaBoundingAreas.h"



class CMyRectGraphicsItem : public QGraphicsItem
{
public:
    CMyRectGraphicsItem();
	virtual ~CMyRectGraphicsItem();
public:
    QRectF boundingRect()const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
    QPainterPath shape()const;
    
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);

    void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent);
private:
	void _ResetRect(QRectF rectDraw);
	void _ResetAreas();
	void _SetCursorShape(QPointF pointCurrent, QCursor* pCurrentCursor);
	void _LogPointF(const std::string& strLogInfo, QPointF pointTmp);
	void _LogRectF(const std::string& strLogInfo, QRectF rectTmp);
private:
    bool m_bMouseLeftButtonDown;
    QCursor* m_pCurrentCursor;
    QPointF m_pointBeginMouseLeftButtonDown;
    QPointF m_pointEndMouseLeftButtonDown;
	CRectAreaBounding::RectAreaBoundingType m_nMouseMoveType;

private:
	qreal  m_nBoundingRectWidthHalf;
	qreal  m_nBoundingRectHeightHalf;
	qreal  m_nBoundingRectWidth;
	qreal  m_nBoundingRectHeight;
	QRectF m_rectDraw;
	QRectF m_rectBounding;

	CRectAreaBoundingAreas* m_pRectAreaBoundingAreas;

};

#endif // __DEF__CLASS__MY_RECT_GRAPHICS_ITEM_HH__














