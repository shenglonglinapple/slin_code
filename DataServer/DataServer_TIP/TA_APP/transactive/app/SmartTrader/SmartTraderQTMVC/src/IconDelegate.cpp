#include "IconDelegate.h"

#include <QtGui/QApplication>
#include <QtCore/QCoreApplication>
#include <QtGui/QPainter>
#include <QtGui/QPicture>
#include <QtGui/QColor>
#include <QtGui/QPen>

#include "ItemUserInstrumentInfo.h"
#include "ConfigInfo.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

static const int DEF_VALUE_INT_SYBOL_Triangle_Tail_Length = 1;
static const int DEF_VALUE_INT_SYBOL_Triangle_Bot_Half_With = 6;
static const int DEF_VALUE_INT_SYBOL_Circle_Radius = 3;//The radius of the circle


IconDelegate::IconDelegate( QObject *parent /*= 0*/ ) : QItemDelegate(parent)
{

}

void IconDelegate::paint( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	//_PaintGreen(painter, option, index);
	//_PaintRed(painter, option, index);
	//_PaintGray(painter, option, index);

	//if(index.column() == 2)
	//int nColumnIndex_Change = 0;
	//nColumnIndex_Change = CConfigInfo::getInstance().getColumnIndex_Change();

	//if (index.column() != nColumnIndex_Change)
	//{
	//	return;
	//}

	CItemUserInstrumentInfo* pTreeItem = NULL;
	enInstrumentPriceChange nInstrumentPriceChange;
	QString strInstrumentCode;
	if (!index.isValid())
	{
		return;
	}

	pTreeItem = static_cast<CItemUserInstrumentInfo*>(index.internalPointer());
	if (NULL == pTreeItem)
	{
		return;
	}

	//InstrumentPriceChange_Increase = 0,//增加  Qt::green
	//InstrumentPriceChange_Reduction,//减少  Qt::red
	//InstrumentPriceChange_Unchanged,//不变  Qt::blue
	//InstrumentPriceChange_NoQuotes,//没有行情 Qt::Gray

	nInstrumentPriceChange = pTreeItem->getInstrumentPriceChange();
	strInstrumentCode = pTreeItem->getInstrumentCode();
	switch (nInstrumentPriceChange)
	{
	case InstrumentPriceChange_Increase:
		_PaintGreen(painter, option, index);
		break;
	case InstrumentPriceChange_Reduction:
		_PaintRed(painter, option, index);
		break;
	case InstrumentPriceChange_Unchanged:
		_PaintBlue(painter, option, index);
		break;
	case InstrumentPriceChange_NoQuotes:
		_PaintGray(painter, option, index);
		break;
	default:
		_PaintGray(painter, option, index);
		break;
	}
}

QRect IconDelegate::_GetSybolRectForGreenRed(const QStyleOptionViewItem &option) const
{
	QRect rectForSybol; 
// 	rectForSybol.setCoords(option.rect.left() + option.rect.width() / 4,
// 		option.rect.top() + option.rect.height() / 4,
// 		option.rect.right() - option.rect.width() / 4,
// 		option.rect.bottom() - option.rect.height() / 4);

	QPoint pointRectTopLeft;
	QPoint pointRectBotRight;

	pointRectTopLeft.setX(option.rect.left());
	pointRectTopLeft.setY(option.rect.top() + option.rect.height() / 4);

	pointRectBotRight.setX(pointRectTopLeft.x() + option.rect.width() / 4 );
	pointRectBotRight.setY(option.rect.bottom() - option.rect.height() / 4);

	rectForSybol = QRect(pointRectTopLeft, pointRectBotRight);

	return rectForSybol;
}


