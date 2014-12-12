#ifndef CLIENTMAINWINDOW_H
#define CLIENTMAINWINDOW_H

#include <QtGui/QMainWindow>

class CClientMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    CClientMainWindow(QWidget *parent = 0);
    ~CClientMainWindow();
};

#endif // CLIENTMAINWINDOW_H
