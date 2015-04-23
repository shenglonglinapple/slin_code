#include "share/UiCanResizeMoveWidget.h"

#include "share/UiImageBorderWidget.h"

#include <QtCore/QPoint>
#include <QtGui/QMouseEvent>
#include <QtGui/QBoxLayout>
#include <QtCore/QDebug>

static const bool DEV_VALUE_IN_THIS_FILE_PRINT_LOG = true;




//////////////////////////////////////////////////////////////////////////
CUiMouseEventWidget::CUiMouseEventWidget( IUiCanResizeMoveWidget* pAffectedWidget, QWidget* parent /*= 0*/ )
: QWidget(parent)
{
	m_pAffectedWidget = pAffectedWidget;

	m_bMousePressed = false;
	m_bCanResize = true;
	m_bCanMove = true;
	m_posTypeMousePress_Parent = CUiCommon::SplitRectType_NULL;
	m_nClientAreaCursorShape = Qt::OpenHandCursor;

	//	
	//半透明的背景
	//this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	//this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking 鼠标跟踪
	this->setMouseTracking(true);
	// 不继承父组件的背景色
	setAutoFillBackground(true);

}



void CUiMouseEventWidget::mousePressEvent( QMouseEvent *event )
{
	QPoint posPressInCurrentWidget = event->pos();
	QPoint posPressInParentWidget = this->mapTo(m_pAffectedWidget, event->pos());
	Qt::CursorShape nCursorShapeCurrent = this->cursor().shape();
	m_bMousePressed = true;
	m_rcOldGeometry_Parent = m_pAffectedWidget->geometry();
	m_ptGlobalMousePress = event->globalPos();
	m_posTypeMousePress_Parent = m_pAffectedWidget->posType(posPressInParentWidget);
	//m_ptGlobalOldTopLeft_Parent = mapToGlobal(m_pOwnerWidget->rect().topLeft());	
	m_ptGlobalOldTopLeft_Parent = m_rcOldGeometry_Parent.topLeft();

	if (Qt::OpenHandCursor == nCursorShapeCurrent)
	{
		this->setCursor(QCursor(Qt::ClosedHandCursor));
	}

	if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
	{
		qDebug()<<"mousePressEvent"
			<<" "<<"m_rcOldGeometry_Parent.topLeft().x="<<m_rcOldGeometry_Parent.topLeft().x()
			<<" "<<"m_rcOldGeometry_Parent.topLeft().y="<<m_rcOldGeometry_Parent.topLeft().y()
			<<" "<<"m_rcOldGeometry_Parent.bottomRight().x="<<m_rcOldGeometry_Parent.bottomRight().x()
			<<" "<<"m_rcOldGeometry_Parent.bottomRight().y="<<m_rcOldGeometry_Parent.bottomRight().y();
		qDebug()<<"mousePressEvent"
			<<" "<<"m_ptGlobalMousePress.x="<<m_ptGlobalMousePress.x()
			<<" "<<"m_ptGlobalMousePress.y="<<m_ptGlobalMousePress.y();
		qDebug()<<"mousePressEvent"
			<<" "<<"posPressInParentWidget.x="<<posPressInParentWidget.x()
			<<" "<<"posPressInParentWidget.y="<<posPressInParentWidget.y()
			<<" "<<"m_posTypeMousePress_Parent="<<CUiCommon::getString(m_posTypeMousePress_Parent);
	}

	//	
	QWidget::mousePressEvent(event);
}
void CUiMouseEventWidget::mouseMoveEvent( QMouseEvent *event )
{
	QPoint ptGlobalCurrent;
	QPoint ptGlobalMouseMoved;
	QPoint ptGlobalNewTopLeft_Parent;
	QRect rcNewGeometry_Parent = m_rcOldGeometry_Parent;
	//
	QPoint posMoveInParentWidget;
	CUiCommon::ESplitRectType posTypeMouseMove_Parent;
	Qt::CursorShape nCursorShapeMove;

	if (m_bMousePressed && (m_bCanMove || m_bCanResize))
	{
		ptGlobalCurrent = event->globalPos();
		ptGlobalMouseMoved = ptGlobalCurrent - m_ptGlobalMousePress;
		//
		ptGlobalNewTopLeft_Parent = m_ptGlobalOldTopLeft_Parent + ptGlobalMouseMoved;
		//
		rcNewGeometry_Parent = _GetNewGeometry(m_rcOldGeometry_Parent, m_posTypeMousePress_Parent, ptGlobalMouseMoved);
	}//	if (m_bMousePressed && (m_bCanMove || m_bCanResize))


	if (m_bMousePressed && m_bCanMove && CUiCommon::SplitRectType_Client == m_posTypeMousePress_Parent)
	{
		m_pAffectedWidget->move(ptGlobalNewTopLeft_Parent);
	}

	//
	if (m_bMousePressed && m_bCanResize&& CUiCommon::SplitRectType_Client != m_posTypeMousePress_Parent)
	{	
		m_pAffectedWidget->setGeometry(rcNewGeometry_Parent);		
	}

	if (false == m_bMousePressed)
	{
		posMoveInParentWidget = this->mapTo(m_pAffectedWidget, event->pos());
		posTypeMouseMove_Parent = m_pAffectedWidget->posType(posMoveInParentWidget);
		nCursorShapeMove = _GetNewCursorShape(posTypeMouseMove_Parent);
		//m_pOwnerWidget->setCursor(QCursor(nCursorShapeMove));
		this->setCursor(QCursor(nCursorShapeMove));
	}

	if (DEV_VALUE_IN_THIS_FILE_PRINT_LOG)
	{
		qDebug()<<"mouseMoveEvent"
			<<" "<<"ptGlobalCurrent.x="<<ptGlobalCurrent.x()
			<<" "<<"ptGlobalCurrent.y="<<ptGlobalCurrent.y();
		qDebug()<<"mouseMoveEvent"
			<<" "<<"ptGlobalMouseMoved.x="<<ptGlobalMouseMoved.x()
			<<" "<<"ptGlobalMouseMoved.y="<<ptGlobalMouseMoved.y();
		qDebug()<<"mouseMoveEvent"
			<<" "<<"ptGlobalNewTopLeft_Parent.x="<<ptGlobalNewTopLeft_Parent.x()
			<<" "<<"ptGlobalNewTopLeft_Parent.y="<<ptGlobalNewTopLeft_Parent.y();
		qDebug()<<"mousePressEvent"
			<<" "<<"rcNewGeometry_Parent.topLeft().x="<<rcNewGeometry_Parent.topLeft().x()
			<<" "<<"rcNewGeometry_Parent.topLeft().y="<<rcNewGeometry_Parent.topLeft().y()
			<<" "<<"rcNewGeometry_Parent.bottomRight().x="<<rcNewGeometry_Parent.bottomRight().x()
			<<" "<<"rcNewGeometry_Parent.bottomRight().y="<<rcNewGeometry_Parent.bottomRight().y();

	}//if (0)
	//QWidget::mouseMoveEvent(event);
}
void CUiMouseEventWidget::mouseReleaseEvent( QMouseEvent *event )
{
	Qt::CursorShape nCursorShapeCurrent = this->cursor().shape();

	if (Qt::ClosedHandCursor == nCursorShapeCurrent)
	{
		this->setCursor(QCursor(Qt::OpenHandCursor));
	}

	m_bMousePressed = false;

	//
	QWidget::mouseReleaseEvent(event);
}

