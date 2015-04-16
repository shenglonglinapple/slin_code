#include "IndicatorEditorMainWindow.h"

#include <QtGui/QApplication>
#include <QtGui/QtGui>
#include <QtGui/QMenu> 
#include <QtGui/QCursor> 
#include <QtGui/QMessageBox>
#include "IndicatorEditorWindow.h"
#include "DataFileNameWindow.h"
#include "InformationTextItem.h"
#include "ItemBoxView.h"


//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Wide_CIndicatorEditorMainWindow = 1000;
static int DEFVALUE_Int_Hight_CIndicatorEditorMainWindow = 800;


static const std::string DEFVALUE_String_IndicatorEditorMainWindow_Title = "Indicator Editor Main Window";




CIndicatorEditorMainWindow::CIndicatorEditorMainWindow(QWidget* parent)
    : QMainWindow(parent)
{
	m_nClassType = ClassType_CIndicatorEditorMainWindow;
	m_colorValue = Qt::black;
	m_nFontActionType = FontActionType_Begin;

 	_CreateActions();
 	_CreateMenus();
 	_CreateToolBars();

    setupUi(this);

	_CreateConnect();

}


CIndicatorEditorMainWindow::~CIndicatorEditorMainWindow()
{

}

EProjectClassType CIndicatorEditorMainWindow::getClassType() const
{
	//ProjectClassType m_nClassType;
	return m_nClassType;
}
int CIndicatorEditorMainWindow::type() const
{
	return m_nClassType;
}
void CIndicatorEditorMainWindow::_CreateActions()
{
	m_pActionExit = new QAction(QObject::tr("E&xit"), this);
	m_pActionExit->setShortcuts(QKeySequence::Quit);
	m_pActionExit->setStatusTip(QObject::tr("Quit Program"));


	m_ActionDelete = new QAction(QIcon(":/images/delete.png"), QObject::tr("Delete"), this);
	m_ActionDelete->setShortcut(QObject::tr("Delete"));
	m_ActionDelete->setStatusTip(QObject::tr("Delete item from IndicatorEditor"));

	QPixmap pixmapSetFontColor(":/images/textpointer.png");
	m_pActionSetFontColor = new QAction(QObject::tr("SetFontColor"), this);
	//m_pActionSetFontColor->setCheckable(true);
	m_pActionSetFontColor->setIcon(QIcon(pixmapSetFontColor));


	//
	QPixmap pixmapActionBlod(":/images/bold.png");
	m_pActionBlod = new QAction(tr("Bold"), this);
	m_pActionBlod->setCheckable(true);
	m_pActionBlod->setIcon(QIcon(pixmapActionBlod));
	m_pActionBlod->setShortcut(tr("Ctrl+B"));
	//connect(m_pActionBlod, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	//
	m_pActionItalic = new QAction(QIcon(":/images/italic.png"), QObject::tr("Italic"), this);
	m_pActionItalic->setCheckable(true);
	m_pActionItalic->setShortcut(tr("Ctrl+I"));
	//connect(m_pActionItalic, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	//
	m_pActionUnderline = new QAction(QIcon(":/images/underline.png"), QObject::tr("Underline"), this);
	m_pActionUnderline->setCheckable(true);
	m_pActionUnderline->setShortcut(tr("Ctrl+U"));
	//connect(m_pActionUnderline, SIGNAL(triggered()), this, SLOT(slotFontChange()));



}

void CIndicatorEditorMainWindow::_CreateMenus()
{
	m_pMenuFile = this->menuBar()->addMenu(QObject::tr("&File"));
	m_pMenuFile->addAction(m_pActionExit);

}


void CIndicatorEditorMainWindow::_CreateToolBars()
{
	_CreateToolBarFont();//fonttype size blob static underline
	_CreateToolBarColor();
	_CreateToolBarEdit();//delete
	_CreateToolBarPointerType();//selectitem insertline
}




