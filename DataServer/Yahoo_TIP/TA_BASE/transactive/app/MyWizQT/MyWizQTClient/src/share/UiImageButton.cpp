#include "share/UiImageButton.h"

#include <QtGui/QtGui>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CWizImageButtonStyle::CWizImageButtonStyle( const QString& normalBackgroundFileName, const QString& hotBackgroundFileName, const QString& downBackgroundFileName, const QString& disabledBackgroundFileName, const QColor& normalTextColor, const QColor& activeTextColor, const QColor& disableTextColor )
{
	m_imagePushButton.setImage(normalBackgroundFileName, QPoint(4, 4));
	m_imagePushButtonHot.setImage(hotBackgroundFileName, QPoint(4, 4));
	m_imagePushButtonPressed.setImage(downBackgroundFileName, QPoint(4, 4));
	m_imagePushButtonDisabled.setImage(disabledBackgroundFileName, QPoint(4, 4));
	m_colorTextNormal = normalTextColor;
	m_colorTextActive = activeTextColor;
	m_colorTextDisable = disableTextColor;
}


void CWizImageButtonStyle::drawControl( ControlElement element, const QStyleOption *option, QPainter *painter, const QWidget *widget ) const
{
	const QStyleOptionButton* vopt = NULL;

	switch (element)
	{
	case CE_PushButton:
		{
			vopt = qstyleoption_cast<const QStyleOptionButton *>(option);
			if (NULL == vopt)
			{
				return;
			}
			//ATLASSERT(vopt);
			//
			if (!vopt->state.testFlag(QStyle::State_Enabled))
			{
				m_imagePushButtonDisabled.draw_const(painter, vopt->rect, 0);
				painter->setPen(m_colorTextDisable);
			}
			else if (!vopt->state.testFlag(QStyle::State_Raised))
			{
				m_imagePushButtonPressed.draw_const(painter, vopt->rect, 0);
				painter->setPen(m_colorTextActive);
			}
			else if (vopt->state.testFlag(QStyle::State_MouseOver))
			{
				m_imagePushButtonHot.draw_const(painter, vopt->rect, 0);
				painter->setPen(m_colorTextActive);
			}
			else
			{
				m_imagePushButton.draw_const(painter, vopt->rect, 0);
				painter->setPen(m_colorTextNormal);
			}
			//
			painter->drawText(vopt->rect,Qt::AlignCenter, vopt->text);
		}
		break;
	default:
		break;
	}
}





//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

CUiImageButton::CUiImageButton( QWidget* parent /*= 0*/ )
	:QPushButton(parent)
{

}

void CUiImageButton::setButtonStyle( 
const QString& normalBackgroundFileName, 
const QString& hotBackgroundFileName, 
const QString& downBackgroundFileName, 
const QString& disabledBackgroundFileName, 
const QColor& normalTextColor, 
const QColor& activeTextColor, 
const QColor& disableTextColor )
{
	CWizImageButtonStyle* style = new CWizImageButtonStyle(
		normalBackgroundFileName,
		hotBackgroundFileName, 
		downBackgroundFileName,
		disabledBackgroundFileName, 
		normalTextColor,
		activeTextColor, 
		disableTextColor);

	setStyle((QStyle*)style);
}
