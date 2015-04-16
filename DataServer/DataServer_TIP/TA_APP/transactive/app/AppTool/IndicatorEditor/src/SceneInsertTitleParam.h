#ifndef  __DEF__CLASS__SCENE_INSERT_TITLE_PARAM_HH__
#define  __DEF__CLASS__SCENE_INSERT_TITLE_PARAM_HH__


#include "CommonDef.h"
#include "CommonData.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CDragTextParam;

class CSceneInsertTitleParam
{
public:
    CSceneInsertTitleParam();
	virtual ~CSceneInsertTitleParam();
public:
	void setMousePos(const QPointF& pointMousePos);
	void setValue(CDragTextParam* pDragTextParam);
	void buildParam();
public:
	QPointF m_pointMousePos;
	QColor m_TextColor;
	EProjectClassType m_nDragItemType;
	QPoint m_pointHot;
	QFont m_TextFont;
public:
	QPointF m_pointItemLeftTop;
private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__SCENE_INSERT_TITLE_PARAM_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










