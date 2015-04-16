#include "IndicatorEditorScene.h"
#include "coloritem.h"
#include "RectItem.h"


//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorScene= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorScene = 600;

static const std::string DEFVALUE_String_CIndicatorEditorScene_Title = "Indicator Editor Secne";


CIndicatorEditorScene::CIndicatorEditorScene(QObject *parent)
:QGraphicsScene(parent)
{
	//setAcceptDrops(true);

}

CIndicatorEditorScene::~CIndicatorEditorScene()
{

}



//void CIndicatorEditorScene::dragMoveEvent(QGraphicsSceneDragDropEvent *event)
//void CIndicatorEditorScene::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
//void CIndicatorEditorScene::dropEvent(QGraphicsSceneDragDropEvent *event)
void CIndicatorEditorScene::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
	QString strXValue;
	QString strYValue;

	m_bDragOver = false;
	if (event->mimeData()->hasColor())
	{
		event->setAccepted(true);
		m_nDragColor = qvariant_cast<QColor>(event->mimeData()->colorData());
		m_nColor = m_nDragColor;
		//strXValue = QString(qvariant_cast<QByteArray>(event->mimeData()->data("xValue")).data());
		//strYValue = QString(qvariant_cast<QByteArray>(event->mimeData()->data("yValue")).data());

		strXValue = QString(event->mimeData()->data("xValue").data());
		strYValue = QString(event->mimeData()->data("yValue").data());
// 		strXValue = "10";
// 		strYValue = "10";
	}


	CRectItem* pItem = NULL;
	QPointF pointMousePos;
	QPointF pointItemPos;
	QPointF pointHot;

	pointMousePos = event->scenePos();
	pointHot.setX(strXValue.toInt());
	pointHot.setY(strYValue.toInt());

	pointItemPos.setX(pointMousePos.x() - pointHot.x());
	pointItemPos.setY(pointMousePos.y() - pointHot.y());

	pItem = new CRectItem();
	pItem->setColor(m_nColor);
	pItem->setItemPos(pointItemPos);
	this->addItem(pItem);
	pItem = NULL;


	//QGraphicsScene::dragLeaveEvent(event);
	update();
}

