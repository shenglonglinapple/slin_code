#ifndef WIZUI_H
#define WIZUI_H

#include <QtGui/QImage>
#include <QtGui/QPushButton>

class QPainter;
class QLineEdit;
class QLabel;

class CWizSkin9GridImage
{
public:
	CWizSkin9GridImage();
	~CWizSkin9GridImage();
protected:
    QImage m_img;
    QRect m_arrayImageGrid[9];
    //
    bool Clear();
public:
    static bool SplitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount);
    bool SetImage(const QString& strImageFileName, QPoint ptTopLeft);
    //
    void Draw(QPainter* p, QRect rc, int nAlpha) const;
    void DrawBorder(QPainter* p, QRect rc) const;
    bool Valid() const;
    //
    QSize actualSize() const { return m_img.size(); }
};


#endif // WIZUI_H
