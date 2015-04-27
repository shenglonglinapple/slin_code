#ifndef  __DEF__CLASS__DRAG_TEXT_PARAM_HH__
#define  __DEF__CLASS__DRAG_TEXT_PARAM_HH__


#include "CommonDef.h"
#include "CommonData.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CDragTextParam
{
public:
    CDragTextParam();
	virtual ~CDragTextParam();
public:
	void setParamValue(EProjectClassType nItemType, const QColor& TextColor, const QPoint& pointHot, const QFont& TextFont );
	void setDataToContainer(QMimeData* mime);
	void getDataFromContainer(const QMimeData* mime);
	void getParamValue(EProjectClassType& nItemType, QColor& TextColor, QPoint& pointHot, QFont& TextFont );
public:
	QString m_strDataType;
	QColor m_TextColor;
	QString m_strParamClassType;
	QString m_strParamRectHotXValue;
	QString m_strParamRectHotYValue;

	QString m_strParamTextTopFont;
	QString m_strParamTextTopFontPointSize;
	QString m_strParamTextTopFontWeight;
	QString m_strParamTextTopFontItalic;
	QString m_strParamTextTopFontUnderline;

public:
	EProjectClassType m_nDataType;
	EProjectClassType m_nDragItemType;
	QPoint m_pointHot;
	QFont m_TextFont;
	int m_TextFontPointSize;
	int m_TextFontWeight;
	bool m_TextFontItalic;
	bool m_TextFontUnderline;


private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__DRAG_TEXT_PARAM_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










