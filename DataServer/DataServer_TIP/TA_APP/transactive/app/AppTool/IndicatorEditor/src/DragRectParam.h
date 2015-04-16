#ifndef  __DEF__CLASS__DRAG_RECT_PARAM_HH__
#define  __DEF__CLASS__DRAG_RECT_PARAM_HH__


#include "CommonDef.h"
#include "CommonData.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CDragRectParam
{
public:
    CDragRectParam();
	virtual ~CDragRectParam();
public:
	void setParamValue(EProjectClassType nRectItemType, const QColor& RectLineColor, const QPoint& pointHot, const QFont& TextFontTop, const QColor& TextColorTop, const QFont& TextFontBottom, const QColor& TextColorBottom );
	void setDataToContainer(QMimeData* mime);
	void getDataFromContainer(const QMimeData* mime);
	void getParamValue(EProjectClassType& nRectItemType, QColor& RectLineColor, QPoint& pointHot, QFont& TextFontTop, QColor& TextColorTop, QFont& TextFontBottom, QColor& TextColorBottom );
public:
	QString m_strDataType;
	QColor m_RectLineColor;
	QString m_strParamClassType;
	QString m_strParamRectHotXValue;
	QString m_strParamRectHotYValue;

	QString m_strParamTextTopFont;
	QString m_strParamTextTopFontPointSize;
	QString m_strParamTextTopFontWeight;
	QString m_strParamTextTopFontItalic;
	QString m_strParamTextTopFontUnderline;
	QString m_strParamTextTopColorR;
	QString m_strParamTextTopColorG;
	QString m_strParamTextTopColorB;

	QString m_strParamTextBottomFont;
	QString m_strParamTextBottomFontPointSize;
	QString m_strParamTextBottomFontWeight;
	QString m_strParamTextBottomFontItalic;
	QString m_strParamTextBottomFontUnderline;
	QString m_strParamTextBottomColorR;
	QString m_strParamTextBottomColorG;
	QString m_strParamTextBottomColorB;
public:
	EProjectClassType m_nDataType;
	EProjectClassType m_nDragItemType;
	QPoint m_pointHot;
	QFont m_TextFontTop;
	int m_TextFontTopPointSize;
	int m_TextFontTopWeight;
	bool m_TextFontTopItalic;
	bool m_TextFontTopUnderline;
	QColor m_TextColorTop;

	QFont m_TextFontBottom;
	int m_TextFontBottomPointSize;
	int m_TextFontBottomWeight;
	bool m_TextFontBottomItalic;
	bool m_TextFontBottomUnderline;
	QColor m_TextColorBottom;

private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__DRAG_RECT_PARAM_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










