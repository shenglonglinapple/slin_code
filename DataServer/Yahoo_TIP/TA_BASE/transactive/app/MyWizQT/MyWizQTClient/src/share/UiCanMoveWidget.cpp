#include "share/UiCanMoveWidget.h"

#include "share/UiRect9GridWidget.h"

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtGui/QBoxLayout>
#include <QtCore/QDebug>

static const bool DEV_VALUE_IN_THIS_FILE_PRINT_LOG = false;

CUiCanMoveWindow::CUiCanMoveWindow( QWidget* parent /*= 0*/ )
 : QWidget(parent)
{
	m_bMousePressed = false;
	m_bCanMove = true;
	//Ui level 0, nothing
	_SetAttribute();
	//Ui level 1
	m_pUiImageBorderWidget = new CUiRect9GirdWidget(this);

	//用一个QBoxLayout来设置m_pShadowWidget的大小和CUiShadowWindow一样大
	QBoxLayout* windowLayout = NULL;
	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	windowLayout->setContentsMargins(0, 0, 0, 0);
	windowLayout->setSpacing(0);
	windowLayout->addWidget(m_pUiImageBorderWidget);//m_pShadowWidget's rect = CUiShadowWindow's rect
	//
	this->setLayout(windowLayout);
}
void CUiCanMoveWindow::_SetAttribute()
{
	//
	//enable MainWindow to be transparent
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	/*
	空白（margin）和间距（spacing）
	每种布局都有两个重要的属性，空白和间距。空白指的是整个布局四周距离窗体边缘的距离；间距指的是布局管理器内部各个窗口部件之间的距离。
	*/
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking 鼠标跟踪
	//this->setMouseTracking(true);

	// 不继承父组件的背景色
	//setAutoFillBackground(true);
}


void CUiCanMoveWindow::mousePressEvent( QMouseEvent *event )
{
	m_bMousePressed = true;
	m_ptGlobalOldTopLeft = mapToGlobal(this->rect().topLeft());
	m_ptGlobalMousePress = event->globalPos();

	if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
	{
		qDebug()<<"mousePressEvent"
			<<" "<<"m_ptGlobalOldTopLeft.x="<<m_ptGlobalOldTopLeft.x()
			<<" "<<"m_ptGlobalOldTopLeft.y="<<m_ptGlobalOldTopLeft.y();
		qDebug()<<"mousePressEvent"
			<<" "<<"m_ptGlobalMousePress.x="<<m_ptGlobalMousePress.x()
			<<" "<<"m_ptGlobalMousePress.y="<<m_ptGlobalMousePress.y();
	}
	
	//
	QWidget::mousePressEvent(event);
}
//mousePress
void CUiCanMoveWindow::mouseMoveEvent( QMouseEvent *event )
{
	if (m_bCanMove && m_bMousePressed)
	{	
		QPoint ptGlobalCurrent;
		QPoint ptGlobalMouseMoved;
		QPoint ptGlobalNewTopLeft;

		ptGlobalCurrent = event->globalPos();
		ptGlobalMouseMoved = ptGlobalCurrent - m_ptGlobalMousePress;
		ptGlobalNewTopLeft = m_ptGlobalOldTopLeft + ptGlobalMouseMoved;
		this->move(ptGlobalNewTopLeft);//(742,325)

		if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
		{
			qDebug()<<"mouseMoveEvent"
				<<" "<<"ptGlobalCurrent.x="<<ptGlobalCurrent.x()
				<<" "<<"ptGlobalCurrent.y="<<ptGlobalCurrent.y();
			qDebug()<<"mouseMoveEvent"
				<<" "<<"ptGlobalMouseMoved.x="<<ptGlobalMouseMoved.x()
				<<" "<<"ptGlobalMouseMoved.y="<<ptGlobalMouseMoved.y();
			qDebug()<<"mouseMoveEvent"
				<<" "<<"ptGlobalNewTopLeft.x="<<ptGlobalNewTopLeft.x()
				<<" "<<"ptGlobalNewTopLeft.y="<<ptGlobalNewTopLeft.y();
		}//if (0)
	}
}


void CUiCanMoveWindow::mouseReleaseEvent( QMouseEvent *event )
{
	m_bMousePressed = false;
	//
	QWidget::mouseReleaseEvent(event);
}
void CUiCanMoveWindow::setCanMove( bool bValue )
{
	m_bCanMove = bValue; 
}

bool CUiCanMoveWindow::canMove() const
{
	return m_bCanMove;
}
