#include "UserDefineInfomation.h"
#include "CommonData.h"
#include "InformationRectItem.h"

#include "InformationBase.h"
#include "InformationTextItem.h"
#include "InfomationItemInEditor.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE





static const qreal DEF_VALUE_InfomationTitle_X = 100;
static const qreal DEF_VALUE_InfomationTitle_Y = 100;
static const qreal DEF_VALUE_InfomationTitle_Width = 800;
static const qreal DEF_VALUE_InfomationTitle_Height = 200;


CUserDefineInfomation::CUserDefineInfomation(QRectF rect, QGraphicsItem* parent, QGraphicsScene* scene)
:QGraphicsItem(parent, scene)
{
	m_nClassType = ClassType_CUserDefineInfomation;
	m_pSceneRef = scene;

	QRectF rectGraphicsRectItem;

	CInformationBase* pNodeLevelOneIndexOne = NULL;
	CInformationBase* pNodeLevelOneIndexTwo = NULL;
	CInformationBase* pNodeLevelTwoIndexOne = NULL;
	CInformationBase* pNodeLevelTwoIndexTwo = NULL;
	CInformationBase* pNodeLevelThreeIndexOne = NULL;

	//
	m_rectBounding = rect;
	//

	m_nTextTitleX = DEF_VALUE_InfomationTitle_X;
	m_nTextTitleY = DEF_VALUE_InfomationTitle_Y;
	m_nTextTitleWidth = DEF_VALUE_InfomationTitle_Width;
	m_strTextTitle = "Title";
	/*
	QFont serifFont("Times", 10, QFont::Bold);
	QFont sansFont("Helvetica [Cronyx]", 12);
	QFont sansFont("Helvetica ", 12);
	*/
	QColor TextColor = Qt::black;
	QString strFamily = "Helvetica";
	int nPointSize = 30;
	int nWeight = QFont::Bold;//QFont::Bold
	bool bItalic = false;
	m_fontTextTitle = QFont(strFamily, nPointSize, nWeight, bItalic);
	m_pTextTitle = new CInformationTextItem(this, m_pSceneRef,  CInformationTextItem::TextItemType_Title);
	m_pTextTitle->setHtml(m_strTextTitle);
	m_pTextTitle->setX(m_nTextTitleX);
	m_pTextTitle->setY(m_nTextTitleY);
	m_pTextTitle->setTextWidth(m_nTextTitleWidth);
	m_pTextTitle->setFont(m_fontTextTitle);

	//
	m_lstNode.clear();
	//
	rectGraphicsRectItem = QRectF(DEF_VALUE_InfomationRectItem_X, DEF_VALUE_InfomationRectItem_Y, 
		DEF_VALUE_InfomationRectItem_Width, DEF_VALUE_InfomationRectItem_Height);

	pNodeLevelOneIndexOne = new CInfomationItemInEditor(rectGraphicsRectItem, this, m_pSceneRef);	
	pNodeLevelOneIndexTwo = new CInfomationItemInEditor(rectGraphicsRectItem, this, m_pSceneRef);	
	pNodeLevelTwoIndexOne = new CInfomationItemInEditor(rectGraphicsRectItem, this, m_pSceneRef);
	pNodeLevelTwoIndexTwo = new CInfomationItemInEditor(rectGraphicsRectItem, this, m_pSceneRef);
	pNodeLevelThreeIndexOne = new CInfomationItemInEditor(rectGraphicsRectItem, this, m_pSceneRef);

	QObject::connect(pNodeLevelOneIndexOne->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pNodeLevelOneIndexOne->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	
	QObject::connect(pNodeLevelOneIndexTwo->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pNodeLevelOneIndexTwo->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	
	QObject::connect(pNodeLevelTwoIndexOne->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pNodeLevelTwoIndexOne->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));

	QObject::connect(pNodeLevelTwoIndexTwo->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pNodeLevelTwoIndexTwo->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));


	QObject::connect(pNodeLevelThreeIndexOne->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pNodeLevelThreeIndexOne->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  m_pSceneRef, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));

	m_lstNode.push_back(pNodeLevelOneIndexOne);
	m_lstNode.push_back(pNodeLevelOneIndexTwo);

	pNodeLevelOneIndexOne->setDestNode(pNodeLevelTwoIndexOne, CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top);
	pNodeLevelOneIndexTwo->setDestNode(pNodeLevelTwoIndexTwo, CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top);

	pNodeLevelTwoIndexOne->setDestNode(pNodeLevelThreeIndexOne, CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top);
	pNodeLevelTwoIndexTwo->setDestNode(pNodeLevelThreeIndexOne, CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom);


	QPointF pointItemBegin;
	pointItemBegin.setX(DEF_VALUE_InfomationRectItem_X);
	pointItemBegin.setY(DEF_VALUE_InfomationRectItem_Y);

	adjustPos(pointItemBegin);
}

CUserDefineInfomation::~CUserDefineInfomation()
{
	m_lstNode.clear();
}

QRectF CUserDefineInfomation::boundingRect() const
{
	return m_rectBounding;
}

void CUserDefineInfomation::paint( QPainter* painter, const QStyleOptionGraphicsItem* option, QWidget* widget )
{

}



void CUserDefineInfomation::adjustPos(QPointF pointItemBegin)
{
	CInformationBase* pCurrentNode = NULL;
	QPointF pointCurrentNode;
	QPointF pointNextNode;
	QList<CInformationBase*>::Iterator iterLst;

	pointCurrentNode = pointItemBegin;

	iterLst = m_lstNode.begin();
	while (iterLst != m_lstNode.end())
	{
		pCurrentNode = (*iterLst);

		pCurrentNode->adjustPos(pointCurrentNode);

		pointNextNode.setX(pointCurrentNode.x());
		pointNextNode.setY(pointCurrentNode.y() + pCurrentNode->getItemHeight() + DEF_VALUE_InfomationRectItemEdge_Height);
		pointCurrentNode = pointNextNode;


		iterLst++;
	}//while

}

EProjectClassType CUserDefineInfomation::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CUserDefineInfomation::type() const
{
	return m_nClassType;
}

//QT_END_NAMESPACE
