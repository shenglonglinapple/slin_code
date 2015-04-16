#include "mainwindow.h"

#include <QtGui/QGridLayout>
#include "TestMyThreadManager.h"


static int DEFVALUE_INT_Window_Width = 400;
static int DEFVALUE_INT_Window_Height = 400;



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
	this->resize(DEFVALUE_INT_Window_Width, DEFVALUE_INT_Window_Height);
	
	QGridLayout* pGridLayout = NULL;
	pGridLayout = new QGridLayout(this);
	m_pPushButton_dotest = new QPushButton(this);
	m_pPushButton_dotest->setText(QObject::tr("do_test"));

	QObject::connect(m_pPushButton_dotest, 
		SIGNAL(clicked(bool)),
		this, 
		SLOT(slotButtonDoTestClicked(bool)));

	pGridLayout->addWidget(m_pPushButton_dotest,0, 0, 1, 1);

	

}

MainWindow::~MainWindow()
{



}

void MainWindow::slotButtonDoTestClicked( bool bValue )
{
	CTestMyThreadManager* m_pTestMyThreadManager;

	m_pTestMyThreadManager = new CTestMyThreadManager();
	//m_pTestMyThreadManager->do_test_mythread_1();
	m_pTestMyThreadManager->do_test_mythread_2();
	


	if (NULL != m_pTestMyThreadManager)
	{
		delete m_pTestMyThreadManager;
		m_pTestMyThreadManager = NULL;
	}
}
