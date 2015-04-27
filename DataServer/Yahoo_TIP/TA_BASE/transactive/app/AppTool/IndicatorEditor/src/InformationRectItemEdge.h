#ifndef  __DEF__CLASS__INFORMATION_RECT_ITEM_EDGE_HH__
#define  __DEF__CLASS__INFORMATION_RECT_ITEM_EDGE_HH__

#include "CommonDef.h"

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



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CInformationBase;

class CInformationRectItemEdge : public QGraphicsObject
{
	Q_OBJECT
public:
	enum EEdgeType
	{
		EEdgeType_Begin,
		EdgeType_Source_Middle_To_Dest_Top,
		EdgeType_Source_Middle_To_Dest_Middle,
		EdgeType_Source_Middle_To_Dest_Bottom,
		EEdgeType_End,
	};
public:
    CInformationRectItemEdge(
		CInformationBase* sourceNode, 
		CInformationBase* destNode, 
		EEdgeType nEdgeType = EEdgeType_Begin,
		QGraphicsItem* parent = 0,
		QGraphicsScene* scene = 0);

	virtual ~CInformationRectItemEdge();

    CInformationBase* getSourceNode() const;
    CInformationBase* getDestNode() const;
	EProjectClassType getClassType() const;
	int type() const;


public slots:
	void slotSetFont();
	void slotSetColor();

public:
    void adjustEdgeLocation();
protected:
	//在函数后用const表示不能改变类的成员
	//该函数为指定后面的绘图区域的外边框
    QRectF boundingRect() const;
    void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
	QPainterPath shape()const;
protected:
	void mousePressEvent(QGraphicsSceneMouseEvent* pEvent);
	void mouseMoveEvent(QGraphicsSceneMouseEvent* pEvent);
	void mouseReleaseEvent(QGraphicsSceneMouseEvent* pEvent);

	void hoverEnterEvent(QGraphicsSceneHoverEvent* pEvent);
	void hoverMoveEvent(QGraphicsSceneHoverEvent* pEvent);
	void hoverLeaveEvent(QGraphicsSceneHoverEvent* pEvent);

protected:
	void contextMenuEvent(QGraphicsSceneContextMenuEvent* event);
private:
	void _CreateActions();
	void _CreateConnect();
private:
	QAction* m_pActionSetFont;
	QAction* m_pActionSetColour;
	QPointF m_pEventScreenPos;
private:
	QColor m_ItemColor;
	QFont m_ItemFont;

private:
	bool m_bMouseInShap;
	bool m_bMouseLeftButtonDown;
	QCursor* m_pCurrentCursor;
	QPointF m_pointBeginMouseLeftButtonDown;
	QPointF m_pointEndMouseLeftButtonDown;
	qreal m_fWidthPenLine;
	QLineF m_LineSourceDest;
	double m_fAngle;

	QPointF m_pointSourceArrowP1;
	QPointF m_pointSourceArrowP2;  
	QPointF m_pointDestArrowP1;
	QPointF m_pointDestArrowP2;

private:
	EEdgeType m_nEdgeType;
    CInformationBase* m_pSourceNodeRef;
	CInformationBase* m_pDestNodeRef;

    QPointF m_pointSource;
    QPointF m_pointDest;
    qreal m_fArrowSize;
private:
	QPolygonF m_PolygonBounding;
private:
	//UI
	QPen m_PenLine;
	QPen m_PenLineBounding;
	EProjectClassType m_nClassType;
};


//QT_END_NAMESPACE
#endif //__DEF__CLASS__INFORMATION_RECT_ITEM_EDGE_HH__


