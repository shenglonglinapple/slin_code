#include "UiIconLineEditContainer.h"

#include <QtCore/QtCore>
#include <QtGui/QtGui>

#include "share/UiSkin9GridImage.h"
#include "share/UiStyleManager.h"
#include "share/UiPathResolve.h"



CUiIconLineEditContainer::CUiIconLineEditContainer(QWidget* parent)
: QWidget(parent)
, m_background(NULL)
, m_layout(NULL)
, m_edit(NULL)
, m_leftIcon(NULL)
, m_rightIcon(NULL)
{
	m_layout = new QHBoxLayout(this);
	m_edit = new QLineEdit(this);
	m_edit->setAttribute(Qt::WA_MacShowFocusRect, false);
	m_edit->setStyleSheet(QString("QLineEdit{ border:none; color:#2F2F2F; "
		"selection-background-color: #8ECAF1;}"));
	m_leftIcon = new QLabel(this);
	m_rightIcon = new QLabel(this);
	//
	m_layout->setSpacing(12);
	m_layout->setContentsMargins(10, 10, 10,10);
	//
	m_layout->addWidget(m_leftIcon);
	m_layout->addWidget(m_edit);
	m_layout->addWidget(m_rightIcon);

}

CUiIconLineEditContainer::~CUiIconLineEditContainer()
{
	if (m_background)
		delete m_background;
}
void CUiIconLineEditContainer::setBackgroundImage(QString fileName, QPoint pt)
{
	m_background = new CUiSkin9GridImage();
	m_background->setImage(fileName, pt);
}

void CUiIconLineEditContainer::setLeftIcon(QString fileName)
{
	m_leftIcon->setPixmap(QPixmap(fileName));
}
void CUiIconLineEditContainer::setRightIcon(QString fileName)
{
	m_rightIcon->setPixmap(QPixmap(fileName));
}

void CUiIconLineEditContainer::setPlaceholderText(const QString &strText)
{
	m_edit->setPlaceholderText(strText);
}

void CUiIconLineEditContainer::setAutoClearRightIcon(bool bAutoClean)
{
	if (bAutoClean)
	{
		connect(m_edit, SIGNAL(textEdited(QString)), SLOT(cleanRightIcon()));
	}
	else
	{
		disconnect(m_edit, SIGNAL(textEdited(QString)), this, SLOT(cleanRightIcon()));
	}
}

void CUiIconLineEditContainer::paintEvent(QPaintEvent *event)
{
	if (m_background && m_background->isValid())
	{
		QPainter paint(this);
		m_background->draw(&paint, rect(), 0);
	}
	else
	{
		QWidget::paintEvent(event);
	}
}


void CUiIconLineEditContainer::mousePressEvent(QMouseEvent *event)
{
	if (m_rightIcon->geometry().contains(event->pos()))
	{
		emit rightIconClicked();
	}
}

void CUiIconLineEditContainer::cleanRightIcon()
{
	m_rightIcon->setPixmap(QPixmap());
}