void CIndicatorEditorMainWindow::_CreateToolBarFont()
{
	QIntValidator* validator = NULL;

	//
	m_pToolBarText = addToolBar(tr("Font"));

	m_pComboBoxFont = new QFontComboBox();
	QObject::connect(m_pComboBoxFont, SIGNAL(currentFontChanged(QFont)), this, SLOT(slotCurrentFontChanged(QFont)));

	m_pComboBoxFontSize = new QComboBox();
	m_pComboBoxFontSize->setEditable(true);
	for (int nIndex = 2; nIndex < 80; nIndex = nIndex + 2)
	{
		m_pComboBoxFontSize->addItem(QString().setNum(nIndex));
	}
	validator = new QIntValidator(2, 80, this);
	m_pComboBoxFontSize->setValidator(validator);
	QObject::connect(m_pComboBoxFontSize, SIGNAL(currentIndexChanged(QString)), this, SLOT(slotFontSizeChanged(QString)));

	m_pToolBarText->addWidget(m_pComboBoxFont);
	m_pToolBarText->addWidget(m_pComboBoxFontSize);
	m_pToolBarText->addAction(m_pActionBlod);
	m_pToolBarText->addAction(m_pActionItalic);
	m_pToolBarText->addAction(m_pActionUnderline);
	m_pToolBarText->addAction(m_pActionSetFontColor);



}



void CIndicatorEditorMainWindow::_CreateToolBarColor()
{
	//
	//m_pToolBarColor = this->addToolBar(QObject::tr("Color"));
	//m_pToolBarColor->addAction(m_pActionSetFontColor);

	
}

void CIndicatorEditorMainWindow::_CreateToolBarEdit()
{
	//
	m_pToolBarEdit = this->addToolBar(QObject::tr("Edit"));
	m_pToolBarEdit->addAction(m_ActionDelete);

}
void CIndicatorEditorMainWindow::_CreateToolBarPointerType()
{
	//
	QToolButton *pToolButtonPointer = NULL;
	QToolButton *pToolButtonLinePointer = NULL;

	m_pToolBarPointer = this->addToolBar(QObject::tr("Pointer type"));

	m_pButtonGroupPointerType = new QButtonGroup(this);
	pToolButtonPointer = new QToolButton();
	pToolButtonLinePointer = new QToolButton();


	pToolButtonPointer->setCheckable(true);
	pToolButtonPointer->setChecked(true);
	pToolButtonPointer->setIcon(QIcon(":/images/pointer.png"));
	pToolButtonPointer->setToolTip(QObject::tr("SelectItem"));

	pToolButtonLinePointer->setCheckable(true);
	pToolButtonLinePointer->setIcon(QIcon(":/images/linepointer.png"));
	pToolButtonLinePointer->setToolTip(QObject::tr("InsertLine"));

	m_pButtonGroupPointerType->addButton(pToolButtonPointer, int(ActionType_MoveItem));
	m_pButtonGroupPointerType->addButton(pToolButtonLinePointer, int(ActionType_Insert_CInformationRectItemEdge));
	//connect(m_pButtonGroupPointerType, SIGNAL(buttonClicked(int)), this, SLOT(slotPointerGroupClicked(int)));//DiagramScene::Mode_MoveItem DiagramScene::Mode_InsertLine


	//connect(m_pComboBoxSceneScale, SIGNAL(currentIndexChanged(QString)), this, SLOT(sceneScaleChanged(QString)));

	QGroupBox* pGroupBoxScale = NULL;
	QVBoxLayout* pGroupLayoutScale = NULL;
	QSize nScaleSliderSize = QSize(400, 40);

	pGroupBoxScale = new QGroupBox(this);
	pGroupBoxScale->setTitle(tr("Scale"));
	m_pSliderScale = new QSlider(Qt::Horizontal, pGroupBoxScale);
	m_pSliderScale->setRange(1, 4000);
	m_pSliderScale->setValue(1000);
	//scaleSlider->setMaximumSize(nScaleSliderSize);
	//scaleSlider->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
	pGroupLayoutScale = new QVBoxLayout(pGroupBoxScale);
	pGroupLayoutScale->addWidget(m_pSliderScale);


	m_pToolBarPointer->addWidget(pToolButtonPointer);
	m_pToolBarPointer->addWidget(pToolButtonLinePointer);
	m_pToolBarPointer->addWidget(pGroupBoxScale);

}



