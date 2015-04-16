#include "SceneInsertLineParam.h"

CSceneInsertLineParam::CSceneInsertLineParam()
{
	m_nClassType = ClassType_CSceneInsertTitleParam;
	m_LineColor = Qt::black;
	m_nLineWidth = 1;
	m_penForLine.setColor(m_LineColor);
	m_penForLine.setWidth(m_nLineWidth);
}

CSceneInsertLineParam::~CSceneInsertLineParam()
{

}


void CSceneInsertLineParam::setMousePos( const QPointF& pointMousePos )
{
	m_pointMousePos = pointMousePos;

	

}

void CSceneInsertLineParam::buildParam()
{
	m_pointStart = m_pointMousePos;
	m_pointEnd = m_pointMousePos;

	m_lineValue.setP1(m_pointStart);
	m_lineValue.setP2(m_pointEnd);

	m_penForLine.setColor(m_LineColor);
	m_penForLine.setWidth(m_nLineWidth);

}

void CSceneInsertLineParam::setLineColor( const QColor& lineColorValue )
{
	m_LineColor = lineColorValue;
}

void CSceneInsertLineParam::setLineWidth( const int& nLineWidthValue )
{
	m_nLineWidth = nLineWidthValue;
}	





