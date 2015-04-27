#ifndef __CLASS_UI_IMAGE_BUTTON_H__
#define __CLASS_UI_IMAGE_BUTTON_H__

#include <QtGui/QPushButton>
#include <QtGui/QProxyStyle>

#include "share/UiSkin9GridImage.h"


/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
class CWizImageButtonStyle : public QProxyStyle
{
public:
	CWizImageButtonStyle(
		const QString& normalBackgroundFileName, 
		const QString& hotBackgroundFileName,
		const QString& downBackgroundFileName, 
		const QString& disabledBackgroundFileName,
		const QColor& normalTextColor, 
		const QColor& activeTextColor, 
		const QColor& disableTextColor);
private:
	CUiSkin9GridImage m_imagePushButton;
	CUiSkin9GridImage m_imagePushButtonHot;
	CUiSkin9GridImage m_imagePushButtonPressed;
	CUiSkin9GridImage m_imagePushButtonDisabled;
	QColor m_colorTextNormal;
	QColor m_colorTextActive;
	QColor m_colorTextDisable;
protected:
	virtual void drawControl(ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget) const;

};

/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
/////////////////////////////////////////////////////
class CUiImageButton : public QPushButton
{
public:
	CUiImageButton(QWidget* parent = 0);
public:
	void setButtonStyle(
		const QString& normalBackgroundFileName, 
		const QString& hotBackgroundFileName,
		const QString& downBackgroundFileName, 
		const QString& disabledBackgroundFileName,
		const QColor& normalTextColor, 
		const QColor& activeTextColor, 
		const QColor& disableTextColor);

};
#endif // __CLASS_UI_IMAGE_BUTTON_H__