void CIndicatorEditorMainWindow::_CreateConnect()
{

	//
	QObject::connect(m_pActionBlod, SIGNAL(triggered()), this, SLOT(slotFontChange()));
	QObject::connect(m_pActionItalic, SIGNAL(triggered()), this, SLOT(slotFontChange()));
	QObject::connect(m_pActionUnderline, SIGNAL(triggered()), this, SLOT(slotFontChange()));

	QObject::connect(m_pActionExit, SIGNAL(triggered()), this, SLOT(close()));

	QObject::connect(m_ActionDelete, SIGNAL(triggered()), m_pIndicatorEditorWindow, SLOT(slotActionDeleteTriggered()));
	QObject::connect(m_pActionSetFontColor, SIGNAL(triggered()), this, SLOT(slotActionSetFontColorTriggered()));


	QObject::connect(m_pSliderScale, SIGNAL(valueChanged(int)), m_pIndicatorEditorWindow, SLOT(slotSceneScaleChanged(int)));

	QObject::connect(this, SIGNAL(signalSetFontInfo(QFont, QColor)), m_pIndicatorEditorWindow, SLOT(slotSetFontInfo(QFont, QColor)));
	QObject::connect(m_pIndicatorEditorWindow, SIGNAL(signalShowFontInfo(QFont, QColor)), this, SLOT(slotShowFontInfo(QFont, QColor)));

	//
	QObject::connect(m_pDataFileNameWindow, 
		SIGNAL(signalShowFile(const QString&)),
		m_pIndicatorEditorWindow,
		SLOT(slotShowFile(const QString&)));


	QObject::connect(m_pButtonGroupPointerType, 
		SIGNAL(buttonClicked(int)), 
		this, 
		SLOT(slotButtonGroupPointerTypeClicked(int)));

	QObject::connect(this, 
		SIGNAL(signalMouseActionType(EActionType)),
		m_pIndicatorEditorWindow, 
		SLOT(slotMouseActionType(EActionType)));


}

void CIndicatorEditorMainWindow::setupUi(QMainWindow* pMainWindow)
{
	if (pMainWindow->objectName().isEmpty())
	{
		pMainWindow->setObjectName(QString::fromUtf8("ObjectName_CIndicatorEditorMainWindow"));
	}
	pMainWindow->resize(DEFVALUE_Int_Wide_CIndicatorEditorMainWindow, DEFVALUE_Int_Hight_CIndicatorEditorMainWindow);

	m_pWidgetCentral = new QWidget(pMainWindow);
	m_pHBoxLayout = new QHBoxLayout(pMainWindow);

	m_pItemBoxView = new CItemBoxView(pMainWindow);
	m_pIndicatorEditorWindow = new CIndicatorEditorWindow(pMainWindow);
	m_pDataFileNameWindow = new CDataFileNameWindow(pMainWindow);

	//m_pIndicatorEditorWindow->setVisible(false);



	m_TabWidgetView = new QTabWidget(pMainWindow);
	m_TabWidgetView->setTabPosition(QTabWidget::North);
	m_TabWidgetView->addTab(m_pIndicatorEditorWindow, "IndicatorEditorView");

	m_TabWidgetData = new QTabWidget(pMainWindow);
	m_TabWidgetData->setTabPosition(QTabWidget::North);
	m_TabWidgetData->addTab(m_pDataFileNameWindow, "IndicatorEditorData");
	
	m_pHBoxLayout->addWidget(m_pItemBoxView);
	//m_pHBoxLayout->addWidget(m_pToolBoxWindow);
	m_pHBoxLayout->addWidget(m_TabWidgetView);
	m_pHBoxLayout->addWidget(m_TabWidgetData);
	m_pHBoxLayout->setStretch(0, 1);
	m_pHBoxLayout->setStretch(1, 3);
	m_pHBoxLayout->setStretch(2, 1);
	m_pWidgetCentral->setLayout(m_pHBoxLayout);
	pMainWindow->setCentralWidget(m_pWidgetCentral);

	//m_pSqlitterV = new QSplitter(Qt::Horizontal);
	//m_pSqlitterV->addWidget(m_TabWidgetLeft);
	//m_pSqlitterV->addWidget(m_TabWidgetRight);
	//m_pSqlitterV->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	//m_pSqlitterV->setHandleWidth(1);
	//m_pSqlitterV->setStyleSheet("QSplitter::handle{background:lightgray;}");
// 	m_pSqlitterV->setStretchFactor(0, 1);//窗口高度比为3:1
// 	m_pSqlitterV->setStretchFactor(1, 1);

	
	//
	retranslateUi(pMainWindow);
	setUnifiedTitleAndToolBarOnMac(true);
	QMetaObject::connectSlotsByName(pMainWindow);
} 

