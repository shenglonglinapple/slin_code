#ifndef TREEITEM_H
#define TREEITEM_H

#include <QList>
#include <QVariant>
#include <QVector>

//! [0]
class TreeItem
{
public:
    TreeItem(const QList<QVariant> &data, TreeItem *parent = 0);
    ~TreeItem();

	void appendChild(TreeItem** ppItem);
    TreeItem *child(int number);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    bool insertChildren(int position, int count, int columns);
    bool insertColumns(int position, int columns);
    TreeItem *parent();
    bool removeChildren(int position, int count);
    bool removeColumns(int position, int columns);
    int childNumber() const;
    bool setData(int column, const QVariant &value);

public:
	static void getLstClumnName(QStringList& lstClumnName );
	static void getLstClumnName(QList<QVariant>& lstClumnName );
private:
    QList<TreeItem*> childItems;
    QList<QVariant> itemData;
    TreeItem *parentItem;
};
//! [0]

#endif
