#ifndef  MAINWINDOW_H
#define  MAINWINDOW_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QTimer>
#include "table_view.h"

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void add();
	void updateCount(int count);

private:

	TableView *table_view;
	QLabel *count_label;
	QPushButton *add_button;
	QPushButton *update_button;
	QPushButton *delete_button;
	QPushButton *clear_button;
	QTimer *timer;
};

#endif  //MAINWINDOW_H
