#include "share/UiImageBorderWidget.h"

//#include <QtGui/QPainter>
//#include <QtGui/QPaintEngine>
// #include <QtGui/QPainter>
// #include <QtGui/QWidget>
// #include <QtGui/QBoxLayout>
// #include <QtGui/QLabel>
// #include <QtGui/QLineEdit>
// #include <QtGui/QMouseEvent>
#include <QtGui/QtGui>

#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"

static const char*  DEF_VALUE_Resources_skins_Theme_ShadowPng = "shadow.png";
static const int  DEF_VALUE_Rect_Border_Hight = 20;//default 12;
static const int  DEF_VALUE_Rect_Border_Width = 20;//default 12;


static const int DEF_VALUE_Contents_Margins_left = 10;
static const int DEF_VALUE_Contents_Margins_top = 10;
static const int DEF_VALUE_Contents_Margins_right = 10;
static const int DEF_VALUE_Contents_Margins_bottom = 10;



CUiImageBorderWidget::CUiImageBorderWidget(QWidget* parent)
    : QWidget(parent)
{
	//setAttribute
	//Ui level 0, nothing
	//半透明的背景
	this->setAttribute(Qt::WA_TranslucentBackground); 
	//无边框
	this->setWindowFlags(Qt::FramelessWindowHint);
	//Widget内部的控件和Widget边框之间的 空白（margin）和间距（spacing）
	this->setContentsMargins(DEF_VALUE_Contents_Margins_left, DEF_VALUE_Contents_Margins_top, 
		DEF_VALUE_Contents_Margins_right, DEF_VALUE_Contents_Margins_bottom);//must set 


	//set data
	m_rcSrc = QRect(0, 0, 0, 0);
	m_ptTopLeft_InRcSrc = QPoint(0, 0);
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
		m_arrayRcSrc9Grid[nIndex] = QRect(0, 0, 0, 0);
	}

	QString strThemeName;
	QString strShadowPngPath;
	strThemeName = CUiStyleManager::getInstance().getThemeName();
	//C:\LSL\SVNWork\slin_code\DataServer\Yahoo_TIP\TA_BASE\transactive\app\YahooFinanceStock\YahooFinanceStockClient\Resources\skins\default\shadow.png
	strShadowPngPath = CUiPathResolve::getInstance().getResourcesSkinsThemePngPath(strThemeName, DEF_VALUE_Resources_skins_Theme_ShadowPng);
    _SetImage(strShadowPngPath, QPoint(DEF_VALUE_Rect_Border_Width, DEF_VALUE_Rect_Border_Hight));


}

void CUiImageBorderWidget::paintEvent(QPaintEvent *p)
{
	//class Q_GUI_EXPORT QWidget : public QObject, public QPaintDevice
    QPainter painter(this);
	QRect rectWidget = this->rect();

	//Ui level 1, rect grid
    _Draw8Border(&painter, rectWidget);
}

bool CUiImageBorderWidget::_ClearImage()
{
	if (!m_imge.isNull())
	{
		m_imge = QImage();
	}
	return true;
}

void CUiImageBorderWidget::_SetAttribute()
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


