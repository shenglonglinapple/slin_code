#ifndef __CLASS__STRATEGY_ORDERS_WINDOW_H__
#define __CLASS__STRATEGY_ORDERS_WINDOW_H__

#include "ProjectCommonData.h"

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>
#include "TreeModel.h"

QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE


class CStrategyOrdersWindow : public QWidget
{
    Q_OBJECT


public:
    CStrategyOrdersWindow(QWidget* parent = 0);
	~CStrategyOrdersWindow();
public:
	void retranslateUi(QWidget* pMainWindow);
	void setupUi(QWidget* pMainWindow);
	void translateLanguage();

protected:

	
public slots:
	void slotStrategyOrdersInfoChanged( TreeItem* pTreeItem );

signals:


private:
	void _CreateAction();
	void _CreateConnect();
private:
	QWidget* m_pWidget_Central;
	QVBoxLayout* m_pVBoxLayout;

private:
	QTreeView* m_pTreeView;
	TreeModel* m_pTreeModel;

};

QT_END_NAMESPACE

#endif//__CLASS__STRATEGY_ORDERS_WINDOW_H__
