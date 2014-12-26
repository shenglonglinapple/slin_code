#ifndef __CLASS_ITEM_USER_ORDER_HH__
#define __CLASS_ITEM_USER_ORDER_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>


class CItemUserOrderHelper;

class CItemUserOrder
{
public:
	enum EItemType
	{ 
		ItemType_ROOT,
		ItemType_ITEM,
	};
public:
	/*init item ROOT*/
	CItemUserOrder();
	/*init item ITEM*/
	CItemUserOrder(QList<QVariant>& ItemData, CItemUserOrder *parent);
	~CItemUserOrder();

	void appendChild(CItemUserOrder** ppItem);
	CItemUserOrder *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CItemUserOrder *parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
///////////////////
public:
	void findAndResetSubNodeData(CItemUserOrderHelper* pDataHelper );
	void _ResetCurrentNodeData(CItemUserOrderHelper* pDataHelper );
	void appendChildByData(CItemUserOrderHelper* pDataHelper);
	void removeChildByData(CItemUserOrderHelper* pDataHelper);

	EItemType getItemType();
	QString getNodeKey();
	void addOrUpdateSubNode( CItemUserOrderHelper* pDataHelper );
private:
	/*
	if ItemDataType_ROOT itemData is column Name parentItem is NULL
	if ItemDataType_ITEM itemData is one row columns value parentItem have value
	*/	
	QMutex m_mutex_ItemData;
	QList<QVariant> m_ItemData;
	CItemUserOrder* m_pParentItem;
	EItemType m_nItemType;
private:
	//	QMutexLocker lock(&m_mutex_LstChildItems);	
	QMutex m_mutex_LstChildItems;
	QList<CItemUserOrder*> m_LstChildItems;
private:
	CItemUserOrderHelper* m_pDataHelper;
private:
	QString m_strNodeKey;
};//CItemUserInstrument


#endif//__CLASS_ITEM_USER_ORDER_HH__





