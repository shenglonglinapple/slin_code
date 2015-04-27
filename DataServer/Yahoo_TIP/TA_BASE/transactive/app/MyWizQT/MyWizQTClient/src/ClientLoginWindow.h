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
class QCheckBox;
QT_END_NAMESPACE


class CUiMouseEventWidget;
class CUiRect9GirdWidget;
class CUiTitleWidget;
class CUiIconLineEditContainer;
class CUiImageButton;

class CClientLoginWindow : public IUiCanResizeMoveWidget
{
	Q_OBJECT;
public:
	explicit CClientLoginWindow(QWidget* parent = 0);
public:
	CUiCommon::ESplitRectType posType( const QPoint& posValue );//IUiCanResizeMoveWidget
private slots:
	void onLoginInputChanged();
	void onUserNameEdited(const QString& arg1);
	void on_btn_login_clicked();
	void on_btn_changeToSignin_clicked();
	void on_btn_changeToLogin_clicked();

private:
	void enableLoginControls(bool bEnable);

public:
	void setCanResize( bool bValue );
	bool canResize() const;
public:
	void setCanMove( bool bValue );
	bool canMove() const;
private:
	CUiMouseEventWidget* m_pUiMouseEventWidget;
	CUiRect9GirdWidget* m_pUiImageBorderWidget;
private:
	CUiTitleWidget* m_pUiTitleWidget;
	CUiIconLineEditContainer* m_wgt_usercontainer;
	QLineEdit* m_lineEditUserNameRef;//m_wgt_usercontainer
	CUiIconLineEditContainer* m_wgt_passwordcontainer;
	QLineEdit* m_lineEditPasswordRef;//m_wgt_passwordcontainer
	QCheckBox* m_cbx_remberPassword;
	QCheckBox* m_cbx_autologin;
	CUiImageButton* m_buttonLogin;
	QLabel* m_label_separator2;
	QLabel* m_label_noaccount;
	QPushButton* m_btn_changeToSignin;
	QPushButton* m_btn_changeToLogin;
};


#endif // __CLASS__CLIENT_LOGIN_WINDOW_H__