void CUiMouseEventWidget::setCanResize( bool bValue )
{
	m_bCanResize = bValue; 
}

bool CUiMouseEventWidget::canResize() const
{
	return m_bCanResize;
}

void CUiMouseEventWidget::setCanMove( bool bValue )
{
	m_bCanMove = bValue;
}

bool CUiMouseEventWidget::canMove() const
{
	return m_bCanMove;
}

Qt::CursorShape CUiMouseEventWidget::_GetNewCursorShape(CUiCommon::ESplitRectType posTypeMouseMove)
{
	Qt::CursorShape nCursorShape = Qt::ArrowCursor;

	switch (posTypeMouseMove)
	{
	case CUiCommon::SplitRectType_TopLeft:
		nCursorShape = Qt::SizeFDiagCursor;
		break;
	case CUiCommon::SplitRectType_Top:
		nCursorShape = Qt::SizeVerCursor;
		break;
	case CUiCommon::SplitRectType_TopRight:
		nCursorShape = Qt::SizeBDiagCursor;
		break;
	case CUiCommon::SplitRectType_Left:
		nCursorShape = Qt::SizeHorCursor;
		break;
	case CUiCommon::SplitRectType_Client:
		nCursorShape = m_nClientAreaCursorShape;
		//nCursorShape = Qt::OpenHandCursor;//Qt::ClosedHandCursor
		break;
	case CUiCommon::SplitRectType_Right:
		nCursorShape = Qt::SizeHorCursor;
		break;
	case CUiCommon::SplitRectType_BottomLeft:
		nCursorShape = Qt::SizeBDiagCursor;
		break;
	case CUiCommon::SplitRectType_Bottom:
		nCursorShape = Qt::SizeVerCursor;
		break;
	case CUiCommon::SplitRectType_BottomRight:
		nCursorShape = Qt::SizeFDiagCursor;
		break;
	default:
		break;
	}//switch

	return nCursorShape;
}