QPolygon IconDelegate::_GetSybolQPolygonForGreen(const QRect& rectForSybol) const
{
	//set QPolygon 7 Points
	QPoint pointRectTopLeft = rectForSybol.topLeft();
	QPoint pointRectTopRight = rectForSybol.topRight();
	int nPointRectWith = rectForSybol.width();
	int nPointRectHeight = rectForSybol.height();
	int nPointRectWithHalf = nPointRectWith / 2;
	int nPointRectHeightHalf = nPointRectHeight / 2;
	int nPointRectHeightHalfHalf = nPointRectHeightHalf / 2;
	int nWith = DEF_VALUE_INT_SYBOL_Triangle_Tail_Length;
	int nWithWith = DEF_VALUE_INT_SYBOL_Triangle_Bot_Half_With;
	QPoint pointTopMid;
	QPoint pointMidMid;
	QPoint pointBotMid;
	QPoint pointPolygonTopMid;
	QPoint pointPolygonMidRightRight;
	QPoint pointPolygonMidRight;
	QPoint pointPolygonBotRight;
	QPoint pointPolygonBotLeft;
	QPoint pointPolygonMidLeft;
	QPoint pointPolygonMidLeftLeft;

	pointTopMid.setX(pointRectTopLeft.x() + nPointRectWithHalf);
	pointTopMid.setY(pointRectTopLeft.y());

	pointMidMid.setX(pointTopMid.x());
	pointMidMid.setY(pointRectTopLeft.y() +  nPointRectHeightHalf + nPointRectHeightHalfHalf);

	pointBotMid.setX(pointTopMid.x());
	pointBotMid.setY(pointRectTopLeft.y() + nPointRectHeight);
	//
	pointPolygonTopMid = pointTopMid;
	pointPolygonMidRightRight.setX(pointMidMid.x() + nWithWith);
	pointPolygonMidRightRight.setY(pointMidMid.y());	
	pointPolygonMidRight.setX(pointMidMid.x() + nWith);
	pointPolygonMidRight.setY(pointMidMid.y());
	pointPolygonBotRight.setX(pointPolygonMidRight.x());
	pointPolygonBotRight.setY(pointBotMid.y());
	pointPolygonBotLeft.setX(pointBotMid.x() - nWith);
	pointPolygonBotLeft.setY(pointBotMid.y());
	pointPolygonMidLeft.setX(pointPolygonBotLeft.x());
	pointPolygonMidLeft.setY(pointPolygonMidRight.y());
	pointPolygonMidLeftLeft.setX(pointMidMid.x() - nWithWith);
	pointPolygonMidLeftLeft.setY(pointPolygonMidRightRight.y());

	//
	QPolygon sybolQPolygon;
	sybolQPolygon<<pointPolygonTopMid
		<<pointPolygonMidRightRight
		<<pointPolygonMidRight
		<<pointPolygonBotRight
		<<pointPolygonBotLeft
		<<pointPolygonMidLeft
		<<pointPolygonMidLeftLeft;

	return sybolQPolygon;
}

void IconDelegate::_PaintGreen( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	QColor itemColor(Qt::green);//Qt::GlobalColor
	QPen penLine;

	//setSybol rect
	QRect rectForSybol = _GetSybolRectForGreenRed(option); 
	QPolygon sybolQPolygon = _GetSybolQPolygonForGreen(rectForSybol);

	penLine.setColor(itemColor);
	painter->setPen(penLine);
	painter->setBrush(itemColor);//设置画刷颜色
	painter->drawPolygon(sybolQPolygon);

}





