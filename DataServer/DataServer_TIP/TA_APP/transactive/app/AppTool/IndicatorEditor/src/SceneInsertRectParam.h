#ifndef  __DEF__CLASS__SCENE_INSERT_RECT_PARAM_HH__
#define  __DEF__CLASS__SCENE_INSERT_RECT_PARAM_HH__


#include "CommonDef.h"
#include "CommonData.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CDragRectParam;

class CSceneInsertRectParam
{
public:
    CSceneInsertRectParam();
	virtual ~CSceneInsertRectParam();
public:
	void setValuePointMousePos(const QPointF& pointMousePos);
	void setValue(CDragRectParam* pDragRectParam);
	void buildParam();
public:
	EProjectClassType m_nDragItemType;
	QColor m_RectLineColor;
	QPoint m_pointHot;
	QFont m_TextFontTop;
	QColor m_TextColorTop;
	QFont m_TextFontBottom;
	QColor m_TextColorBottom;
public:
	QPointF m_pointMousePos;
	QPointF m_pointItemLeftTop;

private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__DRAG_PARAM_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










