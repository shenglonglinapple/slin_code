#ifndef __CLASS_UI_RECT_9GRID_WIDGET_H__
#define __CLASS_UI_RECT_9GRID_WIDGET_H__

#include "share/UiCommon.h"
#include <QtGui/QWidget>

class CUiSkin9GridImage;

class CUiRect9GirdWidget : public QWidget
{
	Q_OBJECT;
public:
    CUiRect9GirdWidget(QWidget* parent = 0);
private:
    CUiSkin9GridImage* m_pUiSkin9GridImage;
protected:
    virtual void paintEvent(QPaintEvent *p);
private:
	void _SetAttribute();
public:
	CUiCommon::ESplitRectType posType(const QPoint& posValue);
};

#endif // __CLASS_UI_RECT_9GRID_WIDGET_H__
