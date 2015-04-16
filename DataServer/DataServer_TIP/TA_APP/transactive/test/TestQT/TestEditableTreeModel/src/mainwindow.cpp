#include <QtGui>

#include "QtProjectCommonInclude.h"

#include "mainwindow.h"
#include "treeitem.h"
#include "treemodel.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi();

#ifdef Q_WS_MAEMO_5
    // Alternating row colors look bad on Maemo
    m_pTreeView->setAlternatingRowColors(false);
#endif


	TreeModel* model = NULL;
	model = new TreeModel(this);

	{
		QList<QVariant> lstClumnName;
		TreeItem::getLstClumnName(lstClumnName);
		TreeItem* pTreeItemRoot = NULL;
		pTreeItemRoot = new TreeItem(lstClumnName, NULL);

		//add item
		QString strItemValue;
		QList<QVariant> dataTreeItem;
		strItemValue = QObject::tr("V1");
		dataTreeItem.push_back(strItemValue);
		strItemValue = QObject::tr("V2");
		dataTreeItem.push_back(strItemValue);
		strItemValue = QObject::tr("V3");
		dataTreeItem.push_back(strItemValue);
		TreeItem* pTreeItem = NULL;
		pTreeItem = new TreeItem(dataTreeItem, pTreeItemRoot);

		pTreeItemRoot->appendChild(&pTreeItem);

		model->setRootItem(pTreeItemRoot);
	}

	{
		QHeaderView* m_pTableView_HheaderView = NULL;
		m_pTableView->setModel(model);
		m_pTableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
		m_pTableView->setAlternatingRowColors(true);
		m_pTableView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);

		m_pTableView_HheaderView = m_pTableView->horizontalHeader();

		m_pTableView_HheaderView->setClickable(true);
		m_pTableView_HheaderView->setHighlightSections(true);
		m_pTableView_HheaderView->setMovable(true);
		m_pTableView_HheaderView->setStretchLastSection(true);


		m_pTableView_HheaderView->moveSection(0, 1);
	
	}

    m_pTreeView->setModel(model);
    for (int column = 0; column < model->columnCount(); ++column)
	{
        m_pTreeView->resizeColumnToContents(column);
	}

    connect(exitAction, SIGNAL(triggered()), qApp, SLOT(quit()));

    connect(m_pTreeView->selectionModel(),
            SIGNAL(selectionChanged(const QItemSelection &,
                                    const QItemSelection &)),
            this, SLOT(updateActions()));

    connect(actionsMenu, SIGNAL(aboutToShow()), this, SLOT(updateActions()));
    connect(insertRowAction, SIGNAL(triggered()), this, SLOT(insertRow()));
    connect(insertColumnAction, SIGNAL(triggered()), this, SLOT(insertColumn()));
    connect(removeRowAction, SIGNAL(triggered()), this, SLOT(removeRow()));
    connect(removeColumnAction, SIGNAL(triggered()), this, SLOT(removeColumn()));
    connect(insertChildAction, SIGNAL(triggered()), this, SLOT(insertChild()));

    updateActions();




}

void MainWindow::insertChild()
{
    QModelIndex index = m_pTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = m_pTreeView->model();

    if (model->columnCount(index) == 0) {
        if (!model->insertColumn(0, index))
            return;
    }

    if (!model->insertRow(0, index))
        return;

    for (int column = 0; column < model->columnCount(index); ++column) {
        QModelIndex child = model->index(0, column, index);
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
        if (!model->headerData(column, Qt::Horizontal).isValid())
            model->setHeaderData(column, Qt::Horizontal, QVariant("[No header]"),
                                 Qt::EditRole);
    }

    m_pTreeView->selectionModel()->setCurrentIndex(model->index(0, 0, index),
                                            QItemSelectionModel::ClearAndSelect);
    updateActions();
}

bool MainWindow::insertColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = m_pTreeView->model();
    int column = m_pTreeView->selectionModel()->currentIndex().column();

    // Insert a column in the parent item.
    bool changed = model->insertColumn(column + 1, parent);
    if (changed)
        model->setHeaderData(column + 1, Qt::Horizontal, QVariant("[No header]"),
                             Qt::EditRole);

    updateActions();

    return changed;
}

void MainWindow::insertRow()
{
    QModelIndex index = m_pTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = m_pTreeView->model();

    if (!model->insertRow(index.row()+1, index.parent()))
        return;

    updateActions();

    for (int column = 0; column < model->columnCount(index.parent()); ++column) {
        QModelIndex child = model->index(index.row()+1, column, index.parent());
        model->setData(child, QVariant("[No data]"), Qt::EditRole);
    }
}

bool MainWindow::removeColumn(const QModelIndex &parent)
{
    QAbstractItemModel *model = m_pTreeView->model();
    int column = m_pTreeView->selectionModel()->currentIndex().column();

    // Insert columns in each child of the parent item.
    bool changed = model->removeColumn(column, parent);

    if (!parent.isValid() && changed)
        updateActions();

    return changed;
}

void MainWindow::removeRow()
{
    QModelIndex index = m_pTreeView->selectionModel()->currentIndex();
    QAbstractItemModel *model = m_pTreeView->model();
    if (model->removeRow(index.row(), index.parent()))
        updateActions();
}

