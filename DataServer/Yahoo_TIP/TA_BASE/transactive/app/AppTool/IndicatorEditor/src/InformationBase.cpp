#include "InformationBase.h"
#include "CommonData.h"
#include "InformationRectItem.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


CInformationBase::CInformationBase(const QRectF& rect, QGraphicsItem* parent, QGraphicsScene* scene)
:CInformationRectItem(rect, parent, scene)
{
	m_nClassType = ClassType_CInformationBase;
	m_pSceneRef = scene;

	m_pTopSourceEdgeRef = NULL;
	m_pBottomSourceEdgeRef = NULL;
	m_pDestEdge = NULL;
	m_pTopSourceNodeRef = NULL;
	m_pBottomSourceNodeRef = NULL;
	m_pDestNode = NULL;
	m_nDestEdgeType = CInformationRectItemEdge::EEdgeType_Begin;


}

CInformationBase::~CInformationBase()
{

	if (NULL != m_pDestNode)
	{
		if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top == m_nDestEdgeType)
		{
			m_pDestNode->setTopSourceEdge(NULL);
			m_pDestNode->setTopSourceNode(NULL);
		}
		else if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom == m_nDestEdgeType)
		{
			m_pDestNode->setBottomSourceEdge(NULL);
			m_pDestNode->setBottomSourceNode(NULL);
		}
	}
	setDestNode(NULL, CInformationRectItemEdge::EEdgeType_Begin);

	if (NULL != m_pTopSourceNodeRef)
	{
		m_pTopSourceNodeRef->setDestNode(NULL, CInformationRectItemEdge::EEdgeType_Begin);
		m_pTopSourceNodeRef = NULL;
		m_pTopSourceEdgeRef = NULL;
	}


	if (NULL != m_pBottomSourceNodeRef)
	{
		m_pBottomSourceNodeRef->setDestNode(NULL, CInformationRectItemEdge::EEdgeType_Begin);
		m_pBottomSourceNodeRef = NULL;
		m_pBottomSourceNodeRef = NULL;
	}


}



void CInformationBase::adjustPos(QPointF pointItemBegin)
{
	QPointF pointCurrentItemNode;
	QPointF pointDestItemNode;
	CInformationRectItemEdge::EEdgeType nEdgeType;
	CInformationBase* pItemDestNode = NULL;


	pointCurrentItemNode = pointItemBegin;
	this->setItemPos(pointCurrentItemNode);


	pItemDestNode = this->getDestNode();
	if (NULL == pItemDestNode)
	{
		return;
	}

	nEdgeType = this->getDestEdgeType();
	if (nEdgeType == CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top)
	{
		pointDestItemNode.setX(pointCurrentItemNode.x() + this->getItemWidth() + DEF_VALUE_InfomationRectItemEdge_Width);
		pointDestItemNode.setY(pointCurrentItemNode.y() + DEF_VALUE_InfomationRectItem_Height);

		pItemDestNode->adjustPos(pointDestItemNode);
	}
	else if (nEdgeType == CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom)
	{
		//not need adjuestPos
	}
	else
	{
		//not need adjuestPos
	}

	_ResetAllEdge();

}

EProjectClassType CInformationBase::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CInformationBase::type() const
{
	return m_nClassType;
}






void CInformationBase::setTopSourceEdge(CInformationRectItemEdge* pTopSourceEdge)
{
	m_pTopSourceEdgeRef = pTopSourceEdge;
}
void CInformationBase::setBottomSourceEdge(CInformationRectItemEdge* pBottomSourceEdge)
{
	m_pBottomSourceEdgeRef = pBottomSourceEdge;
}


void CInformationBase::setDestEdge( CInformationRectItemEdge* pBottomSourceEdge )
{
	m_pDestEdge = pBottomSourceEdge;
}

void CInformationBase::setTopSourceNode(CInformationBase* pItem) 
{
	m_pTopSourceNodeRef = pItem;
}
void CInformationBase::setBottomSourceNode(CInformationBase* pItem)
{
	m_pBottomSourceNodeRef = pItem;
}

void CInformationBase::setDestNode(CInformationBase* pItem)
{
	m_pDestNode = pItem;
}

