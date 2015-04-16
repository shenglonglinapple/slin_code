#include "DataFileNameWindow.h"
#include "CommonData.h"


//#include "BoostLogger.h"
//USING_BOOST_LOG;


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

//////////////////////////////////////////////////////////////////////////
static int DEFVALUE_Int_Width_CDataFileNameWindow = 400;
static int DEFVALUE_Int_Hight_CDataFileNameWindow = 600;


static const std::string DEFVALUE_String_CDataFileNameWindow_Title = "DataFileName Window";

static const std::string DEFVALUE_String_List_File_UserDefineInfomation = "UserDefineInfomation.file";






CDataFileNameWindow::CDataFileNameWindow( QWidget* parent /*= 0*/ )
:QWidget(parent)
{
	m_pHBoxLayout = NULL;

	setupUi(this);
	_CreateConnect();
}

CDataFileNameWindow::~CDataFileNameWindow()
{

}


void CDataFileNameWindow::setupUi(QWidget* pWindow)
{
	if (pWindow->objectName().isEmpty())
	{
		pWindow->setObjectName(QString::fromUtf8("ObjectName_CDataFileNameWindow"));
	}
	pWindow->resize(DEFVALUE_Int_Width_CDataFileNameWindow, DEFVALUE_Int_Hight_CDataFileNameWindow);

	m_pHBoxLayout = new QHBoxLayout(pWindow);
	m_pStringListModel = new QStringListModel(pWindow);
	m_pListView = new QListView(pWindow);

	m_StringList.push_back(DEFVALUE_String_List_File_UserDefineInfomation.c_str());

	m_pStringListModel->setStringList(m_StringList);


	m_pListView->setObjectName(QString::fromUtf8("ObjectName_CDataFileNameWindow_QListView"));
	m_pListView->setModel(m_pStringListModel);
	//m_pListView->setEditTriggers(QAbstractItemView::AnyKeyPressed  | QAbstractItemView::DoubleClicked);
	m_pListView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pListView->setAlternatingRowColors(true);
	m_pListView->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_pListView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);


	m_pHBoxLayout->addWidget(m_pListView);

	this->setLayout(m_pHBoxLayout);
	retranslateUi(pWindow);

	QMetaObject::connectSlotsByName(pWindow);
} 

void CDataFileNameWindow::retranslateUi(QWidget *pWindow)
{
	pWindow->setWindowTitle(
		QApplication::translate(DEFVALUE_String_CDataFileNameWindow_Title.c_str(), 
		DEFVALUE_String_CDataFileNameWindow_Title.c_str(), 
		0, QApplication::UnicodeUTF8));
} 

void CDataFileNameWindow::_CreateConnect()
{
	//
	QObject::connect(m_pListView, 
		SIGNAL(doubleClicked ( const QModelIndex)),
		this,
		SLOT(slotListViewDoubleClicked(const QModelIndex)));


}

void CDataFileNameWindow::slotListViewDoubleClicked(const QModelIndex& index)
{
	int nRowDoubleClick = 0;
	int nColumnDoubleClick = 0;
	QString strTmp;

	nRowDoubleClick = index.row();
	nColumnDoubleClick = index.column();

	strTmp = m_pStringListModel->data(index, Qt::DisplayRole).toString();

	if (strTmp == QString(DEFVALUE_String_List_File_UserDefineInfomation.c_str()))
	{
		emit signalShowFile(QString(DEFVALUE_String_List_File_UserDefineInfomation.c_str()));
	}

}


//QT_END_NAMESPACE

