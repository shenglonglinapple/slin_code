#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->checkBox_5->setCheckState(Qt::PartiallyChecked);

    QFile file(":/Resources/style.css");
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    QString s = in.readAll();

    qApp->setStyleSheet(s);
}

MainWindow::~MainWindow()
{
    delete ui;
}
