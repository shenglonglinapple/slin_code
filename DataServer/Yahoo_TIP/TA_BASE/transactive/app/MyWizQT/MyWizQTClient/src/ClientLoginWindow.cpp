#include "ClientLoginWindow.h"


#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"

#include "share/UiRect9GridWidget.h"
#include "share/UiCanResizeMoveWidget.h"
#include "share/UiIconLineEditContainer.h"
#include "share/UiImageButton.h"

#include "UiTitleWidget.h"

//
static const char*  DEF_VALUE_Resources_skins_Theme_loginTopLineEditor_png = "loginTopLineEditor.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginIconPerson_png = "loginIconPerson.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginLineEditorDownArrow_png = "loginLineEditorDownArrow.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginBottomLineEditor_png = "loginBottomLineEditor.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginIconKey_png = "loginIconKey.png";
//
static const char*  DEF_VALUE_Resources_skins_Theme_loginOKButton_active_png = "loginOKButton_active.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginOKButton_hover_png = "loginOKButton_hover.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginOKButton_down_png = "loginOKButton_down.png";
static const char*  DEF_VALUE_Resources_skins_Theme_loginOKButton_normal_png = "loginOKButton_normal.png";
//
static const char*  DEF_VALUE_Resources_skins_Theme_loginSeparator_png = "loginSeparator.png";



//////////////////
CClientLoginWindow::CClientLoginWindow( QWidget* parent /*= 0*/ )
: IUiCanResizeMoveWidget(parent)
{	
	//Ui level 0, nothing
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	this->setContentsMargins(0, 0, 0, 0);

	m_pUiMouseEventWidget = NULL;
	m_pUiImageBorderWidget = NULL;
	m_pUiTitleWidget = NULL;
	m_wgt_usercontainer = NULL;
	//Ui level 1
	m_pUiImageBorderWidget = new CUiRect9GirdWidget(this);

	m_pUiMouseEventWidget = new CUiMouseEventWidget(this, m_pUiImageBorderWidget);
	m_pUiMouseEventWidget->setContentsMargins(0, 0, 0, 0);
	m_pUiMouseEventWidget->setAutoFillBackground(true);// 不继承父组件的背景色 must set
	m_pUiMouseEventWidget->setClientAreaCursorShape(Qt::ArrowCursor);
	m_pUiTitleWidget = new CUiTitleWidget(this, m_pUiMouseEventWidget);
	m_pUiTitleWidget->setTitle("LoginWindow");

	QString strThemeName;
	QString strLoginTopLineEditor;
	QString strIconPerson;
	QString strLoginLineEditorDownArrow;
	QString strLoginBottomLineEditor;
	QString strIconKey;

	strThemeName = CUiStyleManager::getInstance().getThemeName();
	strLoginTopLineEditor = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginTopLineEditor_png);
	strIconPerson = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginIconPerson_png);
	strLoginLineEditorDownArrow = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginLineEditorDownArrow_png);
	m_lineEditUserNameRef = NULL;
	m_wgt_usercontainer = new CUiIconLineEditContainer(m_pUiMouseEventWidget);
	m_wgt_usercontainer->setBackgroundImage(strLoginTopLineEditor, QPoint(8, 8));
	m_wgt_usercontainer->setLeftIcon(strIconPerson);
	m_wgt_usercontainer->setRightIcon(strLoginLineEditorDownArrow);
	m_lineEditUserNameRef = m_wgt_usercontainer->edit();
	m_lineEditUserNameRef->setPlaceholderText("shenglonglin1986@gmail.com");//设置占位符文本
	QObject::connect(m_lineEditUserNameRef, SIGNAL(textChanged(QString)), SLOT(onLoginInputChanged()));
	QObject::connect(m_lineEditUserNameRef, SIGNAL(textEdited(QString)), SLOT(onUserNameEdited(QString)));

	strLoginBottomLineEditor = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginBottomLineEditor_png);
	strIconKey = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginIconKey_png);
	m_lineEditPasswordRef = NULL;
	m_wgt_passwordcontainer = new CUiIconLineEditContainer(m_pUiMouseEventWidget);
	m_wgt_passwordcontainer->setBackgroundImage(strLoginBottomLineEditor, QPoint(8, 8));
	m_wgt_passwordcontainer->setLeftIcon(strIconKey);
	m_lineEditPasswordRef = m_wgt_passwordcontainer->edit();
	m_lineEditPasswordRef->setEchoMode(QLineEdit::Password);
	m_lineEditPasswordRef->setPlaceholderText(QObject::tr("Password"));//设置占位符文本
	QObject::connect(m_lineEditPasswordRef, SIGNAL(textChanged(QString)), SLOT(onLoginInputChanged()));

	m_cbx_remberPassword = new QCheckBox(m_pUiMouseEventWidget);
	m_cbx_remberPassword->setText("Remember password");
	m_cbx_remberPassword->setStyleSheet(QString("QCheckBox{background:none;border:none;}"
		"QCheckBox:focus{background:none;border:none;}"
		"QCheckBox::pressed{background:none;border:none;}"));
	m_cbx_remberPassword->setChecked(true);

	m_cbx_autologin = new QCheckBox(m_pUiMouseEventWidget);
	m_cbx_autologin->setText("Auto sign in");
	m_cbx_autologin->setStyleSheet(QString("QCheckBox{background:none;border:none;}"
		"QCheckBox:focus{background:none;border:none;}"
		"QCheckBox::pressed{background:none;border:none;}"));
	m_cbx_autologin->setChecked(true);

	QString strBtnNormal;
	QString strBtnHover;
	QString strBtnDown;
	QString strBtnDisable;
	strBtnNormal = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginOKButton_active_png);
	strBtnHover = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginOKButton_hover_png);
	strBtnDown = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginOKButton_down_png);
	strBtnDisable = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginOKButton_normal_png);
	m_buttonLogin = new CUiImageButton(m_pUiMouseEventWidget);
	m_buttonLogin->setButtonStyle(strBtnNormal, strBtnHover, strBtnDown, strBtnDisable, QColor("#ffffff"),
		QColor("#ffffff"), QColor("b1b1b1"));
	m_buttonLogin->setText(QObject::tr("Login"));
	m_buttonLogin->setEnabled(false);	
	QObject::connect(m_buttonLogin, SIGNAL(clicked()), SLOT(on_btn_login_clicked()));

	QString strSeparator;
	strSeparator = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_loginSeparator_png);
	m_label_separator2 = new QLabel(m_pUiMouseEventWidget);
	m_label_separator2->setStyleSheet(QString("QLabel {border: none;background-image: url(%1);"
		"background-position: center; background-repeat: no-repeat}").arg(strSeparator));

	m_label_noaccount = new QLabel(m_pUiMouseEventWidget);
	m_label_noaccount->setText(QObject::tr("No account yet,"));
	m_label_noaccount->setStyleSheet(QString("QLabel {border: none; color: #5f5f5f;}"));
	//
	m_btn_changeToSignin = new QPushButton(m_pUiMouseEventWidget);
	m_btn_changeToSignin->setText(QObject::tr("click to sign up"));
	m_btn_changeToSignin->setVisible(true);
	m_btn_changeToSignin->setStyleSheet(QString("QPushButton { border: 1px; background: none; "
		"color: #43a6e8;  padding-left: 10px; padding-bottom: 0px}"));
	connect(m_btn_changeToSignin, SIGNAL(clicked()), SLOT(on_btn_changeToSignin_clicked()));

	m_btn_changeToLogin = new QPushButton(m_pUiMouseEventWidget);
	m_btn_changeToLogin->setText(QObject::tr("click to login"));
	m_btn_changeToLogin->setVisible(false);
	m_btn_changeToLogin->setStyleSheet(QString("QPushButton { border: 1px; background: none; "
		"color: #43a6e8;  padding-left: 10px; padding-bottom: 0px}"));
	connect(m_btn_changeToLogin, SIGNAL(clicked()), SLOT(on_btn_changeToLogin_clicked()));

	//////////////////////////////////////////////////////////////////////////
	QHBoxLayout* pHBoxLayout_cbx_remberPassword_autologin = NULL;
	pHBoxLayout_cbx_remberPassword_autologin = new QHBoxLayout();
	pHBoxLayout_cbx_remberPassword_autologin->addWidget(m_cbx_remberPassword);
	pHBoxLayout_cbx_remberPassword_autologin->addWidget(m_cbx_autologin);


	QHBoxLayout* pHBoxLayout_noaccount_changeToSignin = NULL;
	pHBoxLayout_noaccount_changeToSignin = new QHBoxLayout();
	pHBoxLayout_noaccount_changeToSignin->addWidget(m_label_noaccount);
	pHBoxLayout_noaccount_changeToSignin->addWidget(m_btn_changeToSignin);
	pHBoxLayout_noaccount_changeToSignin->addWidget(m_btn_changeToLogin);

	QBoxLayout* pLayout_MouseEventWidget = NULL;
	pLayout_MouseEventWidget = new QBoxLayout(QBoxLayout::TopToBottom, m_pUiMouseEventWidget);
	pLayout_MouseEventWidget->setContentsMargins(0, 0, 0, 0);
	pLayout_MouseEventWidget->setSpacing(0);
	pLayout_MouseEventWidget->addWidget(m_pUiTitleWidget);
	pLayout_MouseEventWidget->addWidget(m_wgt_usercontainer);
	pLayout_MouseEventWidget->addWidget(m_wgt_passwordcontainer);
	pLayout_MouseEventWidget->addLayout(pHBoxLayout_cbx_remberPassword_autologin);
	pLayout_MouseEventWidget->addWidget(m_buttonLogin);
	pLayout_MouseEventWidget->addWidget(m_label_separator2);	
	pLayout_MouseEventWidget->addLayout(pHBoxLayout_noaccount_changeToSignin);
	m_pUiMouseEventWidget->setLayout(pLayout_MouseEventWidget);


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
CUiCommon::ESplitRectType CClientLoginWindow::posType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType  nType = CUiCommon::SplitRectType_NULL;

	if (NULL != m_pUiImageBorderWidget)
	{
		nType = m_pUiImageBorderWidget->posType(posValue);
	}

	return nType;
}

