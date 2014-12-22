#ifndef __CLASS__USER_INSTRUMENT_WINDOW_H__
#define __CLASS__USER_INSTRUMENT_WINDOW_H__

#include <QtGui/QWidget>
#include <QtGui/QMdiSubWindow>


//class IconDelegate;
class CUserInstrumentWindow : public QMdiSubWindow
{
    Q_OBJECT
public:
    CUserInstrumentWindow(QWidget* parent = 0);
	~CUserInstrumentWindow();
public:
	QSize sizeHint() const;
};

//QT_END_NAMESPACE

#endif//__CLASS__USER_INSTRUMENT_WINDOW_H__
