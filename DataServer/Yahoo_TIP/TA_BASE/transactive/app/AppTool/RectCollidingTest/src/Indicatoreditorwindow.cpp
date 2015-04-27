#include "IndicatorEditorWindow.h"
#include "CommonData.h"
#include "InformationRectItem.h"

//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorWindow= 600;
static int DEFVALUE_Int_Hight_CIndicatorEditorWindow = 600;


static const std::string DEFVALUE_String_CIndicatorEditorWindow_Title = "Indicator Editor Window";







CIndicatorEditorWindow::CIndicatorEditorWindow( QWidget* parent /*= 0*/ )
:QWidget(parent)
{
	m_nClassType = ClassType_CIndicatorEditorWindow;

	m_pHBoxLayout = NULL;
	m_pIndicatorEditorView = NULL;
	m_pIndicatorEditorScene = NULL;
	setupUi(this);
}

CIndicatorEditorWindow::~CIndicatorEditorWindow()
{

}


void CIndicatorEditorWindow::setupUi(QWidget* pWindow)
{
	m_rectScene = QRectF(0, 0, 1500, 1500);

	if (pWindow->objectName().isEmpty())
	{
		pWindow->setObjectName(QString::fromUtf8("ObjectName_CIndicatorEditorWindow"));
	}
	pWindow->resize(DEFVALUE_Int_Wide_CIndicatorEditorWindow, DEFVALUE_Int_Hight_CIndicatorEditorWindow);

	m_pHBoxLayout = new QHBoxLayout(this);
	m_pIndicatorEditorView = new QGraphicsView(this);
	m_pIndicatorEditorView->resize(m_rectScene.width(), m_rectScene.height());

	m_pIndicatorEditorScene = new QGraphicsScene(this);
	m_pIndicatorEditorScene->setSceneRect(m_rectScene);

	m_pIndicatorEditorView->setScene(m_pIndicatorEditorScene);



	_AddRects();


	m_pHBoxLayout->addWidget(m_pIndicatorEditorView);

	this->setLayout(m_pHBoxLayout);
	retranslateUi(pWindow);

	QMetaObject::connectSlotsByName(pWindow);
} 

void CIndicatorEditorWindow::_AddRects()
{
	CInformationRectItem* pRectItem = NULL;
	QRectF rect;
	QPointF point;

	rect.setX(DEF_VALUE_InfomationRectItem_X);
	rect.setY(DEF_VALUE_InfomationRectItem_Y);
	rect.setWidth(DEF_VALUE_InfomationRectItem_Width);
	rect.setHeight(DEF_VALUE_InfomationRectItem_Height);

	pRectItem = new CInformationRectItem(rect);
	point.setX(DEF_VALUE_InfomationRectItem_X);
	point.setY(DEF_VALUE_InfomationRectItem_Y);
	pRectItem->setItemPos(point);

	m_pIndicatorEditorScene->addItem(pRectItem);


	pRectItem = new CInformationRectItem(rect);
	point.setX(DEF_VALUE_InfomationRectItem_X + DEF_VALUE_InfomationRectItem_Width * 2);
	point.setY(DEF_VALUE_InfomationRectItem_Y);
	pRectItem->setItemPos(point);

	m_pIndicatorEditorScene->addItem(pRectItem);
}


void CIndicatorEditorWindow::retranslateUi(QWidget *pWindow)
{
	pWindow->setWindowTitle(
		QApplication::translate(DEFVALUE_String_CIndicatorEditorWindow_Title.c_str(), 
		DEFVALUE_String_CIndicatorEditorWindow_Title.c_str(), 
		0, QApplication::UnicodeUTF8));
} 

EProjectClassType CIndicatorEditorWindow::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CIndicatorEditorWindow::type() const
{
	return m_nClassType;
}





//QT_END_NAMESPACE

