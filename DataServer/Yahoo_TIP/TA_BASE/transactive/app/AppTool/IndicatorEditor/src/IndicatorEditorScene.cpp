#include "IndicatorEditorScene.h"
#include "InformationBase.h"
#include "InformationTextItem.h"
#include "InfomationItemInEditor.h"
#include "DragRectParam.h"
#include "DragTextParam.h"
#include "SceneInsertRectParam.h"
#include "SceneInsertLineParam.h"
#include "SceneInsertTitleParam.h"


//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorScene= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorScene = 600;


static const std::string DEFVALUE_String_CIndicatorEditorScene_Title = "Indicator Editor Secne";





CIndicatorEditorScene::CIndicatorEditorScene( QObject *parent /*= 0*/ )
:QGraphicsScene(parent)
{
	m_nClassType = ClassType_CIndicatorEditorScene;
	m_pGraphicsLineItemTmp = NULL;


	QColor TextColor = Qt::black;
	QString strFamily = "Helvetica";
	int nPointSize = 30;
	int nWeight = QFont::Bold;//QFont::Bold
	bool bItalic = false;

	m_fontInScene = QFont(strFamily, nPointSize, nWeight, bItalic);
	m_colorInScene = TextColor;

	m_LineColor = Qt::black;
	//setAcceptDrops(true);
}

CIndicatorEditorScene::~CIndicatorEditorScene()
{

	setupUi(this);
}

void CIndicatorEditorScene::setupUi( QGraphicsScene* pWindow )
{

	setBackgroundBrush(QPixmap(":/images/background2.png"));
	retranslateUi(pWindow);
	update();
}

void CIndicatorEditorScene::retranslateUi( QGraphicsScene *pWindow )
{

}



EProjectClassType CIndicatorEditorScene::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}

void CIndicatorEditorScene::setActionType( EActionType nActionType )
{
	m_nActionType = nActionType;

}

int CIndicatorEditorScene::type() const
{
	return m_nClassType;
}






void CIndicatorEditorScene::mousePressEvent(QGraphicsSceneMouseEvent* mouseEvent)
{
	if (mouseEvent->button() != Qt::LeftButton)
	{
		return;
	}
	CSceneInsertLineParam* pSceneInsertLineParam = NULL;

	pSceneInsertLineParam = new CSceneInsertLineParam();
	pSceneInsertLineParam->setMousePos(mouseEvent->scenePos());
	pSceneInsertLineParam->setLineColor(m_LineColor);
	pSceneInsertLineParam->setLineWidth(1);
	pSceneInsertLineParam->buildParam();

	switch (m_nActionType) 
	{
	case ActionType_Insert_CInformationRectItemEdge:		
		_InsertLine(pSceneInsertLineParam);
		break;		
	default:
		break;
	}

	if (NULL != pSceneInsertLineParam)
	{
		delete pSceneInsertLineParam;
		pSceneInsertLineParam = NULL;
	}

	QGraphicsScene::mousePressEvent(mouseEvent);


}





void CIndicatorEditorScene::_InsertTitle(CSceneInsertTitleParam* pSceneInsertTitleParam)
{
	QRectF rectItem;
	CInformationTextItem* pInformationTextItem = NULL;

	pInformationTextItem = new CInformationTextItem(NULL, this, CInformationTextItem::TextItemType_Title);
	pInformationTextItem->SetTextItemFont(pSceneInsertTitleParam->m_TextFont);
	pInformationTextItem->setDefaultTextColor(pSceneInsertTitleParam->m_TextColor);
	pInformationTextItem->setTextInteractionFlags(Qt::TextEditorInteraction);
	pInformationTextItem->setZValue(1000.0);
	//pInformationTextItem->setDefaultTextColor(m_ColorText);
	pInformationTextItem->setPos(pSceneInsertTitleParam->m_pointMousePos);
	pInformationTextItem->setHtml("Title");

	QObject::connect(pInformationTextItem, SIGNAL(signalEditorLostFocus(CInformationTextItem*)), this, SLOT(slotEditorLostFocus(CInformationTextItem*)));
	QObject::connect(pInformationTextItem, SIGNAL(selectedChange(QGraphicsItem*)),  this, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));

	//this->addItem(pInformationTextItem);


	m_nActionType = ActionType_MoveItem;
}

