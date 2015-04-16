#include "IndicatorEditorWindow.h"
#include "CommonData.h"
#include "IndicatorEditorScene.h"
#include "IndicatorEditorView.h"
#include "UserDefineInfomation.h"
#include "InformationTextItem.h"

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

	_CreateConnect();
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
	m_pIndicatorEditorView = new CIndicatorEditorView(this);
	m_pIndicatorEditorView->resize(m_rectScene.width(), m_rectScene.height());

	m_pIndicatorEditorScene = new CIndicatorEditorScene(this);
	m_pIndicatorEditorScene->setSceneRect(m_rectScene);

	m_pIndicatorEditorView->setScene(m_pIndicatorEditorScene);


	m_pHBoxLayout->addWidget(m_pIndicatorEditorView);

	this->setLayout(m_pHBoxLayout);
	retranslateUi(pWindow);

	QMetaObject::connectSlotsByName(pWindow);
} 

void CIndicatorEditorWindow::retranslateUi(QWidget* pWindow)
{
	pWindow->setWindowTitle(
		QApplication::translate(DEFVALUE_String_CIndicatorEditorWindow_Title.c_str(), 
		DEFVALUE_String_CIndicatorEditorWindow_Title.c_str(), 
		0, QApplication::UnicodeUTF8));
} 

void CIndicatorEditorWindow::slotShowFile(const QString& strFileName )
{
	setVisible(true);
	CUserDefineInfomation* pUserDefineInfomation;
	m_pIndicatorEditorScene->clear();
	pUserDefineInfomation = new CUserDefineInfomation(m_rectScene, NULL, m_pIndicatorEditorScene);
	m_pIndicatorEditorScene->addItem(pUserDefineInfomation);

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


void CIndicatorEditorWindow::slotMouseActionType( EActionType nActionType )
{
	m_pIndicatorEditorScene->setActionType(nActionType);
}



void CIndicatorEditorWindow::slotSceneScaleChanged(int nScaleVale)
{
    //qreal newScale = strScaleVale.left(strScaleVale.indexOf(tr("%"))).toDouble() / 100.0;
//     QMatrix oldMatrix = m_pIndicatorEditorView->matrix();
//     m_pIndicatorEditorView->resetMatrix();
//     m_pIndicatorEditorView->translate(oldMatrix.dx(), oldMatrix.dy());
//     m_pIndicatorEditorView->scale(newScale, newScale);

	qreal newScale = 0;
	QMatrix matrix;

	newScale = qreal(nScaleVale) / 1000;
	matrix.scale(newScale, newScale);
	m_pIndicatorEditorView->setMatrix(matrix);

}




void CIndicatorEditorWindow::slotActionDeleteTriggered()
{
	m_pIndicatorEditorScene->slotActionDeleteTriggered();
}



void CIndicatorEditorWindow::slotItemSelectedInScene( QGraphicsItem* item)
{
	EProjectClassType nItmeClassType;
	CInformationTextItem* pTextItem = NULL;
	QFont fontValue;
	QColor colorValue;

	if (NULL == item)
	{
		return;
	}
	nItmeClassType = (EProjectClassType)(item->type());

	if (ClassType_CInformationTextItem == nItmeClassType)
	{
		//pTextItem =	qgraphicsitem_cast<CInformationTextItem *>(item);
		pTextItem =	(CInformationTextItem *)(item);

		fontValue = pTextItem->GetTextItemFont();
		colorValue = pTextItem->defaultTextColor();

		emit signalShowFontInfo(fontValue, colorValue);
	}
}

void CIndicatorEditorWindow::_CreateConnect()
{
	connect(m_pIndicatorEditorScene, SIGNAL(singnalItemSelectedInScene(QGraphicsItem*)), this, SLOT(slotItemSelectedInScene(QGraphicsItem*)));

}

void CIndicatorEditorWindow::slotSetFontInfo(QFont fontValue,QColor colorValue)
{
	m_pIndicatorEditorScene->setEditorSceneFont(fontValue, colorValue);


}

//QT_END_NAMESPACE