QRect CUiMouseEventWidget::_GetNewGeometry(
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

void CUiMouseEventWidget::setClientAreaCursorShape( Qt::CursorShape nCursorShape )
{
	m_nClientAreaCursorShape = nCursorShape;
}

//////////////////////////////////////////////////////////////////////////

CUiCanResizeMoveWidget::CUiCanResizeMoveWidget( QWidget* parent /*= 0*/ )
:IUiCanResizeMoveWidget(parent)
{	
	//Ui level 0, nothing
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);
	//Ui level 1
	m_pUiImageBorderWidget = new CUiImageBorderWidget(this);

	m_pUiMouseEventWidget = new CUiMouseEventWidget(this, m_pUiImageBorderWidget);
	m_pUiMouseEventWidget->setContentsMargins(0, 0, 0, 0);
	m_pUiMouseEventWidget->setAutoFillBackground(true);// 不继承父组件的背景色 must set

	
	//用一个QBoxLayout来设置m_pUiWallWidget的大小和m_pUiRect9GirdWidget一样大
	QBoxLayout* pBoxLayout = NULL;
	pBoxLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	pBoxLayout->setContentsMargins(0, 0, 0, 0);
	pBoxLayout->setSpacing(0);
	pBoxLayout->addWidget(m_pUiMouseEventWidget);//m_pUiWallWidget's rect = m_pUiRect9GirdWidget's rect
	m_pUiImageBorderWidget->setLayout(pBoxLayout);

	//用一个QBoxLayout来设置m_pShadowWidget的大小和CUiShadowWindow一样大
 	QBoxLayout* windowLayout = NULL;
 	windowLayout = new QBoxLayout(QBoxLayout::TopToBottom);
 	windowLayout->setContentsMargins(0, 0, 0, 0);
 	windowLayout->setSpacing(0);
 	windowLayout->addWidget(m_pUiImageBorderWidget);//m_pShadowWidget's rect = CUiShadowWindow's rect
	//
	this->setLayout(windowLayout);
}


//posCurrent_InWidget
CUiCommon::ESplitRectType CUiCanResizeMoveWidget::posType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType  nType = CUiCommon::SplitRectType_NULL;

	if (NULL != m_pUiImageBorderWidget)
	{
		nType = m_pUiImageBorderWidget->posType(posValue);
	}
	
	return nType;
}



