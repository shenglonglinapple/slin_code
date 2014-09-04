#ifndef __CLASS_ICON_DELEGATE_HH__
#define __CLASS_ICON_DELEGATE_HH__



#include <QtGui/QItemDelegate>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

/*

enum enInstrumentPriceChange
{
InstrumentPriceChange_Increase = 0,//增加  Qt::green
InstrumentPriceChange_Reduction,//减少  Qt::red
InstrumentPriceChange_Unchanged,//不变  Qt::blue
InstrumentPriceChange_NoQuotes,//没有行情 Qt::Gray
};

*/


//头像列，只是在单元格中央放一张小图而已  
class IconDelegate : public QItemDelegate  
{  
	Q_OBJECT  

public:
	enum enInstrumentPriceChange
	{
		InstrumentPriceChange_Increase = 0,//增加  Qt::green
		InstrumentPriceChange_Reduction,//减少  Qt::red
		InstrumentPriceChange_Unchanged,//不变  Qt::blue
		InstrumentPriceChange_NoQuotes,//没有行情 Qt::Gray
	};


public:  
	IconDelegate(QObject *parent = 0);  
	void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const; 
private:  
	void _PaintGreen( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	void _PaintRed( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;

	QRect _GetSybolRectForGreenRed(const QStyleOptionViewItem &option) const;
	QRect _GetSybolRectForGray(const QStyleOptionViewItem &option) const;
	QPolygon _GetSybolQPolygonForGreen(const QRect& rectForSybol) const;
	QPolygon _GetSybolQPolygonForRed(const QRect& rectForSybol) const;
	void _PaintGray( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
	void _PaintBlue( QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex & index ) const;
};


//QT_END_NAMESPACE

#endif//__CLASS_ICON_DELEGATE_HH__




