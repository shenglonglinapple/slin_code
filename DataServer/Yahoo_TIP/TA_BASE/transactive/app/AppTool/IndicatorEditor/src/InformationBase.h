#ifndef  __DEF__CLASS__INFORMATION_BASE_HH__
#define  __DEF__CLASS__INFORMATION_BASE_HH__

#include "CommonDef.h"
#include "InformationRectItem.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CInformationBase : public CInformationRectItem
{
public:
    CInformationBase(const QRectF& rect, QGraphicsItem* parent = 0, QGraphicsScene* scene = 0);
	virtual ~CInformationBase();
public:
	void adjustPos(QPointF pointItemBegin);
	EProjectClassType getClassType() const;
	int type() const;
public:
	void adjustAllPos();
public:
	void setTopSourceEdge(CInformationRectItemEdge* pTopSourceEdge);
	void setBottomSourceEdge(CInformationRectItemEdge* pBottomSourceEdge);
	void setDestEdge(CInformationRectItemEdge* pBottomSourceEdge);

	void setTopSourceNode(CInformationBase* pItem);
	void setBottomSourceNode(CInformationBase* pItem);
	void setDestNode(CInformationBase* pItem);
	
	void setDestEdgeType(CInformationRectItemEdge::EEdgeType nEdgeType);

	void setDestNode(CInformationBase* pItem, CInformationRectItemEdge::EEdgeType nEdgeType);


	CInformationBase* getTopSourceNode() const;
	CInformationBase* getBottomSourceNode() const;
	CInformationBase* getDestNode() const;
	CInformationRectItemEdge::EEdgeType getDestEdgeType() const;

	CInformationRectItemEdge::EEdgeType checkEdgeTypeByPos( QPointF pointPos );
public:
	void removeDestEdge();

	
private:
	void _ResetAllEdge();
private:
	CInformationRectItemEdge* m_pTopSourceEdgeRef;
	CInformationRectItemEdge* m_pBottomSourceEdgeRef;
	CInformationRectItemEdge* m_pDestEdge;
	CInformationBase* m_pTopSourceNodeRef;
	CInformationBase* m_pBottomSourceNodeRef;
	CInformationBase* m_pDestNode;
	CInformationRectItemEdge::EEdgeType m_nDestEdgeType;
private:
	EProjectClassType m_nClassType;
	QGraphicsScene* m_pSceneRef;

};
//QT_END_NAMESPACE

#endif // __DEF__CLASS__EQUALITY_OPERATOR_HH__














