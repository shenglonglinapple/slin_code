#include "wizLoginDialog.h"

#include <QtGui/QPainter>
#include <QtGui/QMouseEvent>
#include <QtGui/QMenu>
#include <QtGui/QBitmap>
#include <QtGui/QToolButton>
#include <QtGui/QDesktopServices>
#include <QtCore/QUrl>
#include <QtCore/QDebug>
#include <QtCore/QDateTime>



CWizLoginDialog::CWizLoginDialog(QWidget *parent)
    : CWizShadowWindow(parent)
{
	setCanResize(true);
	this->resize(500, 500);
	//setCanResize(true);
	//setCanResize(false);
	setCanResize(true);
}

CWizLoginDialog::~CWizLoginDialog()
{
 
}
