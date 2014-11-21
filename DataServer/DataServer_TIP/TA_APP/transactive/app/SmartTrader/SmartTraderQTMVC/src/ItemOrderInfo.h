#ifndef __CLASS_TREE_ITEM_ORDER_HH__
#define __CLASS_TREE_ITEM_ORDER_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "IconDelegate.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class COrderInfo;


class CTreeItemOrder
{
public:
	enum enItemDataType
	{ 
		ItemDataType_NULL,
		ItemDataType_ROOT,
		ItemDataType_ITEM,

	};
public:
	CTreeItemOrder();
    CTreeItemOrder(const QList<QVariant> &data, CTreeItemOrder *parent = NULL);
    ~CTreeItemOrder();

public:
	void appendChild(CTreeItemOrder** ppItem);

	CTreeItemOrder* child(int row);

    int childCount() const;

    int columnCount() const;

    QVariant data(int column) const;

    int childNumber() const;

    CTreeItemOrder* parent();
public:
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	bool setData(int column, const QVariant &dataValue);

public:
	int indexOfChildren(CTreeItemOrder* pChildrenItem) const;

public:
	void rootNodeSetColumnsName();
public:
	void appendChildByData(COrderInfo* pData);
	void resetChildrenData(COrderInfo* pData);
	void resetCurrentNodeData(COrderInfo* pData );
	void resetCurrentNodeDataDefultValue();

	void setDataType(enItemDataType nDataTypeExchange);
	enItemDataType getDataType();
	unsigned int getKey();

public:
	static void getLstClumnName(QList<QVariant>& lstClumnName );
	static void getLstClumnName(QStringList& strlstClumnName );

private:
	void _GetItemDataFromClass(COrderInfo* pExchangeInfo, QList<QVariant>& itemDataTmp);
private:
	CTreeItemOrder* m_pParentItem;
	QList<CTreeItemOrder*> m_LstChildItems;
    QList<QVariant> m_ItemData;
	int  m_ItemDataNum;
private:
	enItemDataType m_nDataType;
private:
	unsigned int m_nKey;

};

//QT_END_NAMESPACE

#endif//__CLASS_TREE_ITEM_ORDER_HH__