void MainWindow::updateActions()
{
    bool hasSelection = !m_pTreeView->selectionModel()->selection().isEmpty();
    removeRowAction->setEnabled(hasSelection);
    removeColumnAction->setEnabled(hasSelection);

    bool hasCurrent = m_pTreeView->selectionModel()->currentIndex().isValid();
    insertRowAction->setEnabled(hasCurrent);
    insertColumnAction->setEnabled(hasCurrent);

    if (hasCurrent) {
        m_pTreeView->closePersistentEditor(m_pTreeView->selectionModel()->currentIndex());

        int row = m_pTreeView->selectionModel()->currentIndex().row();
        int column = m_pTreeView->selectionModel()->currentIndex().column();
        if (m_pTreeView->selectionModel()->currentIndex().parent().isValid())
            statusBar()->showMessage(tr("Position: (%1,%2)").arg(row).arg(column));
        else
            statusBar()->showMessage(tr("Position: (%1,%2) in top level").arg(row).arg(column));
    }
}

void MainWindow::setupUi()
{
	if (this->objectName().isEmpty())
		this->setObjectName(QString::fromUtf8("MainWindow"));
	this->resize(573, 468);
	exitAction = new QAction(this);
	exitAction->setObjectName(QString::fromUtf8("exitAction"));
	insertRowAction = new QAction(this);
	insertRowAction->setObjectName(QString::fromUtf8("insertRowAction"));
	removeRowAction = new QAction(this);
	removeRowAction->setObjectName(QString::fromUtf8("removeRowAction"));
	insertColumnAction = new QAction(this);
	insertColumnAction->setObjectName(QString::fromUtf8("insertColumnAction"));
	removeColumnAction = new QAction(this);
	removeColumnAction->setObjectName(QString::fromUtf8("removeColumnAction"));
	insertChildAction = new QAction(this);
	insertChildAction->setObjectName(QString::fromUtf8("insertChildAction"));
	centralwidget = new QWidget(this);
	centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
	vboxLayout = new QVBoxLayout(centralwidget);
	vboxLayout->setSpacing(0);
	vboxLayout->setContentsMargins(0, 0, 0, 0);
	vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
	m_pTreeView = new QTreeView(centralwidget);
	m_pTreeView->setObjectName(QString::fromUtf8("view"));
	m_pTreeView->setAlternatingRowColors(true);
	m_pTreeView->setSelectionBehavior(QAbstractItemView::SelectItems);
	m_pTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
	m_pTreeView->setAnimated(false);
	m_pTreeView->setAllColumnsShowFocus(true);

	//m_pTreeView->setEditTriggers(QAbstractItemView::NoEditTriggers);
	m_pTreeView->setAlternatingRowColors(true);
	m_pTreeView->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);



	
	//m_pTreeView->setColumnHidden(0, true);
	m_pTableView = new QTableView(this);

	vboxLayout->addWidget(m_pTreeView);
	vboxLayout->addWidget(m_pTableView);

	this->setCentralWidget(centralwidget);
	menubar = new QMenuBar(this);
	menubar->setObjectName(QString::fromUtf8("menubar"));
	menubar->setGeometry(QRect(0, 0, 573, 31));
	fileMenu = new QMenu(menubar);
	fileMenu->setObjectName(QString::fromUtf8("fileMenu"));
	actionsMenu = new QMenu(menubar);
	actionsMenu->setObjectName(QString::fromUtf8("actionsMenu"));
	this->setMenuBar(menubar);
	statusbar = new QStatusBar(this);
	statusbar->setObjectName(QString::fromUtf8("statusbar"));
	this->setStatusBar(statusbar);

	menubar->addAction(fileMenu->menuAction());
	menubar->addAction(actionsMenu->menuAction());
	fileMenu->addAction(exitAction);
	actionsMenu->addAction(insertRowAction);
	actionsMenu->addAction(insertColumnAction);
	actionsMenu->addSeparator();
	actionsMenu->addAction(removeRowAction);
	actionsMenu->addAction(removeColumnAction);
	actionsMenu->addSeparator();
	actionsMenu->addAction(insertChildAction);

	retranslateUi();

	QMetaObject::connectSlotsByName(this);
}

void MainWindow::retranslateUi()
{
	this->setWindowTitle(QApplication::translate("MainWindow", "Editable Tree Model", 0, QApplication::UnicodeUTF8));
	exitAction->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
	exitAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0, QApplication::UnicodeUTF8));
	insertRowAction->setText(QApplication::translate("MainWindow", "Insert Row", 0, QApplication::UnicodeUTF8));
	insertRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, R", 0, QApplication::UnicodeUTF8));
	removeRowAction->setText(QApplication::translate("MainWindow", "Remove Row", 0, QApplication::UnicodeUTF8));
	removeRowAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, R", 0, QApplication::UnicodeUTF8));
	insertColumnAction->setText(QApplication::translate("MainWindow", "Insert Column", 0, QApplication::UnicodeUTF8));
	insertColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+I, C", 0, QApplication::UnicodeUTF8));
	removeColumnAction->setText(QApplication::translate("MainWindow", "Remove Column", 0, QApplication::UnicodeUTF8));
	removeColumnAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+R, C", 0, QApplication::UnicodeUTF8));
	insertChildAction->setText(QApplication::translate("MainWindow", "Insert Child", 0, QApplication::UnicodeUTF8));
	insertChildAction->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
	fileMenu->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
	actionsMenu->setTitle(QApplication::translate("MainWindow", "&Actions", 0, QApplication::UnicodeUTF8));
}