void CClientLoginWindow::setCanResize( bool bValue )
{
	m_pUiMouseEventWidget->setCanResize(bValue);
}

bool CClientLoginWindow::canResize() const
{
	return m_pUiMouseEventWidget->canResize();
}

void CClientLoginWindow::setCanMove( bool bValue )
{
	m_pUiMouseEventWidget->setCanMove(bValue);
}

bool CClientLoginWindow::canMove() const
{
	return m_pUiMouseEventWidget->canMove();
}

void CClientLoginWindow::onLoginInputChanged()
{
	bool bInputFinished = false;
	if (false == m_lineEditUserNameRef->text().isEmpty() && false == m_lineEditPasswordRef->text().isEmpty())
	{
		bInputFinished =  true;
	}
	m_buttonLogin->setEnabled(bInputFinished);
}

void CClientLoginWindow::onUserNameEdited(const QString& arg1)
{
	//Q_UNUSED(arg1);
	m_lineEditPasswordRef->setText("");
}

void CClientLoginWindow::on_btn_login_clicked()
{
	enableLoginControls(false);
	
	if (1)
	{
		m_buttonLogin->setEnabled(true);
	}
}

void CClientLoginWindow::enableLoginControls(bool bEnable)
{
	m_lineEditUserNameRef->setEnabled(bEnable);
	m_lineEditPasswordRef->setEnabled(bEnable);
	m_cbx_autologin->setEnabled(bEnable);
	m_cbx_remberPassword->setEnabled(bEnable);
	m_buttonLogin->setEnabled(bEnable);
}

void CClientLoginWindow::on_btn_changeToSignin_clicked()
{
	m_btn_changeToSignin->setVisible(false);
	m_btn_changeToLogin->setVisible(true);
	m_label_noaccount->setText(tr("Already got account,"));

	m_cbx_remberPassword->setVisible(false);
	m_cbx_autologin->setVisible(false);
	m_buttonLogin->setVisible(false);
}

void CClientLoginWindow::on_btn_changeToLogin_clicked()
{
	m_btn_changeToLogin->setVisible(false);
	m_btn_changeToSignin->setVisible(true);
	m_label_noaccount->setText(tr("No account yet,"));
}

