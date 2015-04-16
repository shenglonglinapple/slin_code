#include "IndicatorEditorView.h"



//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorView= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorView = 600;


static const std::string DEFVALUE_String_CIndicatorEditorView_Title = "Indicator Editor Window";






CIndicatorEditorView::CIndicatorEditorView( QWidget *parent /*= 0*/ )
:QGraphicsView(parent)
{
	m_nClassType = ClassType_CIndicatorEditorView;

	setupUi(this);

	// 使用抗锯齿渲染
	setRenderHint(QPainter::Antialiasing);

	// 设置缓存背景，这样可以加快渲染速度
	setCacheMode(QGraphicsView::CacheBackground);
	setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
	
	setDragMode(QGraphicsView::ScrollHandDrag);



// 	setViewportUpdateMode(BoundingRectViewportUpdate);
// 	setRenderHint(QPainter::Antialiasing);
// 	setTransformationAnchor(AnchorUnderMouse);
// 	scale(qreal(0.8), qreal(0.8));
// 	setMinimumSize(400, 400);

}

CIndicatorEditorView::~CIndicatorEditorView()
{

}

void CIndicatorEditorView::setupUi( QGraphicsView* pWindow )
{
	if (pWindow->objectName().isEmpty())
	{
		pWindow->setObjectName(QString::fromUtf8("ObjectName_CIndicatorEditorView"));
	}
	pWindow->resize(DEFVALUE_Int_Wide_CIndicatorEditorView, DEFVALUE_Int_Hight_CIndicatorEditorView);

	retranslateUi(pWindow);
}

void CIndicatorEditorView::retranslateUi( QGraphicsView *pWindow )
{

}


EProjectClassType CIndicatorEditorView::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CIndicatorEditorView::type() const
{
	return m_nClassType;
}

//QT_END_NAMESPACE

