#ifndef __CLASS_UISKIN9_GUIDIMAGE_H__
#define __CLASS_UISKIN9_GUIDIMAGE_H__

#include "share/UiCommon.h"
#include <QtGui/QImage>

class QPainter;

class CUiSkin9GridImage
{
public:
	CUiSkin9GridImage();
	~CUiSkin9GridImage();
protected:
    QImage m_imge;
	QRect m_arrayRcImage9Grid[9];//CUiCommon::ESplitRectType 
    //
    bool _Clear();
public:
    static bool splitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount);
	void draw_const(QPainter* p, QRect rc, int nAlpha) const;
	//void drawBorder(QPainter* p, QRect rc) const;
	void drawBorder_const(QPainter* p, QRect rc) const;
public:
	//bool splitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount);
    bool setImage(const QString& strImageFileName, QPoint ptTopLeft);
	void draw(QPainter* p, QRect rc, int nAlpha);
	void drawBorder(QPainter* p, QRect rc);
    bool isValid() const;
    QSize actualSize() const;
public:
	CUiCommon::ESplitRectType posType(const QPoint& posValue);//drawBorder//draw
protected:
	QRect m_rcSrc;//RectSrc;
	QPoint m_ptTopLeft_InRcSrc;
	QRect m_arrayRcSrc9Grid[9];
	
};


#endif // __CLASS_UISKIN9_GUIDIMAGE_H__
