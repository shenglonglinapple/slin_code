#include "IndicatorToolView.h"


//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorView= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorView = 600;

static const std::string DEFVALUE_String_CIndicatorEditorView_Title = "Indicator Editor Window";

CIndicatorToolView::CIndicatorToolView(QWidget* parent)
:QGraphicsView(parent)
{
	// 使用抗锯齿渲染
	setRenderHint(QPainter::Antialiasing);

	// 设置缓存背景，这样可以加快渲染速度
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	
	setDragMode(QGraphicsView::ScrollHandDrag);
}

CIndicatorToolView::~CIndicatorToolView()
{

}