void CInformationBase::setDestEdgeType( CInformationRectItemEdge::EEdgeType nEdgeType )
{
	m_nDestEdgeType = nEdgeType;
}

CInformationBase* CInformationBase::getTopSourceNode() const
{
	return m_pTopSourceNodeRef;
}
CInformationBase* CInformationBase::getBottomSourceNode() const
{
	return m_pBottomSourceNodeRef;
}
CInformationBase* CInformationBase::getDestNode() const
{
	return m_pDestNode;
}


CInformationRectItemEdge::EEdgeType CInformationBase::getDestEdgeType() const
{
	return m_nDestEdgeType;
}



void CInformationBase::setDestNode(CInformationBase* pItem, CInformationRectItemEdge::EEdgeType nEdgeType)
{
	CInformationRectItemEdge* pEdge = NULL;

	setDestNode(pItem);
	setDestEdgeType(nEdgeType);

	if (NULL != m_pDestEdge)
	{
		delete m_pDestEdge;
		m_pDestEdge = NULL;
	}

	if (NULL == pItem)
	{
		return;
	}

	switch (m_nDestEdgeType)
	{
	case CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top:
		{
			m_pDestNode->setTopSourceNode(this);
			m_pDestEdge = new CInformationRectItemEdge(this, m_pDestNode, 
				CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top, this, m_pSceneRef);
			m_pDestNode->setTopSourceEdge(m_pDestEdge);
			//m_pDestNode->setParentItem(this);
			m_pDestEdge->setParentItem(this);
			break;
		}
	case CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom:
		{
			m_pDestNode->setBottomSourceNode(this);
			m_pDestEdge = new CInformationRectItemEdge(this, m_pDestNode, 
				CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom, this, m_pSceneRef);
			m_pDestNode->setBottomSourceEdge(m_pDestEdge);
			//m_pDestNode->setParentItem(this);
			m_pDestEdge->setParentItem(this);
			break;
		}
	default:
		break;
	}

}



void CInformationBase::_ResetAllEdge()
{
	if (NULL != m_pTopSourceEdgeRef)
	{
		m_pTopSourceEdgeRef->adjustEdgeLocation();
	}
	if (NULL != m_pBottomSourceEdgeRef)
	{
		m_pBottomSourceEdgeRef->adjustEdgeLocation();
	}
	if (NULL != m_pDestEdge)
	{
		m_pDestEdge->adjustEdgeLocation();
	}


}

void CInformationBase::adjustAllPos()
{
	_ResetAllEdge();
}

CInformationRectItemEdge::EEdgeType CInformationBase::checkEdgeTypeByPos( QPointF pointPos )
{
	CInformationRectItemEdge::EEdgeType nEdgeType = CInformationRectItemEdge::EEdgeType_Begin;

	nEdgeType = this->checkEdgeType(pointPos);

	if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top == nEdgeType
		&& NULL == m_pTopSourceNodeRef)
	{
		nEdgeType = CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top;
	}
	else if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom == nEdgeType
		&& NULL == m_pBottomSourceNodeRef)
	{
		nEdgeType = CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom;
	}
	else
	{
		nEdgeType = CInformationRectItemEdge::EEdgeType_Begin;
	}

	return nEdgeType;
}

void CInformationBase::removeDestEdge()
{
	if (NULL != m_pDestNode) 
	{
		CInformationBase* pSourceNodeTmp = this;
		CInformationBase* pDestNodeTmp = m_pDestNode;

		CInformationRectItemEdge::EEdgeType  nEdgeType = pSourceNodeTmp->getDestEdgeType();

		if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top == nEdgeType)
		{
			pDestNodeTmp->setTopSourceEdge(NULL);
			pDestNodeTmp->setTopSourceNode(NULL);
		}
		else if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom == nEdgeType)
		{
			pDestNodeTmp->setBottomSourceEdge(NULL);
			pDestNodeTmp->setBottomSourceNode(NULL);
		}

		pSourceNodeTmp->setDestNode(NULL, CInformationRectItemEdge::EEdgeType_Begin);

	}
}


//QT_END_NAMESPACE
