#include "share/UiSkin9GridImage.h"

#include <QtGui/QPainter>
#include <QtGui/QWidget>
#include <QtGui/QBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMouseEvent>

//Horizontal line//横线
//Vertical line//竖线


CUiSkin9GridImage::CUiSkin9GridImage()
{
	m_rcSrc = QRect(0, 0, 0, 0);
	m_ptTopLeft_InRcSrc = QPoint(0, 0);
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
		m_arrayRcSrc9Grid[nIndex] = QRect(0, 0, 0, 0);
	}
}

CUiSkin9GridImage::~CUiSkin9GridImage()
{

}

bool CUiSkin9GridImage::_Clear()
{
    if (!m_imge.isNull())
    {
        m_imge = QImage();
    }
    return true;
}
//SplitRect
//0 1 2 
//3 4 5 
//6 7 8 
bool CUiSkin9GridImage::splitRect(const QRect& rcSrc, QPoint ptTopLeft, QRect* parrayRect, int nArrayCount)
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

bool CUiSkin9GridImage::setImage(const QString& strImageFileName, QPoint ptTopLeft)
{
    _Clear();
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
    return splitRect(QRect(0, 0, nImageWidth, nImageHeight), ptTopLeft, m_arrayRcImage9Grid, 9);
}

bool CUiSkin9GridImage::isValid() const
{
	bool bIsValid = false;
	if (m_imge.width() > 0 && m_imge.height() > 0)
	{
		bIsValid = true;
	}
    return bIsValid;
}

void CUiSkin9GridImage::draw_const( QPainter* p, QRect rc, int nAlpha ) const
{
	QRect arrayDest[9];
	//
	splitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
	//
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
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

//void CUiSkin9GridImage::draw(QPainter* p, QRect rc, int nAlpha) const
void CUiSkin9GridImage::draw(QPainter* p, QRect rc, int nAlpha)
{
    QRect arrayDest[9];
	m_rcSrc = rc;//save data
	m_ptTopLeft_InRcSrc = m_arrayRcImage9Grid[0].bottomRight();//save data

    //
    splitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
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

void CUiSkin9GridImage::drawBorder_const(QPainter* p, QRect rc) const
{
	QRect arrayDest[9];
	//
	splitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
	//
	//0 1 2 
	//3 4 5 
	//6 7 8 
	for (int nIndex = 0; nIndex < 9; nIndex++)
	{
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

//void CUiSkin9GridImage::drawBorder(QPainter* p, QRect rc) const
void CUiSkin9GridImage::drawBorder(QPainter* p, QRect rc)
{
    QRect arrayDest[9];

	m_rcSrc = rc;//save data
	m_ptTopLeft_InRcSrc = m_arrayRcImage9Grid[0].bottomRight();//save data
    //
    splitRect(rc, m_arrayRcImage9Grid[0].bottomRight(), arrayDest, 9);
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
QSize CUiSkin9GridImage::actualSize() const
{
	QSize sizeImage;
	sizeImage = m_imge.size(); 
	return sizeImage; 
}

CUiCommon::ESplitRectType CUiSkin9GridImage::posType( const QPoint& posValue )
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
