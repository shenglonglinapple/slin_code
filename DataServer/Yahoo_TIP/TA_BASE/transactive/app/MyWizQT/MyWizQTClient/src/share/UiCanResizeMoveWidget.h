#ifndef __CLASS_UI_CNA_RESIZE_MOVE_WIDGET_H__
#define __CLASS_UI_CNA_RESIZE_MOVE_WIDGET_H__

#include "share/UiCommon.h"
#include <QtGui/QDialog>

class IUiCanResizeMoveWidget : public QWidget
{
	Q_OBJECT;
public:
	IUiCanResizeMoveWidget(QWidget* parent = 0):QWidget(parent)
	{

	}
	virtual ~IUiCanResizeMoveWidget()
	{

	}
public:
	virtual CUiCommon::ESplitRectType posType( const QPoint& posValue ) = 0;
};//class IUiCanResizeMoveWidget

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CUiMouseEventWidget : public QWidget
{
	Q_OBJECT;
public:
	explicit CUiMouseEventWidget(IUiCanResizeMoveWidget* pAffectedWidget, QWidget* parent = 0);
protected:
	virtual void mousePressEvent(QMouseEvent *event);
	virtual void mouseMoveEvent(QMouseEvent *event);
	virtual void mouseReleaseEvent(QMouseEvent *event);
public:
	void setCanResize( bool bValue );
	bool canResize() const;
public:
	void setCanMove( bool bValue );
	bool canMove() const;
public:
	void setClientAreaCursorShape(Qt::CursorShape nCursorShape);
private:
	QRect _GetNewGeometry( QRect rcOldGeometry, CUiCommon::ESplitRectType posTypeMousePress, QPoint ptMouseMoved);
	Qt::CursorShape _GetNewCursorShape(CUiCommon::ESplitRectType posTypeMouseMove);
private:
	IUiCanResizeMoveWidget* m_pAffectedWidget;
private:
	bool m_bMousePressed;
	bool m_bCanResize;
	CUiCommon::ESplitRectType m_posTypeMousePress_Parent;
	QPoint m_ptGlobalMousePress;
	QRect m_rcOldGeometry_Parent;
private:
	bool m_bCanMove;
	QPoint m_ptGlobalOldTopLeft_Parent;
	Qt::CursorShape m_nClientAreaCursorShape;
};//class CUiWallWidget 


//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CUiRect9GirdWidget;
class CUiCanResizeMoveWidget : public IUiCanResizeMoveWidget
{
	Q_OBJECT;
public:
   explicit CUiCanResizeMoveWidget(QWidget* parent = 0);
public:
	CUiCommon::ESplitRectType posType( const QPoint& posValue );
private:
	CUiMouseEventWidget* m_pUiMouseEventWidget;
	CUiRect9GirdWidget* m_pUiImageBorderWidget;
};

#endif // __CLASS_UI_CNA_RESIZE_MOVE_WIDGET_H__
