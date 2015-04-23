#ifndef __CLASS_UI_TEST_WIDGET_H__
#define __CLASS_UI_TEST_WIDGET_H__

#include <QtGui/QWidget>
#include <QtGui/QDialog>

class CUiTestWidget : public QDialog
{
	Q_OBJECT;
public:
    CUiTestWidget(QWidget* parent=0);
protected:
	//鼠标在对话框上移动，但是没有调用mouseMoveEvent，要按下左键移动才行
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
private:
	void _SetAttribute();
};

#endif // __CLASS_UI_TEST_WIDGET_H__