//SplitRect
//0 1 2 
//3 4 5 
//6 7 8 
bool CUiImageBorderWidget::_SplitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount)
{
	//
	QRect* arrayRect = parrayRect;
	//
	int nWidth = rcSrc.width();
	int nHeight = rcSrc.height();
	//
	if (ptTopLeft.x() <= 0)
		return false;
	if (ptTopLeft.y() <= 0)
		return false;
	if (ptTopLeft.x() >= nWidth / 2)
		return false;
	if (ptTopLeft.y() >= nHeight / 2)
		return false;
	//
	int x1 = rcSrc.left() + 0;
	int x2 = rcSrc.left() + ptTopLeft.x();
	int x3 = rcSrc.left() + nWidth - ptTopLeft.x();
	int x4 = rcSrc.left() + nWidth;
	//
	int y1 = rcSrc.top() + 0;
	int y2 = rcSrc.top() + ptTopLeft.y();
	int y3 = rcSrc.top() + nHeight - ptTopLeft.y();
	int y4 = rcSrc.top() + nHeight;
	//
	arrayRect[0] = QRect(QPoint(x1, y1), QPoint(x2, y2));
	arrayRect[1] = QRect(QPoint(x2 + 1, y1), QPoint(x3, y2));
	arrayRect[2] = QRect(QPoint(x3 + 1, y1), QPoint(x4, y2));

	arrayRect[3] = QRect(QPoint(x1, y2 + 1), QPoint(x2, y3));
	arrayRect[4] = QRect(QPoint(x2 + 1, y2 + 1), QPoint(x3, y3));
	arrayRect[5] = QRect(QPoint(x3 + 1, y2 + 1), QPoint(x4, y3));

	arrayRect[6] = QRect(QPoint(x1, y3 + 1), QPoint(x2, y4));
	arrayRect[7] = QRect(QPoint(x2 + 1, y3 + 1), QPoint(x3, y4));
	arrayRect[8] = QRect(QPoint(x3 + 1, y3 + 1), QPoint(x4, y4));
	//
	return true;
}

bool CUiImageBorderWidget::_SetImage(const QString& strImageFileName, QPoint ptTopLeft)
{
	_ClearImage();
	//
	if (false == m_imge.load(strImageFileName))
	{
		return false;
	}
	//
	int nImageWidth = m_imge.width();
	int nImageHeight = m_imge.height();
	//
	//将图片分割成9块，边缘部分以后有用
	return _SplitRect(QRect(0, 0, nImageWidth, nImageHeight), ptTopLeft, m_arrayRcImage9Grid, 9);
}



//void CUiSkin9GridImage::draw(QPainter* p, QRect rc, int nAlpha) const
void CUiImageBorderWidget::_Draw9(QPainter* p, QRect rc, int nAlpha)
{
	QRect arrayDest[9];
	m_rcSrc = rc;//save data
	m_ptTopLeft_InRcSrc = m_arrayRcImage9Grid[0].bottomRight();//save data

	//
	_SplitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
	//
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
		m_arrayRcSrc9Grid[nIndex] = arrayDest[nIndex];//save data

		const QRect& rcSrc = m_arrayRcImage9Grid[nIndex];
		const QRect& rcDest = arrayDest[nIndex];
		//
		if (nAlpha > 0 && nAlpha <= 255)
		{
			p->drawImage(rcDest, m_imge, rcSrc);
		}
		else
		{
			p->drawImage(rcDest, m_imge, rcSrc);
		}
	}
}
//void CUiSkin9GridImage::drawBorder(QPainter* p, QRect rc) const
void CUiImageBorderWidget::_Draw8Border(QPainter* p, QRect rc)
{
	QRect arrayDest[9];

	m_rcSrc = rc;//save data
	m_ptTopLeft_InRcSrc = m_arrayRcImage9Grid[0].bottomRight();//save data
	//
	_SplitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
	//
	//0 1 2 
	//3 4 5 
	//6 7 8 
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
		m_arrayRcSrc9Grid[nIndex] = arrayDest[nIndex];//save data

		//4 is client area		
		if (nIndex == 4)
			continue;
		//
		const QRect& rcSrc = m_arrayRcImage9Grid[nIndex];
		const QRect& rcDest = arrayDest[nIndex];
		//
		p->drawImage(rcDest, m_imge, rcSrc);
	}
}


CUiCommon::ESplitRectType CUiImageBorderWidget::posType( const QPoint& posValue )
{
	CUiCommon::ESplitRectType nPosType = CUiCommon::SplitRectType_NULL;
	bool bIsValid = false;
	bool bRectContainsPos = false;

	if (m_rcSrc.width() > 0 && m_rcSrc.height() > 0)
	{
		bIsValid = true;
	}

	if (false == bIsValid)
	{
		nPosType = CUiCommon::SplitRectType_NULL;
		return nPosType;
	}

	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
		bRectContainsPos = false;
		bRectContainsPos = m_arrayRcSrc9Grid[nIndex].contains(posValue);
		if (bRectContainsPos)
		{
			nPosType = CUiCommon::getIntValue(nIndex);
			return nPosType;
		}
	}//for


	return nPosType;
}