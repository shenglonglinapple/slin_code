#ifndef __CLASS__SMART_HOT_QUOTES_WINDOW_H__
#define __CLASS__SMART_HOT_QUOTES_WINDOW_H__



#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include <QtGui/QTabWidget>


QT_BEGIN_NAMESPACE
class QVBoxLayout;
class QTabWidget;

QT_END_NAMESPACE

class CItemModelUserInstrumentInfo;
class CUserInstrumentInfoView;
class CItemUserInstrumentInfo;

//class IconDelegate;
class CLeftDockWidget : public QWidget
{
    Q_OBJECT


public:
    CLeftDockWidget(QWidget* parent = 0);
	~CLeftDockWidget();
public:
	void setupUi();
	void translateLanguage();
public:
	QSize sizeHint() const;
protected:

	
public slots:
	void slotUserInstrumentInfoChanged(CItemUserInstrumentInfo* pTreeItem);
	void slotCurrentInstrumentChanged(unsigned int nInstrumentID);

signals:
	void signalCurrentInstrumentChanged(unsigned int nInstrumentID);

private:
	void _CreateAction();
	void _CreateConnect();
private:
	QVBoxLayout* m_pVBoxLayout;
	QTabWidget* m_pTabWidget;
private:
	CItemModelUserInstrumentInfo* m_pItemModelUserInstrumentInfo;
public:
	//IconDelegate* m_pIconDelegate;
	CUserInstrumentInfoView* m_pUserInstrumentInfoView;

};

//QT_END_NAMESPACE

#endif//__CLASS__SMART_HOT_QUOTES_WINDOW_H__
