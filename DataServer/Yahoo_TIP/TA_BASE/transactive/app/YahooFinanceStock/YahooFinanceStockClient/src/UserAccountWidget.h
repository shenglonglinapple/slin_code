#ifndef __CLASS_USER_ACCOUNT_WIDGET_HH__
#define __CLASS_USER_ACCOUNT_WIDGET_HH__

#include <QtGui/QWidget>
#include <QtGui/QTableView>

class QSqlTableModel;

class CUserAccountWidget : public QWidget
{ 
	Q_OBJECT
public: 
	CUserAccountWidget(QWidget* parent = 0); 
	~CUserAccountWidget(); 
signals:
public slots:
	void slot_DataChange_UserAccount();
	void slot_DataChange_UserHoldAccount();

private:
	void _CreateAction();
	void _CreateConnect();
private:
	QTableView* m_pUserAccountTableView;
	QSqlTableModel* m_pUserAccountModel;

	QTableView* m_pUserHoldAccountTableView;
	QSqlTableModel* m_pUserHoldAccountModel;
}; 



#endif//__CLASS_USER_AMOUNT_WIDGET_HH__



