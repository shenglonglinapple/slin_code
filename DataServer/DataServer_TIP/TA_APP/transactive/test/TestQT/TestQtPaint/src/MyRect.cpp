#include "MyRect.h"
#include "CommonData.h"

#include "MyRectGraphicsItem.h"

#include <QtGui/QPainter>
#include <QtCore/QPoint>

//////////////////////////////////////////////////////////////////////////
class CMyRectData  
{
public:
	CMyRectData();
	virtual ~CMyRectData();
public:
	QPainter* m_pPainter;
};

CMyRectData::CMyRectData()
{
	m_pPainter = NULL;
	m_pPainter = new QPainter();
}

CMyRectData::~CMyRectData ()
{
	if (NULL != m_pPainter)
	{
		delete m_pPainter;
		m_pPainter = NULL;
	}
}

//////////////////////////////////////////////////////////////////////////

// constructor
CMyRect::CMyRect( QWidget* parent /*= 0*/ )
:QWidget(parent)
{
	m_pData = NULL;
	m_pGraphicsView = NULL;
	m_pGraphicsScene = NULL;
	m_pMyRectGraphicsItem = NULL;

	m_pData = new CMyRectData();

	_SetupWidgetUi();
}

// destructor
CMyRect::~CMyRect ()
{

	if (NULL != m_pMyRectGraphicsItem)
	{
		delete m_pMyRectGraphicsItem;
		m_pMyRectGraphicsItem = NULL;
	}

	if (NULL != m_pGraphicsScene)
	{
		delete m_pGraphicsScene;
		m_pGraphicsScene = NULL;
	}

	if (NULL != m_pGraphicsView)
	{
		delete m_pGraphicsView;
		m_pGraphicsView = NULL;
	}
	

	if (NULL != m_pData)
	{
		delete m_pData;
		m_pData = NULL;
	}

};

void CMyRect::_SetupWidgetUi()
{
	/*move to central*/
	this->setWindowTitle(tr("MyRect"));
	//this->setGeometry(0, 0, 800, 800);
	this->setFixedSize(800, 800);

	QDesktopWidget *desk = QApplication::desktop();   
	int wd = desk->width();   
	int ht = desk->height();   
	this->move( (wd - width())/2, (ht - height())/2 );   


	/*
	再有一个就是QGraphicsScene，我们可以把它理解成是一个画布，
	我们的QGraphicsItem都会绘制到这个画布上，
	然后再把这个画布“挂”到QGraphicsView这垛“墙”上展示出来
	*/

	m_pGraphicsView = new QGraphicsView(this);
	m_pGraphicsScene = new QGraphicsScene();
	m_pMyRectGraphicsItem = new CMyRectGraphicsItem();



	//设置“画布”矩形区域，坐标（-500，-500）为左上角，
	//这就意味着scene的中心位置为(0,0).这个坐标系就是scene的坐标系
	m_pGraphicsScene->setSceneRect(-500, -500, 1000, 1000);

	m_pGraphicsScene->addItem(m_pMyRectGraphicsItem);//往“画布”上绘制MyItem 
	//m_pMyRectGraphicsItem->setPos(0,0)设置MyItem在“画布”scene的位置，此时，就是把item相对于自己的坐标系的原点放到scene的（0,0）位置
	m_pMyRectGraphicsItem->setPos(0, 0);


	m_pGraphicsView->setObjectName(QString::fromUtf8("graphicsView"));
	m_pGraphicsView->setScene(m_pGraphicsScene);
	m_pGraphicsView->centerOn(0, 0);//把画布scene的中心位置放到QGraphicsView正中央 
	//m_pGraphicsView->setGeometry(QRect(0, 0, 600, 600));
	m_pGraphicsView->setFixedSize(600, 600);
	m_pGraphicsView->move(
		((this->width() - m_pGraphicsView->width()) / 2),
		((this->height() - m_pGraphicsView->height()) / 2)
		);



} // setupUi

void CMyRect::paintEvent( QPaintEvent *pEvent )
{
	//QPainter* painter = NULL;
	//painter = m_pData->m_pPainter;
	//painter->begin(this);
	//painter->setPen(QPen(Qt::blue, 4, Qt::DashLine)); //设置画笔形式 参数：颜色，线的类型，
	//painter->setBrush(QBrush(Qt::red, Qt::SolidPattern)); //设置画刷形式
	//painter->drawRect(20,20,160,160);//画 矩形
	//painter->drawEllipse(20,20,210,160);  //画椭圆 //   第1，2个参数分别表示圆/椭圆距左上角的像素数。第3,4个参数表示圆/椭圆的宽度和高度。更加确切地表述，这个圆或椭圆是在矩形中，这个矩形的左上角的顶点在坐标轴中的位置为（20，20），这个圆或椭圆的中心为这个矩形的中心，以下的都相似！！！
	//painter->drawRoundRect(20,20,210,160,50,50);//绘制圆角矩形    最后两个参数决定角的圆度。它可以为0到99之间的任意值（99代表最圆）。
	//painter->drawPie(20,20,210,160,0,500);//绘制扇形图  前四个参数定义圆(与drawEllipse()函数相同）。后两个参数定义圆的样式。0为起始角度（实际单位为1/16度），500为扇形所展开的角度(单位也为1/16度)。
	//painter->drawChord(20,20,210,160,500,1000);//绘制弦
	//painter->drawArc(20, 20, 210, 160, 500, 1000);//绘制圆弧
	//painter->end();
	//painter = NULL;
}
