#include "main_window.h"

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
	this->resize(800, 600);

    table_view = new TableView();

	count_label = new QLabel();

    add_button = new QPushButton();
    add_button->setText("add");
	connect(add_button, SIGNAL(clicked()), this, SLOT(add()));

	update_button = new QPushButton();
	update_button->setText("update");

	delete_button = new QPushButton();
	delete_button->setText("delete");
	connect(delete_button, SIGNAL(clicked()), table_view, SLOT(remove()));

	clear_button = new QPushButton();
	clear_button->setText("clear");

	QHBoxLayout *operate_layout = new QHBoxLayout();
	operate_layout->addWidget(count_label);
	operate_layout->addStretch();
	operate_layout->addWidget(add_button);
	operate_layout->addWidget(update_button);
	operate_layout->addWidget(delete_button);
	operate_layout->addWidget(clear_button);
	operate_layout->addStretch();
	operate_layout->setSpacing(20);
	operate_layout->setContentsMargins(0, 0, 0, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addWidget(table_view);
	main_layout->addLayout(operate_layout);
	main_layout->setSpacing(20);
	main_layout->setContentsMargins(20, 20, 20, 20);

	this->setLayout(main_layout); 

	timer = new QTimer();
	timer->setInterval(1000);
	connect(timer, SIGNAL(timeout()), table_view, SLOT(changeValue()));
	connect(update_button, SIGNAL(clicked()), timer, SLOT(start()));
	connect(clear_button, SIGNAL(clicked()), timer, SLOT(stop()));
	connect(clear_button, SIGNAL(clicked()), table_view, SLOT(clear()));
	connect(table_view, SIGNAL(updateCount(int)), this, SLOT(updateCount(int)));


	this->updateCount(0);
}

MainWindow::~MainWindow()
{

}

void MainWindow::updateCount(int count)
{
	count_label->setText(QString("row count : %1").arg(QString::number(count)));
}

void MainWindow::add()
{
	int row_count = table_view->rowCount();
    for(int i = 0; i < 10000; ++i)
    {
        QStringList row_list;
		row_list <<  QString("file : %1").arg(row_count++) << QString("%1KB").arg(i) << QString::number(0) << QString("%1KB/s").arg(i) << QString("08:08:08") << QString("uploading");
        table_view->addRow(row_list);
    }
}