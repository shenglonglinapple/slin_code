#ifndef  __DEF__CLASS_USER_DEFINE_INFORMATION_HH__
#define  __DEF__CLASS_USER_DEFINE_INFORMATION_HH__

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

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CRelativeHistoryInfomation;
class CEqualityOperator;
class CInformationNode;
class CInformationBase;
class CInformationTextItem;

class CUserDefineInfomation : public QGraphicsItem
{
public:
    CUserDefineInfomation(QRectF rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	virtual ~CUserDefineInfomation();
public:
	QRectF boundingRect() const;
	void paint(QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget);
public:
	void adjustPos(QPointF pointItemBegin);
	EProjectClassType getClassType() const;
	int type() const;
private:
	//rect
	QRectF m_rectBounding;

private:
	QString m_strTextTitle;
	CInformationTextItem* m_pTextTitle;
	QFont m_fontTextTitle;
	qreal m_nTextTitleX;
	qreal m_nTextTitleY;
	qreal m_nTextTitleWidth;
	QGraphicsScene* m_pSceneRef;

private:
	QList<CInformationBase*> m_lstNode;
	EProjectClassType m_nClassType;
};




//QT_END_NAMESPACE

#endif // __DEF__CLASS_USER_DEFINE_INFORMATION_HH__














