#ifndef QCP_ITEM_TRACER_CROSSHAIR_H
#define QCP_ITEM_TRACER_CROSSHAIR_H

#include "../global.h"
#include "../item.h"

class QCPPainter;
class QCustomPlot;
class QCPGraph;

class QCP_LIB_DECL QCPItemTracerCrossHair : public QCPAbstractItem
{
	Q_OBJECT
		/// \cond INCLUDE_QPROPERTIES
		Q_PROPERTY(QPen pen READ pen WRITE setPen)
		Q_PROPERTY(QPen selectedPen READ selectedPen WRITE setSelectedPen)
		Q_PROPERTY(QBrush brush READ brush WRITE setBrush)
		Q_PROPERTY(QBrush selectedBrush READ selectedBrush WRITE setSelectedBrush)
		Q_PROPERTY(TracerStyle style READ style WRITE setStyle)
		/// \endcond
public:
	/*!
	The different visual appearances a tracer item can have. Some styles size may be controlled with \ref setSize.

	\see setStyle
	*/
	enum TracerStyle { tsNone        ///< The tracer is not visible
		,tsCrosshair  ///< A plus shaped crosshair which spans the complete axis rect
	};
	Q_ENUMS(TracerStyle)

		QCPItemTracerCrossHair(QCustomPlot *parentPlot);
	virtual ~QCPItemTracerCrossHair();
public:
	// getters:
	QPen pen() const { return mPen; }
	QPen selectedPen() const { return mSelectedPen; }
	QBrush brush() const { return mBrush; }
	QBrush selectedBrush() const { return mSelectedBrush; }
	TracerStyle style() const { return mStyle; }

	// setters;
	void setPen(const QPen &pen);
	void setSelectedPen(const QPen &pen);
	void setBrush(const QBrush &brush);
	void setSelectedBrush(const QBrush &brush);
	void setStyle(TracerStyle style);
	void setCenterPos(const QPointF& posf);

	// reimplemented virtual methods:
	virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const;


protected:
	// reimplemented virtual methods:
	virtual void draw(QCPPainter *painter);

	// non-virtual methods:
	QPen mainPen() const;
	QBrush mainBrush() const;
private:
	void _UpdateItemInfo();
protected:
	// property members:
	QPen mPen;
	QPen mSelectedPen;
	QBrush mBrush;
	QBrush mSelectedBrush;
	TracerStyle mStyle;
protected:
	QPointF m_pointf_center;
protected:
	//Qt::Horizontal
	bool   m_bShowHorizontalLine;
	QLineF m_linef_Horizontal;
	QString m_str_Horizontal_bottom;
	QPointF m_pointf_Horizontal_bottom;
	QString m_str_Horizontal_top;
	QPointF m_pointf_Horizontal_top;
	//Qt::Vertical
	bool   m_bShowVerticalLine;
	QLineF m_linef_Vertical;
	QString m_str_Vertical_left;
	QPointF m_pointf_Vertical_left;
	QString m_str_Vertical_right;
	QPointF m_pointf_Vertical_right;


	
};

#endif // QCP_ITEM_TRACER_CROSSHAIR_H
