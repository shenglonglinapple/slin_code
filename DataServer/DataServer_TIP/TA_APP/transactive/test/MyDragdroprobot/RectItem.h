#ifndef __CLASS_CRECT_ITEM__HH__
#define __CLASS_CRECT_ITEM__HH__

#include <QtGui/QtGui>
#include <QtGui/QGraphicsItem>
#include <QtGui/QGraphicsScene>

//! [0]
class CRectItem : public QGraphicsItem
{
public:
    CRectItem(QGraphicsItem *parent = 0, QGraphicsScene *scene = 0);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
protected:
	// dragEnterEvent 当拖拽后进入接收拖拽的控件时触发
	//void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	// dragLeaveEvent 当拖拽(没有释放鼠标时)离开接收拖拽的控件时触发
	//void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	// dragMoveEvent 拖拽状态下在接收拖拽的控件内移动鼠标时触发

	//dropEvent 拖拽状态下释放鼠标时触发
	//void dropEvent(QGraphicsSceneDragDropEvent *event);
public:
	void setColor(QColor nColorValue);
	void setItemPos( QPointF pointValue );
private:
	qreal  m_nBoundingRectWidthHalf;
	qreal  m_nBoundingRectHeightHalf;
	qreal  m_nBoundingRectWidth;
	qreal  m_nBoundingRectHeight;
	QRectF m_rectDrawInScenePos;
	QRectF m_rectOutSideBoundingInScenePos;

private:
    QColor m_nColor;
	QColor m_nDragColor;
	bool m_bDragOver;
	QGraphicsScene* m_pSceneRef;
};
//! [0]

#endif
