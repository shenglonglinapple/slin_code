#include "SceneInsertRectParam.h"
#include "DragRectParam.h"

CSceneInsertRectParam::CSceneInsertRectParam()
{
	m_nClassType = ClassType_CSceneInsertRectParam;
}

CSceneInsertRectParam::~CSceneInsertRectParam()
{

}

void CSceneInsertRectParam::setValue( CDragRectParam* pDragRectParam )
{
	if (NULL == pDragRectParam)
	{
		return;
	}

	this->m_nDragItemType = pDragRectParam->m_nDragItemType;
	this->m_RectLineColor = pDragRectParam->m_RectLineColor;
	this->m_pointHot = pDragRectParam->m_pointHot;
	this->m_TextFontTop = pDragRectParam->m_TextFontTop;
	this->m_TextColorTop = pDragRectParam->m_TextColorTop;
	this->m_TextFontBottom = pDragRectParam->m_TextFontBottom;
	this->m_TextColorBottom = pDragRectParam->m_TextColorBottom;
}

void CSceneInsertRectParam::setValuePointMousePos( const QPointF& pointMousePos )
{
	m_pointMousePos = pointMousePos;
}

void CSceneInsertRectParam::buildParam()
{
	m_pointItemLeftTop.setX(m_pointMousePos.x() - this->m_pointHot.x());
	m_pointItemLeftTop.setY(m_pointMousePos.y() - this->m_pointHot.y());
}

