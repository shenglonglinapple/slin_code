#ifndef WIZLOGINWIDGET_H
#define WIZLOGINWIDGET_H

#include <QtGui/QDialog>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>

#ifndef Q_OS_MAC
#include "share/wizshadowwindow.h"
#endif



class CWizLoginDialog : public CWizShadowWindow
{
    Q_OBJECT
public:
    explicit CWizLoginDialog(QWidget *parent = 0);
    ~CWizLoginDialog();


};

#endif // WIZLOGINWIDGET_H
