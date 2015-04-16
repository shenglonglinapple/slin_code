#ifndef __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__
#define __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__

#include <QtGui/QMdiArea>
#include <QtGui/QMdiSubWindow>

class CStockMinTimeMaxTimeTableView;
class CStockHistoryDataTableView;
class CUserTradeTableView;
class CUserAccountWidget;
class CUserHoldAccountWidget;
class CStockInfoWidget;

class CClientMainWindowMdiArea : public QMdiArea
{
    Q_OBJECT

public:
    CClientMainWindowMdiArea(QWidget *parent = 0);
    ~CClientMainWindowMdiArea();
private:
	void _SetupUi();
	void _TranslateLanguage();
private:
	CStockMinTimeMaxTimeTableView* m_pStockMinTimeMaxTimeTableView;
	CStockHistoryDataTableView* m_pStockHistoryDataTableView;
	CUserTradeTableView* m_pUserTradeTableView;
	CUserAccountWidget* m_pUserAccountWidget;
	CUserHoldAccountWidget* m_pUserHoldAccountWidget;
	CStockInfoWidget* m_pStockInfoWidget;
};

#endif // __CLASS_CLIENT_MAIN_WINDOW_MDIAREA_HH__
