#include "ItemBoxView.h"
#include "ItemBoxScene.h"
#include "RectItemInBox.h"
#include "TextItemInBox.h"

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CItemBoxView = 200;
static int DEFVALUE_Int_Hight_CItemBoxView = 600;

static const std::string DEFVALUE_String_CItemBoxView_Title = "Base Item";



CItemBoxView::CItemBoxView( QWidget *parent /*= 0*/ )
:QGraphicsView(parent)
{
	setCacheMode(QGraphicsView::CacheBackground);//设置缓存背景，这样可以加快渲染速度/
	//setDragMode(QGraphicsView::ScrollHandDrag);
	setRenderHint(QPainter::Antialiasing);// 使用抗锯齿渲染
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	//setBackgroundBrush(QColor(0, 200, 0));
	setWindowTitle(QObject::tr(DEFVALUE_String_CItemBoxView_Title.c_str()));

	m_pItemBoxScene = NULL;
	m_pItemBoxScene = new CItemBoxScene(NULL);
	m_pItemBoxScene->setSceneRect(0, 0, DEFVALUE_Int_Wide_CItemBoxView - 1, DEFVALUE_Int_Hight_CItemBoxView - 1);

	QRectF rectItem = QRectF(DEF_VALUE_InfomationRectItem_X, DEF_VALUE_InfomationRectItem_Y, DEF_VALUE_InfomationRectItem_Width, DEF_VALUE_InfomationRectItem_Height);
	CRectItemInBox* pRectItemInBox = NULL;
	CTextItemInBox* pTextItemInBox = NULL;

	pTextItemInBox = new CTextItemInBox(NULL, m_pItemBoxScene);
	pTextItemInBox->setPos(20, 20);
	m_pItemBoxScene->addItem(pTextItemInBox);
	pTextItemInBox = NULL;

	pRectItemInBox = new CRectItemInBox(rectItem, NULL, m_pItemBoxScene);
	pRectItemInBox->setItemPos(QPointF(20, 100));
	m_pItemBoxScene->addItem(pRectItemInBox);
	pRectItemInBox = NULL;

	this->setScene(m_pItemBoxScene);
	this->resize(DEFVALUE_Int_Wide_CItemBoxView, DEFVALUE_Int_Hight_CItemBoxView);
}

CItemBoxView::~CItemBoxView()
{

}