void CIndicatorEditorScene::_InsertRect(CSceneInsertRectParam* pSceneInsertRectParam)
{
	QRectF rectItem;
	CInfomationItemInEditor* pInfomationItemInEditor = NULL;

	rectItem = QRectF(DEF_VALUE_InfomationRectItem_X, DEF_VALUE_InfomationRectItem_Y, DEF_VALUE_InfomationRectItem_Width, DEF_VALUE_InfomationRectItem_Height);

	pInfomationItemInEditor = new CInfomationItemInEditor(rectItem, NULL, this);

	QObject::connect(pInfomationItemInEditor->getTopTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  this, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));
	QObject::connect(pInfomationItemInEditor->getBottomTextHandle(), SIGNAL(selectedChange(QGraphicsItem*)),  this, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)));

	pInfomationItemInEditor->setItemPos(pSceneInsertRectParam->m_pointItemLeftTop);
	pInfomationItemInEditor->SetLineColor(pSceneInsertRectParam->m_RectLineColor);
	pInfomationItemInEditor->getTopTextHandle()->SetTextItemFont(pSceneInsertRectParam->m_TextFontTop);
	pInfomationItemInEditor->getTopTextHandle()->SetTextItemColor(pSceneInsertRectParam->m_TextColorTop);
	pInfomationItemInEditor->getBottomTextHandle()->SetTextItemFont(pSceneInsertRectParam->m_TextFontBottom);
	pInfomationItemInEditor->getBottomTextHandle()->SetTextItemColor(pSceneInsertRectParam->m_TextColorBottom);
	
	this->addItem(pInfomationItemInEditor);

	if (pInfomationItemInEditor->isColliding())
	{
		this->removeItem(pInfomationItemInEditor);
		delete pInfomationItemInEditor;
		pInfomationItemInEditor = NULL;
	}

	m_nActionType = ActionType_MoveItem;
}


void CIndicatorEditorScene::_InsertLine(CSceneInsertLineParam* pSceneInsertLineParam)
{
	//ActionType_InsertLine
	m_pGraphicsLineItemTmp = new QGraphicsLineItem(pSceneInsertLineParam->m_lineValue);
	m_pGraphicsLineItemTmp->setPen(pSceneInsertLineParam->m_penForLine);
	this->addItem(m_pGraphicsLineItemTmp);	
}



void CIndicatorEditorScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
{

	if (ActionType_Insert_CInformationRectItemEdge == m_nActionType && NULL != m_pGraphicsLineItemTmp) 
	{
		QLineF newLine(m_pGraphicsLineItemTmp->line().p1(), mouseEvent->scenePos());
		m_pGraphicsLineItemTmp->setLine(newLine);
	} 
	else if (ActionType_MoveItem == m_nActionType) 
	{
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
	else 
	{
		QGraphicsScene::mouseMoveEvent(mouseEvent);
	}
}

void CIndicatorEditorScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
	if (ActionType_Insert_CInformationRectItemEdge != m_nActionType 
		|| NULL == m_pGraphicsLineItemTmp)
	{
		QGraphicsScene::mouseReleaseEvent(mouseEvent);
		return;
	}

	//if (ActionType_Insert_CInformationRectItemEdge == m_nActionType && NULL != m_pGraphicsLineItemTmp) 

	QPointF pointLineStart;
	QPointF pointLineEnd;
	int nItemIndexStart = 0;
	int nItemIndexEnd = 0;
	QList<QGraphicsItem *>::Iterator iterLst;
	EProjectClassType nClassTypeStart = ClassType_Begin;
	EProjectClassType nClassTypeEnd = ClassType_Begin;
	QList<QGraphicsItem *> lstStartItems;
	QList<QGraphicsItem *> lstEndItems;

	pointLineStart = m_pGraphicsLineItemTmp->line().p1();
	pointLineEnd = m_pGraphicsLineItemTmp->line().p2();

	//
	lstStartItems = this->items(m_pGraphicsLineItemTmp->line().p1());
	if (lstStartItems.count() && lstStartItems.first() == m_pGraphicsLineItemTmp)
	{
		lstStartItems.removeFirst();
	}
	//
	lstEndItems = this->items(m_pGraphicsLineItemTmp->line().p2());
	if (lstEndItems.count() && lstEndItems.first() == m_pGraphicsLineItemTmp)
	{
		lstEndItems.removeFirst();
	}

	//
	removeItem(m_pGraphicsLineItemTmp);
	if (NULL != m_pGraphicsLineItemTmp)
	{
		delete m_pGraphicsLineItemTmp;
		m_pGraphicsLineItemTmp = NULL;
	}

	if (lstStartItems.count() <= 0 || lstEndItems.count() <= 0)
	{
		return;
	}

	nItemIndexStart = 0;
	iterLst = lstStartItems.begin();
	while (iterLst != lstStartItems.end())
	{
		nClassTypeStart = (EProjectClassType)(*iterLst)->type();

		if (ClassType_CInfomationItemInEditor == nClassTypeStart)
		{
			break;
		}
		nItemIndexStart++;
		iterLst++;
	}



	nItemIndexEnd = 0;
	iterLst = lstEndItems.begin();
	while (iterLst != lstEndItems.end())
	{
		nClassTypeEnd = (EProjectClassType)(*iterLst)->type();

		if (ClassType_CInfomationItemInEditor == nClassTypeEnd)
		{
			break;
		}
		nItemIndexEnd++;
		iterLst++;
	}


	//nClassTypeStart = (EProjectClassType)(lstStartItems.first()->type());
	//nClassTypeEnd = (EProjectClassType)(lstEndItems.first()->type());


	if (lstStartItems.count() > 0 
		&& lstEndItems.count() > 0
		&& (ClassType_CInfomationItemInEditor == nClassTypeStart)
		&& (ClassType_CInfomationItemInEditor == nClassTypeEnd)
		//&& lstStartItems.first() != lstEndItems.first()
		&& lstStartItems.at(nItemIndexStart) != lstEndItems.at(nItemIndexEnd)
		) 
	{
		CInformationRectItemEdge::EEdgeType nEdgeType;
		//CInformationBase* pStartItem = qgraphicsitem_cast<CInformationBase *>(lstStartItems.first());
		//CInformationBase* pEndItem = qgraphicsitem_cast<CInformationBase *>(lstEndItems.first());
		CInformationBase* pStartItem = qgraphicsitem_cast<CInformationBase *>(lstStartItems.at(nItemIndexStart));
		CInformationBase* pEndItem = qgraphicsitem_cast<CInformationBase *>(lstEndItems.at(nItemIndexEnd));
		QPointF pointStartItem = pStartItem->getItemPos();

		//delete old one
		pStartItem->removeDestEdge();

		//add new one
		nEdgeType = pEndItem->checkEdgeTypeByPos(pointLineEnd);
		if (CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Top == nEdgeType
			|| CInformationRectItemEdge::EdgeType_Source_Middle_To_Dest_Bottom == nEdgeType)
		{
			pStartItem->setDestNode(pEndItem, nEdgeType);
			pStartItem->adjustPos(pointStartItem);
		}

	}

	QGraphicsScene::mouseReleaseEvent(mouseEvent);
}


void CIndicatorEditorScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	EActionType nActionType;
	EProjectClassType nDragItemType;
	CDragRectParam* pDragRectParam = NULL;
	CDragTextParam* pDragTextParam = NULL;
	CSceneInsertRectParam* pSceneInsertRectParam = NULL;
	CSceneInsertTitleParam* pSceneInsertTitleParam = NULL;
	QString strDataType;
	EProjectClassType nDataType;

	if (event->mimeData()->hasText())
	{
		event->setAccepted(true);
	}
	else
	{
		return;
	}

	strDataType = qvariant_cast<QString>(event->mimeData()->text());
	nDataType = (EProjectClassType)(strDataType.toInt());

	pDragRectParam = new CDragRectParam();
	pDragTextParam = new CDragTextParam();
	pSceneInsertRectParam = new CSceneInsertRectParam();
	pSceneInsertTitleParam = new CSceneInsertTitleParam();

	if (ClassType_CDragRectParam == nDataType)
	{
		pDragRectParam->getDataFromContainer(event->mimeData());
		nDragItemType = (EProjectClassType)(pDragRectParam->m_nDragItemType);
	}
	else if (ClassType_CDragTextParam == nDataType)
	{
		pDragTextParam->getDataFromContainer(event->mimeData());
		nDragItemType = (EProjectClassType)(pDragTextParam->m_nDragItemType);
	}


	//get param value


	if (ClassType_CRectItemInBox == nDragItemType)
	{
		nActionType = ActionType_Insert_CInfomationItemInEditor;
		pSceneInsertRectParam->setValuePointMousePos(event->scenePos());
		pSceneInsertRectParam->setValue(pDragRectParam);
		pSceneInsertRectParam->buildParam();
	}
	else if (ClassType_CTextItemInBox == nDragItemType)
	{
		nActionType = ActionType_Insert_CInformationTextItem;
		pSceneInsertTitleParam->setMousePos(event->scenePos());
		pSceneInsertTitleParam->setValue(pDragTextParam);
		pSceneInsertTitleParam->buildParam();
	}

	switch (nActionType) 
	{
	case ActionType_Insert_CInfomationItemInEditor:
		_InsertRect(pSceneInsertRectParam);
		break;
	case ActionType_Insert_CInformationTextItem:
		_InsertTitle(pSceneInsertTitleParam);
		break;
	default:
		break;
	}

	this->update();


	//////////////////////////////////////////////////////////////////////////

	if (NULL != pSceneInsertRectParam)
	{
		delete pSceneInsertRectParam;
		pSceneInsertRectParam = NULL;
	}

	if (NULL != pDragRectParam)
	{
		delete pDragRectParam;
		pDragRectParam = NULL;
	}


	if (NULL != pDragTextParam)
	{
		delete pDragTextParam;
		pDragTextParam = NULL;
	}
	
	
}