QPolygon IconDelegate::_GetSybolQPolygonForRed(const QRect& rectForSybol) const
{
	//set QPolygon 7 Points
	QPoint pointRectTopLeft = rectForSybol.topLeft();
	QPoint pointRectTopRight = rectForSybol.topRight();
	int nPointRectWith = rectForSybol.width();
	int nPointRectHeight = rectForSybol.height();
	int nPointRectWithHalf = nPointRectWith / 2;
	int nPointRectHeightHalf = nPointRectHeight / 2;
	int nPointRectHeightHalfHalf = nPointRectHeightHalf / 2;

	int nWith = DEF_VALUE_INT_SYBOL_Triangle_Tail_Length;
	int nWithWith = DEF_VALUE_INT_SYBOL_Triangle_Bot_Half_With;
	QPoint pointTopMid;
	QPoint pointMidMid;
	QPoint pointBotMid;
	QPoint pointPolygonTopMid;
	QPoint pointPolygonMidRightRight;
	QPoint pointPolygonMidRight;
	QPoint pointPolygonBotRight;
	QPoint pointPolygonBotLeft;
	QPoint pointPolygonMidLeft;
	QPoint pointPolygonMidLeftLeft;

	pointTopMid.setX(pointRectTopLeft.x() + nPointRectWithHalf);
	pointTopMid.setY(pointRectTopLeft.y());

	pointMidMid.setX(pointTopMid.x());
	pointMidMid.setY(pointRectTopLeft.y() +  nPointRectHeightHalf - nPointRectHeightHalfHalf);

	pointBotMid.setX(pointTopMid.x());
	pointBotMid.setY(pointRectTopLeft.y() + nPointRectHeight);
	//
	pointPolygonTopMid = pointBotMid;
	pointPolygonMidRightRight.setX(pointMidMid.x() + nWithWith);
	pointPolygonMidRightRight.setY(pointMidMid.y());	
	pointPolygonMidRight.setX(pointMidMid.x() + nWith);
	pointPolygonMidRight.setY(pointMidMid.y());
	pointPolygonBotRight.setX(pointPolygonMidRight.x());
	pointPolygonBotRight.setY(pointTopMid.y());
	pointPolygonBotLeft.setX(pointTopMid.x() - nWith);
	pointPolygonBotLeft.setY(pointTopMid.y());
	pointPolygonMidLeft.setX(pointPolygonBotLeft.x());
	pointPolygonMidLeft.setY(pointPolygonMidRight.y());
	pointPolygonMidLeftLeft.setX(pointMidMid.x() - nWithWith);
	pointPolygonMidLeftLeft.setY(pointPolygonMidRightRight.y());

	//
	QPolygon sybolQPolygon;
	sybolQPolygon<<pointPolygonTopMid
		<<pointPolygonMidRightRight
		<<pointPolygonMidRight
		<<pointPolygonBotRight
		<<pointPolygonBotLeft
		<<pointPolygonMidLeft
		<<pointPolygonMidLeftLeft;

	return sybolQPolygon;
}

void IconDelegate::_PaintRed( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	QColor itemColor(Qt::red);//Qt::GlobalColor
	QPen penLine;

	//setSybol rect
	QRect rectForSybol = _GetSybolRectForGreenRed(option); 
	QPolygon sybolQPolygon = _GetSybolQPolygonForRed(rectForSybol);

	penLine.setColor(itemColor);
	painter->setPen(penLine);
	painter->setBrush(itemColor);//设置画刷颜色
	painter->drawPolygon(sybolQPolygon);

}


QRect IconDelegate::_GetSybolRectForGray(const QStyleOptionViewItem &option) const
{
	QRect rectForSybol;
	QPoint pointRectTopLeft = option.rect.topLeft();
	int nPointRectHeightHalf = option.rect.height() / 2;
	int nWith = DEF_VALUE_INT_SYBOL_Circle_Radius;
	
	QPoint pointRectMid;
	
	pointRectMid.setX(pointRectTopLeft.x() + option.rect.width() / 8);
	pointRectMid.setY(pointRectTopLeft.y() + nPointRectHeightHalf);

	rectForSybol.setCoords(pointRectMid.x() - nWith,
		pointRectMid.y() - nWith,
		pointRectMid.x() + nWith,
		pointRectMid.y() + nWith);

	return rectForSybol;
}

void IconDelegate::_PaintGray( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	QColor itemColor(Qt::gray);//Qt::GlobalColor
	QPen penLine;

	//setSybol rect
	QRect rectForSybol = _GetSybolRectForGray(option); 

	penLine.setColor(itemColor);
	painter->setPen(penLine);
	painter->setBrush(itemColor);//设置画刷颜色
	painter->drawEllipse(rectForSybol);

}

void IconDelegate::_PaintBlue( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const
{
	QColor itemColor(Qt::blue);//Qt::GlobalColor
	QPen penLine;

	//setSybol rect
	QRect rectForSybol = _GetSybolRectForGray(option); 

	penLine.setColor(itemColor);
	painter->setPen(penLine);
	painter->setBrush(itemColor);//设置画刷颜色
	painter->drawEllipse(rectForSybol);

}

//QT_END_NAMESPACE

