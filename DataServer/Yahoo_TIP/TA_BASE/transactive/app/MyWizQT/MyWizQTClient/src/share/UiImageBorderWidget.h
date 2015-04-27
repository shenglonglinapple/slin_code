#ifndef __CLASS_UI_IMAGE_BORDER_WIDGET_H__
#define __CLASS_UI_IMAGE_BORDER_WIDGET_H__

#include "share/UiCommon.h"
#include <QtGui/QWidget>
#include <QtGui/QImage>


class QPainter;

class CUiRect9GirdWidget : public QWidget
{
	Q_OBJECT;
public:
    CUiRect9GirdWidget(QWidget* parent = 0);
protected:
    virtual void paintEvent(QPaintEvent *p);
public:
	CUiCommon::ESplitRectType posType(const QPoint& posValue);
private:
	void _SetAttribute();
	bool _ClearImage();
	bool _SplitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount);
	bool _SetImage(const QString& strImageFileName, QPoint ptTopLeft);
	void _Draw9(QPainter* p, QRect rc, int nAlpha);
	void _Draw8Border(QPainter* p, QRect rc);
private:
	QImage m_imge;
	QRect m_arrayRcImage9Grid[9];//CUiCommon::ESplitRectType 
private:
	QRect m_rcSrc;//RectSrc;
	QPoint m_ptTopLeft_InRcSrc;
	QRect m_arrayRcSrc9Grid[9];
};

#endif // __CLASS_UI_IMAGE_BORDER_WIDGET_H__
