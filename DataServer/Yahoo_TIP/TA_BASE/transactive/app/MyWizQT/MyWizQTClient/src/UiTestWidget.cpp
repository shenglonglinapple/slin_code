#include "UiTestWidget.h"
CUiTestWidget::CUiTestWidget( QWidget* parent/*=0*/ )
{
	//setMouseTracking 鼠标跟踪
	//If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
	//If mouse tracking is switched off, mouse move events only occur if a mouse button is pressed 
	this->setMouseTracking(true);
}

void CUiTestWidget::_SetAttribute()
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
	Qt的默认风格下，子窗体部件的margin()的值是9英寸，窗体的margin()值是11英寸
	*/
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking 鼠标跟踪
	//If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
	this->setMouseTracking(true);
	//this->setMouseTracking(false);

	// 不继承父组件的背景色
	//can't set setAutoFillBackground=true, 不然矩形四边都是黑的
	//setAutoFillBackground(true);
}


void CUiTestWidget::mousePressEvent( QMouseEvent *event )
{
	QWidget::mousePressEvent(event);
}
//If mouse tracking is switched off, mouse move events only occur if a mouse button is pressed 
//鼠标在对话框上移动，但是没有调用mouseMoveEvent，要按下左键移动才行
void CUiTestWidget::mouseMoveEvent( QMouseEvent *event )
{
	int a = 0;
}


void CUiTestWidget::mouseReleaseEvent( QMouseEvent *event )
{
	//
	QWidget::mouseReleaseEvent(event);
}
