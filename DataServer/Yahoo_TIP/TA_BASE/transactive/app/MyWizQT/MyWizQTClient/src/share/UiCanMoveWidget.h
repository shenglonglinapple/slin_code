#ifndef __CLASS_UI_CNAMOVE_WIDGET_H__
#define __CLASS_UI_CNAMOVE_WIDGET_H__

#include <QtGui/QDialog>

class CUiImageBorderWidget;

class CUiCanMoveWindow : public QWidget
{
	Q_OBJECT;
public:
   explicit CUiCanMoveWindow(QWidget* parent = 0);
protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
private:
	void _SetAttribute();
public:
	void setCanMove( bool bValue );
	bool canMove() const;
protected:
	bool m_bMousePressed;
	bool m_bCanMove;
	CUiImageBorderWidget* m_pUiImageBorderWidget;
	QPoint m_ptGlobalOldTopLeft;
	QPoint m_ptGlobalMousePress;
};

#endif // __CLASS_UI_CNAMOVE_WIDGET_H__