void CIndicatorEditorMainWindow::retranslateUi(QMainWindow *pMainWindow)
{
	pMainWindow->setWindowTitle(
		QApplication::translate(DEFVALUE_String_IndicatorEditorMainWindow_Title.c_str(), 
		DEFVALUE_String_IndicatorEditorMainWindow_Title.c_str(), 
		0, QApplication::UnicodeUTF8));
} 




void CIndicatorEditorMainWindow::slotButtonGroupPointerTypeClicked(int nIndex)
{
	int nCheckedId = 0;
	EActionType nActionType;
	nCheckedId = m_pButtonGroupPointerType->checkedId();
	nActionType = (EActionType)nCheckedId;

	emit signalMouseActionType(nActionType);
}


void CIndicatorEditorMainWindow::slotFontChange()
{
	QFont fontValue = m_pComboBoxFont->currentFont();
	QString strFontSize;
	int nFontSize = 0;
	bool bFontBlod = false;
	int nFontWeight = QFont::Normal;
	bool nFontItalic = false;
	bool nFontUnderline = false;

	if (FontActionType_ShowValue == m_nFontActionType)
	{
		return;
	}
	m_nFontActionType = FontActionType_SetValue;

	strFontSize = m_pComboBoxFontSize->currentText();
	nFontSize = strFontSize.toInt();
	bFontBlod = m_pActionBlod->isChecked();
	nFontItalic = m_pActionItalic->isChecked();
	nFontUnderline = m_pActionUnderline->isChecked();

	if (bFontBlod)
	{
		nFontWeight = QFont::Bold;
	}
	else
	{
		nFontWeight = QFont::Normal;
	}

	fontValue.setPointSize(nFontSize);
	fontValue.setWeight(nFontWeight);
	fontValue.setItalic(nFontItalic);
	fontValue.setUnderline(nFontUnderline);

	m_FontValue = fontValue;

	//m_pIndicatorEditorWindow->_SetFont(fontValue);
	emit signalSetFontInfo(fontValue, m_colorValue);
}

void CIndicatorEditorMainWindow::slotCurrentFontChanged( const QFont& font )
{
	slotFontChange();
}
void CIndicatorEditorMainWindow::slotFontSizeChanged(const QString& strValue)
{
	slotFontChange();
}

void CIndicatorEditorMainWindow::slotShowFontInfo( QFont fontValue, QColor colorValue)
{
	QString strFontSize;
	int nFontSize = 0;
	bool bFontBlod = false;
	int nFontWeight = QFont::Normal;
	bool nFontItalic = false;
	bool nFontUnderline = false;
	m_nFontActionType = FontActionType_ShowValue;

	m_colorValue = colorValue;
	m_FontValue = fontValue;
	
	nFontSize = m_FontValue.pointSize();
	strFontSize = QString().setNum(nFontSize);
	nFontWeight = m_FontValue.weight();
	bFontBlod = false;
	if (QFont::Bold == nFontWeight )
	{
		bFontBlod = true;
	}
	nFontItalic = m_FontValue.italic();
	nFontUnderline = m_FontValue.underline();

	m_pComboBoxFont->setCurrentFont(m_FontValue);
	m_pComboBoxFontSize->setEditText(strFontSize);
	m_pActionBlod->setChecked(bFontBlod);
	m_pActionItalic->setChecked(nFontItalic);
	m_pActionUnderline->setChecked(nFontUnderline);
	m_nFontActionType = FontActionType_SetValue;

}

void CIndicatorEditorMainWindow::slotActionSetFontColorTriggered()
{
	QColor colorValue;

	colorValue = QColorDialog::getColor(
		m_colorValue, 
		NULL, 
		QObject::tr("ColorDialog"));

	if (colorValue.isValid())
	{
		m_colorValue = colorValue;
		m_nFontActionType = FontActionType_SetValue;
		slotFontChange();
	}
}

//QT_END_NAMESPACE

