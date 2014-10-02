#ifndef QCP_ITEM_TRACER_CROSSHAIR_H
#define QCP_ITEM_TRACER_CROSSHAIR_H

#include "../global.h"
#include "../item.h"
#include <QtCore/QList>
#include <QtCore/QMap>

class QCPPainter;
class QCustomPlot;
class QCPGraph;
class QCPStatisticalBox;

//////////////////////////////////////////////////////////////////////////
class QCP_LIB_DECL QCPStatisticalBoxTracerCrossData
{
public:
	QCPStatisticalBoxTracerCrossData();
	~QCPStatisticalBoxTracerCrossData();
public:
	void clear();
	void setKey(double fKey);
	void setValue(QCPStatisticalBox* pPlottableRef);
	bool isSetData();
	void setDrawInfo(QRect clipRect);
public:
	bool m_bSetData;
public:
	double m_fKey;
	double m_fMinimum;
	double m_fLowerQuartile;
	double m_fUpperQuartile;
	double m_fMaximum;
	double m_fWidth;
	QPen m_fWhiskerBarPen;
	int m_nBoxType;
public:
	QPointF m_pointf;
	QString m_strInfo;
};
//////////////////////////////////////////////////////////////////////////
class QCP_LIB_DECL QCPGraphTracerCrossData
{
public:
	QCPGraphTracerCrossData();
	~QCPGraphTracerCrossData();
public:
	void clear();
	void setKey(double fGraphKey);
	void setValue(QCPGraph* pPlottableRef);
	bool isSetData();
	void setDrawInfo(QRect clipRect);
public:
	bool m_bSetData;
public:
	double m_nGraphKey;
	double m_nGraphValue;
	QPen m_Pen;
public:
	QPointF m_pointf;
	QString m_strInfo;
	
};
//////////////////////////////////////////////////////////////////////////

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

public:
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

	// reimplemented virtual methods:
	virtual double selectTest(const QPointF &pos, bool onlySelectable, QVariant *details=0) const;

public:
	void setCenterPos(const QPointF& posf);
	void setTracerAxisRect(QCPAxisRect* pAxisRect);
	void setShowBottom(QCPAxis::LabelType nShowType, bool bShow, const QString& strFormat);
	void setShowLeft(QCPAxis::LabelType nShowType, bool bShow, const QString& strFormat);
	QList<QCPStatisticalBoxTracerCrossData*>* getCrossBarData();
	QList<QCPGraphTracerCrossData*>* getCrossGrapData();
public:
	QCPItemPosition* const m_pItemPosition;

protected:
	// reimplemented virtual methods:
	virtual void draw(QCPPainter *painter);

	// non-virtual methods:
	QPen mainPen() const;
	QBrush mainBrush() const;
private:
	void _UpdateAllInfo();
	void _UpdateLinesInfo();
	void _UpdateTextInfo();
	void _UpdateVerticalCrossValue();
	void _GetValue_QCPGraph(QCPGraph* pPlottableRef);
	void _GetValue_QCPStatisticalBox(QCPStatisticalBox* pPlottableRef);
	void _ClearCrossData();
	void _ClearData_ListCrossBarData();
	void _ClearData_ListCrossGrapData();
protected:
	// property members:
	QPen mPen;
	QPen mSelectedPen;
	QBrush mBrush;
	QBrush mSelectedBrush;
	TracerStyle mStyle;
protected:
	//QPointF m_pointf_center;
protected:
	//Qt::Horizontal Ë®Æ½
	QLineF m_linef_Horizontal;
	bool   m_bShow_Linef_Horizontal;

	bool   m_bShow_Horizontal_left;
	QCPAxis::LabelType m_nShowType_Horizontal_left;
	QString   m_strFormat_Horizontal_left;
	QString m_str_Horizontal_left;
	QPointF m_pointf_Horizontal_left;
	QString m_str_Horizontal_right;
	QPointF m_pointf_Horizontal_right;


	//Qt::Vertical ´¹Ö±
	QLineF m_linef_Vertical;
	bool   m_bShow_Linef_Vertical;

	bool   m_bShow_Vertical_bottom;
	QCPAxis::LabelType m_nShowType_Vertical_bottom;
	QString   m_strFormat_Vertical_bottom;
	QString m_str_Vertical_bottom;
	QPointF m_pointf_Vertical_bottom;
	QString m_str_Vertical_top;
	QPointF m_pointf_Vertical_top;

private:
	QCPGraphTracerCrossData* m_pQCPGraphTracerCrossData;
	QCPStatisticalBoxTracerCrossData* m_pQCPStatisticalBoxTracerCrossData;
	QList<QCPStatisticalBoxTracerCrossData*>* m_pListCrossBarData;
	QList<QCPGraphTracerCrossData*>* m_pListCrossGrapData;

};

#endif // QCP_ITEM_TRACER_CROSSHAIR_H