void CIndicatorEditorScene::slotActionDeleteTriggered()
{
	EProjectClassType nClassTypeSelect = ClassType_Begin;
	CInformationTextItem* pTextTmp = NULL; 
	CInformationRectItemEdge* pEdgeTmp = NULL;
	CInformationBase* pSourceNodeTmp = NULL;
	CInformationBase* pDestNodeTmp = NULL;
	QList<QGraphicsItem *> lstSelectedItems;

	lstSelectedItems = this->selectedItems();



	foreach (QGraphicsItem *item, lstSelectedItems)
	{
		nClassTypeSelect = (EProjectClassType)item->type();

		if (ClassType_CInfomationItemInEditor == nClassTypeSelect) 
		{
			pSourceNodeTmp = qgraphicsitem_cast<CInformationBase *>(item);

			this->removeItem(pSourceNodeTmp);

			if (NULL != pSourceNodeTmp)
			{
				delete pSourceNodeTmp;
				pSourceNodeTmp = NULL;
			}
		}
		else if (ClassType_CInformationTextItem == nClassTypeSelect)
		{
			pTextTmp = (CInformationTextItem*)(item);
			this->removeItem(pTextTmp);
			if (NULL != pTextTmp)
			{
				delete pTextTmp;
				pTextTmp = NULL;
			}

		}
		else if (nClassTypeSelect == ClassType_CInformationRectItemEdge) 
		{
			pEdgeTmp = qgraphicsitem_cast<CInformationRectItemEdge *>(item);
			pSourceNodeTmp = (CInformationBase*)(pEdgeTmp->getSourceNode());
			pSourceNodeTmp->removeDestEdge();
		}
	}

	lstSelectedItems.clear();
}


void CIndicatorEditorScene::slotEditorLostFocus(CInformationTextItem* item)
{
	QTextCursor cursor = item->textCursor();
	cursor.clearSelection();
	item->setTextCursor(cursor);

	if (item->toPlainText().isEmpty()) 
	{
		this->removeItem(item);
		item->deleteLater();
	}
}

bool CIndicatorEditorScene::_IsItemChange(int nTypeValue)
{
	bool bIsItemChange = false;
	QList<QGraphicsItem *> lstSelectedItems = this->selectedItems();

	foreach (QGraphicsItem* item, lstSelectedItems) 
	{
		if (item->type() == nTypeValue)
		{
			bIsItemChange = true;
			return bIsItemChange;
		}
	}
	return bIsItemChange;
}

QFont CIndicatorEditorScene::getEditorSceneFont() const
{
	return m_fontInScene;
}

void CIndicatorEditorScene::setEditorSceneFont( const QFont& fontValue, const QColor& colorValue)
{
	m_fontInScene = fontValue;
	m_colorInScene = colorValue;

	if (_IsItemChange(ClassType_CInformationTextItem)) 
	{
		//At this point the selection can change so the first selected item might not be a CInformationTextItem

		CInformationTextItem* pGraphicsTextItem = NULL;
		QList<QGraphicsItem *> lstSelectedItems = this->selectedItems();

		foreach (QGraphicsItem* pGraphicsItem, lstSelectedItems) 
		{
			if (pGraphicsItem->type() == ClassType_CInformationTextItem)
			{
				pGraphicsTextItem = NULL;
				//pGraphicsTextItem = qgraphicsitem_cast<CInformationTextItem *>(pGraphicsItem);
				pGraphicsTextItem = (CInformationTextItem *)(pGraphicsItem);

				if (NULL != pGraphicsTextItem)
				{
					pGraphicsTextItem->SetTextItemFont(m_fontInScene);
					pGraphicsTextItem->setDefaultTextColor(m_colorInScene);
				}

			}
		}//foreach

	}
}

//QT_END_NAMESPACE

