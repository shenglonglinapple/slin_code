#ifndef __CLASS_USER_HOLD_ACCOUNT_WIDGET_HH__
#define __CLASS_USER_HOLD_ACCOUNT_WIDGET_HH__

#include <QtGui/QWidget>
#include <QtGui/QTableView>

class QSqlTableModel;

class CUserHoldAccountWidget : public QWidget
{ 
	Q_OBJECT
public: 
	CUserHoldAccountWidget(QWidget* parent = 0); 
	~CUserHoldAccountWidget(); 
signals:
public slots:
	void slot_DataChange_UserHoldAccount();

private:
	void _CreateAction();
	void _CreateConnect();
private:
	QTableView* m_pUserHoldAccountTableView;
	QSqlTableModel* m_pUserHoldAccountModel;
}; 



#endif//__CLASS_USER_HOLD_ACCOUNT_WIDGET_HH__



