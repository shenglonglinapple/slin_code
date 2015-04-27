#ifndef  __DEF__CLASS__SCENE_INSERT_LINE_PARAM_HH__
#define  __DEF__CLASS__SCENE_INSERT_LINE_PARAM_HH__


#include "CommonDef.h"
#include "CommonData.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CSceneInsertLineParam
{
public:
    CSceneInsertLineParam();
	virtual ~CSceneInsertLineParam();
public:
	void setMousePos(const QPointF& pointMousePos);
	void setLineColor(const QColor& lineColorValue);
	void setLineWidth(const int& nLineWidthValue);
	void buildParam();
public:
	QPointF m_pointMousePos;
	QColor m_LineColor;	
	int m_nLineWidth;
	QPen m_penForLine;
public:
	QPointF m_pointStart;
	QPointF m_pointEnd;
	QLineF m_lineValue;

private:
	EProjectClassType m_nClassType;

};

#endif // __DEF__CLASS__SCENE_INSERT_LINE_PARAM_HH__



////QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE










