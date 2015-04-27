#include "UiTitleWidget.h"


#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"


static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowclose_png = "linuxwindowclose.png";//\share\skins\default\linuxwindowclose.png
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowclose_on_png = "linuxwindowclose_on.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowclose_selected_png = "linuxwindowclose_selected.png";
//
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmin_png = "linuxwindowmin.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmin_on_png = "linuxwindowmin_on.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmin_selected_png = "linuxwindowmin_selected.png";
//
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmax_png = "linuxwindowmax.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmax_on_png = "linuxwindowmax_on.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowmax_selected_png = "linuxwindowmax_selected.png";
//
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_png = "linuxwindowrestore.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_on_png = "linuxwindowrestore_on.png";
static const char*  DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_selected_png = "linuxwindowrestore_selected.png";
//




CUiTitleWidget::CUiTitleWidget( QWidget* pAffectedWidget, QWidget* parent /*= 0*/ )
 : QWidget(parent)
{
	m_pAffectedWidget = pAffectedWidget;

	m_titleLabel = new QLabel(this);
	m_minsize = new QToolButton(this);
	m_maxsize = new QToolButton(this);
	m_close = new QToolButton(this);
	m_strTitle = "Title";

	QHBoxLayout *pHBoxLayout = new QHBoxLayout(this);
	pHBoxLayout->addWidget(m_titleLabel);
	pHBoxLayout->addWidget(m_minsize);
	pHBoxLayout->addWidget(m_maxsize);
	pHBoxLayout->addWidget(m_close);
	pHBoxLayout->insertStretch(1, 500);//拉伸
	pHBoxLayout->setSpacing(0);
	this->setLayout(pHBoxLayout);

	_SetStyleSheet();
	_SetAttribute();

	connect(m_minsize, SIGNAL( clicked() ), this, SLOT(onMinSizeClicked() ) );
	connect(m_maxsize, SIGNAL( clicked() ), this, SLOT(onMaxSizeClicked() ) );
	connect(m_close, SIGNAL(clicked()), this, SLOT(onCloseClicked() ) );
}



void CUiTitleWidget::_SetAttribute()
{
	//
	//enable MainWindow to be transparent
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	/*
	空白（margin）和间距（spacing）
	*/
	this->setContentsMargins(0, 0, 0, 0);
	//setMouseTracking 鼠标跟踪
	//this->setMouseTracking(true);

	// 不继承父组件的背景色
	//setAutoFillBackground(true);

	//H Expanding, V Fixed
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

void CUiTitleWidget::_SetStyleSheet()
{
	// 设置按钮图像的样式
	QString strThemeName;
	QString strButtonClose;
	QString strButtonCloseOn;
	QString strButtonCloseSelected;

	QString strButtonMin;
	QString strButtonMinOn;
	QString strButtonMinSelected;

	QString strButtonMax;
	QString strButtonMaxOn;
	QString strButtonMaxSelected;

	QString strButtonRestore;
	QString strButtonRestoreOn;
	QString strButtonRestoreSelected;

	strThemeName = CUiStyleManager::getInstance().getThemeName();
	strButtonClose = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowclose_png);
	strButtonCloseOn = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowclose_on_png);
	strButtonCloseSelected = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowclose_selected_png);
	//
	strButtonMin = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmin_png);
	strButtonMinOn = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmin_on_png);
	strButtonMinSelected = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmin_selected_png);
	//
	strButtonMax = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmax_png);
	strButtonMaxOn = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmax_on_png);
	strButtonMaxSelected = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowmax_selected_png);
	//
	strButtonRestore = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_png);
	strButtonRestoreOn = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_on_png);
	strButtonRestoreSelected = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_linuxwindowrestore_selected_png);

	//
	m_close->setStyleSheet(QString("QToolButton{ border-image:url(%1);background:none;}"
		"QToolButton:hover{border-image:url(%2); background:none;}"
		"QToolButton::pressed{border-image:url(%3); background:none;}")
		.arg(strButtonClose).arg(strButtonCloseOn).arg(strButtonCloseSelected));

	m_minsize->setStyleSheet(QString("QToolButton{ border-image:url(%1); background:none;}"
		"QToolButton:hover{border-image:url(%2); background:none;}"
		"QToolButton::pressed{border-image:url(%3); background:none;}")
		.arg(strButtonMin).arg(strButtonMinOn).arg(strButtonMinSelected));

	m_maxSheet = QString("QToolButton{ border-image:url(%1); background:none;}"
		"QToolButton:hover{border-image:url(%2); background:none;}"
		"QToolButton::pressed{border-image:url(%3); background:none;}")
		.arg(strButtonMax).arg(strButtonMaxOn).arg(strButtonMaxSelected);
	m_maxsize->setStyleSheet(m_maxSheet);

	m_restoreStyleSheet = QString("QToolButton{ border-image:url(%1); background:none;}"
		"QToolButton:hover{border-image:url(%2); background:none;}"
		"QToolButton::pressed{border-image:url(%3); background:none;}")
		.arg(strButtonRestore).arg(strButtonRestoreOn).arg(strButtonRestoreSelected);

	int nWidth = 20;
	int nHight = 18;
	m_close->setFixedSize(nWidth, nHight);//(16, 16);
	m_minsize->setFixedSize(nWidth, nHight);//(16, 16);
	m_maxsize->setFixedSize(nWidth, nHight);//(16, 16);

	m_titleLabel->setText(m_strTitle);
}

void CUiTitleWidget::setCanResize( bool bValue )
{
	m_maxsize->setEnabled(bValue);
	m_minsize->setEnabled(bValue);
}

void CUiTitleWidget::onCloseClicked()
{
	m_pAffectedWidget->close();
}

void CUiTitleWidget::onMinSizeClicked()
{
	m_pAffectedWidget->showMinimized();
}

void CUiTitleWidget::onMaxSizeClicked()
{
	if (Qt::WindowMaximized == m_pAffectedWidget->windowState())
	{
		m_maxsize->setStyleSheet(m_maxSheet);
		m_pAffectedWidget->showNormal();
	}
	else
	{
		m_maxsize->setStyleSheet(m_restoreStyleSheet);
		m_pAffectedWidget->showMaximized();
	}
	
}

void CUiTitleWidget::setTitle( const QString& strValue )
{
	m_strTitle = strValue;
	m_titleLabel->setText(m_strTitle);
}

