#include "TreeItem.h"
#include "TreeModel.h"


int main()
{

	TreeItem* pTreeItemRoot = NULL;
	TreeModel* model = NULL;
	QTableView* m_pTableView = NULL;


	{//data
		QList<QVariant> lstClumnName;
		TreeItem::getLstClumnName(lstClumnName);
		pTreeItemRoot = new TreeItem(lstClumnName, NULL);

		//add item
		QString strItemValue;
		QList<QVariant> dataTreeItem;
		strItemValue = QObject::tr("Column1_Value");
		dataTreeItem.push_back(strItemValue);
		strItemValue = QObject::tr("Column2_Value");
		dataTreeItem.push_back(strItemValue);
		strItemValue = QObject::tr("Column3_Value");
		dataTreeItem.push_back(strItemValue);
		TreeItem* pTreeItem = NULL;
		pTreeItem = new TreeItem(dataTreeItem, pTreeItemRoot);

		pTreeItemRoot->appendChild(&pTreeItem);

	}

	{//model
		model = new TreeModel(NULL);
		model->setRootItem(pTreeItemRoot);
	}

	{//view
		QHeaderView* m_pTableView_HheaderView = NULL;
		m_pTableView = new QTableView();
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


	return 0;
}

