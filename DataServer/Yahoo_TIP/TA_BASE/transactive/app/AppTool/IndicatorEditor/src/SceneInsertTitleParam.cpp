#include "SceneInsertTitleParam.h"
#include "DragTextParam.h"

CSceneInsertTitleParam::CSceneInsertTitleParam()
{
	m_nClassType = ClassType_CSceneInsertTitleParam;
}

CSceneInsertTitleParam::~CSceneInsertTitleParam()
{

}


void CSceneInsertTitleParam::setMousePos( const QPointF& pointMousePos )
{
	m_pointMousePos = pointMousePos;
}



void CSceneInsertTitleParam::setValue( CDragTextParam* pDragTextParam )
{
	if (NULL == pDragTextParam)
	{
		return;
	}
	this->m_nDragItemType = pDragTextParam->m_nDragItemType;
	this->m_TextColor = pDragTextParam->m_TextColor;
	this->m_pointHot = pDragTextParam->m_pointHot;
	this->m_TextFont = pDragTextParam->m_TextFont;	
}

void CSceneInsertTitleParam::buildParam()
{
	m_pointItemLeftTop.setX(m_pointMousePos.x() - this->m_pointHot.x());
	m_pointItemLeftTop.setY(m_pointMousePos.y() - this->m_pointHot.y());
}