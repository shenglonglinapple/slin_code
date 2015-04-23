#include "share/UiRect9GridWidget.h"

#include <QtGui/QPainter>
//#include <QtGui/QPaintEngine>

#include "share/UiSkin9GridImage.h"
#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"

static const char*  DEF_VALUE_Resources_skins_Theme_ShadowPng = "shadow.png";
static const int  DEF_VALUE_Rect_Border_Hight = 20;//default 12;
static const int  DEF_VALUE_Rect_Border_Width = 20;//default 12;


static const int DEF_VALUE_Contents_Margins_left = 10;
static const int DEF_VALUE_Contents_Margins_top = 10;
static const int DEF_VALUE_Contents_Margins_right = 10;
static const int DEF_VALUE_Contents_Margins_bottom = 10;



CUiRect9GirdWidget::CUiRect9GirdWidget(QWidget* parent)
    : QWidget(parent)
    , m_pUiSkin9GridImage(new CUiSkin9GridImage())
{

	QString strThemeName;
	QString strShadowPngPath;

	strThemeName = CUiStyleManager::getInstance().getThemeName();
	//C:\LSL\SVNWork\slin_code\DataServer\Yahoo_TIP\TA_BASE\transactive\app\YahooFinanceStock\YahooFinanceStockClient\Resources\skins\default\shadow.png
	strShadowPngPath = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_ShadowPng);
    m_pUiSkin9GridImage->setImage(strShadowPngPath, QPoint(DEF_VALUE_Rect_Border_Width, DEF_VALUE_Rect_Border_Hight));

	//Ui level 0, nothing
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	//Widget内部的控件和Widget边框之间的 空白（margin）和间距（spacing）
	this->setContentsMargins(DEF_VALUE_Contents_Margins_left, DEF_VALUE_Contents_Margins_top, 
		DEF_VALUE_Contents_Margins_right, DEF_VALUE_Contents_Margins_bottom);//must set 

}

void CUiRect9GirdWidget::paintEvent(QPaintEvent *p)
{
	//class Q_GUI_EXPORT QWidget : public QObject, public QPaintDevice
    QPainter painter(this);
	QRect rectWidget = this->rect();

	//Ui level 1, rect grid
    m_pUiSkin9GridImage->drawBorder(&painter, rectWidget);
}



void CUiRect9GirdWidget::_SetAttribute()
{
	//
	//enable MainWindow to be transparent
	//半透明的背景
	//this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	//this->setWindowFlags(Qt::FramelessWindowHint);
	/*
	Widget内部的控件和Widget边框之间的 空白（margin）和间距（spacing）
	每种布局都有两个重要的属性，空白和间距。空白指的是整个布局四周距离窗体边缘的距离；间距指的是布局管理器内部各个窗口部件之间的距离。
	Qt的默认风格下，子窗体部件的margin()的值是9英寸，窗体的margin()值是11英寸
	*/
	//this->setContentsMargins(0, 0, 0, 0);

	//setMouseTracking 鼠标跟踪
	//If mouse tracking is enabled, the widget receives mouse move events even if no buttons are pressed.
	//this->setMouseTracking(true);

	// 不继承父组件的背景色
	//can't set setAutoFillBackground=true, 不然矩形四边都是黑的
	//setAutoFillBackground(true);
}

CUiCommon::ESplitRectType CUiRect9GirdWidget::posType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType nType = CUiCommon::SplitRectType_NULL;
	if (NULL != m_pUiSkin9GridImage)
	{
		nType = m_pUiSkin9GridImage->posType(posValue);
	}
	return nType;
}
