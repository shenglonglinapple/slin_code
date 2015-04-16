#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtCore/QModelIndex>


class QAction;
class QWidget;
class QVBoxLayout;
class QTreeView;
class QMenuBar;
class QMenu;
class QStatusBar;
class QTableView;



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);

public slots:
    void updateActions();

private slots:
    void insertChild();
    bool insertColumn(const QModelIndex &parent = QModelIndex());
    void insertRow();
    bool removeColumn(const QModelIndex &parent = QModelIndex());
    void removeRow();
public:
	void setupUi(); // setupUi
	void retranslateUi(); // retranslateUi

public:
	QAction *exitAction;
	QAction *insertRowAction;
	QAction *removeRowAction;
	QAction *insertColumnAction;
	QAction *removeColumnAction;
	QAction *insertChildAction;
	QWidget *centralwidget;
	QVBoxLayout *vboxLayout;
	QTreeView *m_pTreeView;
	QMenuBar *menubar;
	QMenu *fileMenu;
	QMenu *actionsMenu;
	QStatusBar *statusbar;
	QTableView* m_pTableView;


};

#endif
