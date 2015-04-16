#ifndef COLORITEM_H
#define COLORITEM_H

#include <QtGui/QtGui>
#include <QGraphicsItem>

//! [0]
class ColorItem : public QGraphicsItem
{
public:
    ColorItem();

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
protected:
	void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
	void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
	void dropEvent(QGraphicsSceneDragDropEvent *event);
public:
	void setColor(QColor nColorValue);
private:
    QColor m_nColor;

	QColor m_nDragColor;
	bool m_bDragOver;
};
//! [0]

#endif
