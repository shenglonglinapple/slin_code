#ifndef __CLASS_UI_CNARESIZE_WIDGET_H__
#define __CLASS_UI_CNARESIZE_WIDGET_H__

#include "share/UiCommon.h"
#include <QtGui/QDialog>

class CUiRect9GirdWidget;

class CUiCanResizeWindow : public QWidget
{
	Q_OBJECT;
public:
   explicit CUiCanResizeWindow(QWidget* parent = 0);
protected:
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
private:
	void _SetAttribute();
public:
	void setCanResize( bool bValue );
	bool canResize() const;
private:
	CUiCommon::ESplitRectType _PosType( const QPoint& posValue );
	QRect _GetNewGeometry( QRect rcOldGeometry, CUiCommon::ESplitRectType posTypeMousePress, QPoint ptMouseMoved);
protected:
	bool m_bMousePressed;
	bool m_bCanResize;
	CUiRect9GirdWidget* m_pUiImageBorderWidget;
	CUiCommon::ESplitRectType m_posTypeMousePress;
	QPoint m_ptGlobalMousePress;
	QRect m_rcOldGeometry;
};

#endif // __CLASS_UI_CNARESIZE_WIDGET_H__
