#include "share/UiCanResizeWidget.h"

#include "share/UiRect9GridWidget.h"

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtGui/QBoxLayout>
#include <QtCore/QDebug>

static const bool DEV_VALUE_IN_THIS_FILE_PRINT_LOG = false;

CUiCanResizeWindow::CUiCanResizeWindow( QWidget* parent /*= 0*/ )
 : QWidget(parent)
{
	m_bMousePressed = false;
	m_bCanResize = true;
	m_posTypeMousePress = CUiCommon::SplitRectType_NULL;
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
void CUiCanResizeWindow::_SetAttribute()
{
	//
	//enable MainWindow to be transparent
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking 鼠标跟踪
	this->setMouseTracking(true);
	// 不继承父组件的背景色
	//setAutoFillBackground(true);
}


void CUiCanResizeWindow::mousePressEvent( QMouseEvent *event )
{
	//QPoint posPressInWidget = event->pos();
	QPoint posPressInWidget;
	m_bMousePressed = true;
	m_rcOldGeometry = geometry();
	m_ptGlobalMousePress = event->globalPos();
	posPressInWidget = mapFromGlobal(event->globalPos());
	m_posTypeMousePress = _PosType(posPressInWidget);

	if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
	{
		qDebug()<<"mousePressEvent"
			<<" "<<"m_rcOldGeometry.topLeft().x="<<m_rcOldGeometry.topLeft().x()
			<<" "<<"m_rcOldGeometry.topLeft().y="<<m_rcOldGeometry.topLeft().y()
			<<" "<<"m_rcOldGeometry.bottomRight().x="<<m_rcOldGeometry.bottomRight().x()
			<<" "<<"m_rcOldGeometry.bottomRight().y="<<m_rcOldGeometry.bottomRight().y();
		qDebug()<<"mousePressEvent"
			<<" "<<"m_ptGlobalMousePress.x="<<m_ptGlobalMousePress.x()
			<<" "<<"m_ptGlobalMousePress.y="<<m_ptGlobalMousePress.y();
		qDebug()<<"mousePressEvent"
			<<" "<<"posPressInWidget.x="<<posPressInWidget.x()
			<<" "<<"posPressInWidget.y="<<posPressInWidget.y()
			<<" "<<"m_posTypeMousePress="<<CUiCommon::getString(m_posTypeMousePress);
	}

	//
	QWidget::mousePressEvent(event);
}
//mousePress
void CUiCanResizeWindow::mouseMoveEvent( QMouseEvent *event )
{
	if (false == m_bCanResize)
	{
		return;
	}

	//
	if (m_bMousePressed)
	{	
		QPoint ptGlobalCurrent;
		QPoint ptGlobalMouseMoved;
		QRect rcNewGeometry = m_rcOldGeometry;

		ptGlobalCurrent = event->globalPos();
		ptGlobalMouseMoved = ptGlobalCurrent - m_ptGlobalMousePress;
		rcNewGeometry = _GetNewGeometry(m_rcOldGeometry, m_posTypeMousePress, ptGlobalMouseMoved);
		this->setGeometry(rcNewGeometry);
		if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
		{
			qDebug()<<"mouseMoveEvent"
				<<" "<<"ptGlobalCurrent.x="<<ptGlobalCurrent.x()
				<<" "<<"ptGlobalCurrent.y="<<ptGlobalCurrent.y();
			qDebug()<<"mouseMoveEvent"
				<<" "<<"ptGlobalMouseMoved.x="<<ptGlobalMouseMoved.x()
				<<" "<<"ptGlobalMouseMoved.y="<<ptGlobalMouseMoved.y();
			qDebug()<<"mousePressEvent"
				<<" "<<"rcNewGeometry.topLeft().x="<<rcNewGeometry.topLeft().x()
				<<" "<<"rcNewGeometry.topLeft().y="<<rcNewGeometry.topLeft().y()
				<<" "<<"rcNewGeometry.bottomRight().x="<<rcNewGeometry.bottomRight().x()
				<<" "<<"rcNewGeometry.bottomRight().y="<<rcNewGeometry.bottomRight().y();

		}//if (0)
	}
}

void CUiCanResizeWindow::mouseReleaseEvent( QMouseEvent *event )
{
	m_bMousePressed = false;
	//
	QWidget::mouseReleaseEvent(event);
}
QRect CUiCanResizeWindow::_GetNewGeometry(
	QRect rcOldGeometry, 
	CUiCommon::ESplitRectType posTypeMousePress,
	QPoint ptMouseMoved)
{
	QRect rcNewGeometry;
	int offsetX = ptMouseMoved.x();
	int offsetY = ptMouseMoved.y();

	rcNewGeometry = rcOldGeometry;
	switch (posTypeMousePress)
	{
	case CUiCommon::SplitRectType_TopLeft:
		rcNewGeometry.adjust(offsetX, offsetY, 0, 0);
		break;
	case CUiCommon::SplitRectType_Top:
		rcNewGeometry.adjust(0, offsetY, 0, 0);
		break;
	case CUiCommon::SplitRectType_TopRight:
		rcNewGeometry.adjust(0, offsetY, offsetX, 0);
		break;
	case CUiCommon::SplitRectType_Left:
		rcNewGeometry.adjust(offsetX, 0, 0, 0);
		break;
	case CUiCommon::SplitRectType_Client:
		break;
	case CUiCommon::SplitRectType_Right:
		rcNewGeometry.adjust(0, 0, offsetX, 0);
		break;
	case CUiCommon::SplitRectType_BottomLeft:
		rcNewGeometry.adjust(offsetX, 0, 0, offsetY);
		break;
	case CUiCommon::SplitRectType_Bottom:
		rcNewGeometry.adjust(0, 0, 0, offsetY);
		break;
	case CUiCommon::SplitRectType_BottomRight:
		rcNewGeometry.adjust(0, 0, offsetX, offsetY);
		break;
	default:
		break;
	}//switch

	return rcNewGeometry;
}
void CUiCanResizeWindow::setCanResize( bool bValue )
{
	m_bCanResize = bValue; 
}

bool CUiCanResizeWindow::canResize() const
{
	return m_bCanResize;
}
//posCurrent_InWidget
CUiCommon::ESplitRectType CUiCanResizeWindow::_PosType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType  nType = CUiCommon::SplitRectType_NULL;

	if (NULL != m_pUiImageBorderWidget)
	{
		nType = m_pUiImageBorderWidget->posType(posValue);
	}
	
	return nType;
}

