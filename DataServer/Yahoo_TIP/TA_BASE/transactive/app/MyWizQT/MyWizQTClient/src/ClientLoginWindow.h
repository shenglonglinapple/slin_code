#ifndef __CLASS__CLIENT_LOGIN_WINDOW_H__
#define __CLASS__CLIENT_LOGIN_WINDOW_H__

#include "share/UiCommon.h"
#include <QtGui/QWidget>

#include "share/UiCanResizeMoveWidget.h"


QT_BEGIN_NAMESPACE
class QToolButton;
class QHBoxLayout;
class QVBoxLayout;
class QLabel;
class QComboBox;
class QLineEdit;
class QPushButton;
class QToolButton;
class QPoint;
class QRect;
QT_END_NAMESPACE


class CUiMouseEventWidget;
class CUiImageBorderWidget;
class CUiTitleWidget;

class CClientLoginWindow : public IUiCanResizeMoveWidget
{
	Q_OBJECT;
public:
	explicit CClientLoginWindow(QWidget* parent = 0);
public:
	CUiCommon::ESplitRectType posType( const QPoint& posValue );//IUiCanResizeMoveWidget
public:
	void setCanResize( bool bValue );
	bool canResize() const;
public:
	void setCanMove( bool bValue );
	bool canMove() const;
private:
	CUiMouseEventWidget* m_pUiMouseEventWidget;
	CUiImageBorderWidget* m_pUiImageBorderWidget;
private:
	CUiTitleWidget* m_pUiTitleWidget;

};


#endif // __CLASS__CLIENT_LOGIN_WINDOW_H__
