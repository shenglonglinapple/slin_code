#ifndef __CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HH__
#define __CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

class CItemStockMinTimeMaxTimeHelper;

class CItemStockMinTimeMaxTime
{
public:
	enum EItemType
	{ 
		ItemType_ROOT,
		ItemType_ITEM,
	};
public:
	/*init item ROOT*/
	CItemStockMinTimeMaxTime();
	/*init item ITEM*/
	CItemStockMinTimeMaxTime(QList<QVariant>& ItemData, CItemStockMinTimeMaxTime *parent);
	~CItemStockMinTimeMaxTime();

	void appendChild(CItemStockMinTimeMaxTime** ppItem);
	CItemStockMinTimeMaxTime *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CItemStockMinTimeMaxTime *parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
///////////////////
private:
	void _ResetCurrentNodeData(CItemStockMinTimeMaxTimeHelper* pItemDataHelper );
public:
	void findAndResetSubNodeData(CItemStockMinTimeMaxTimeHelper* pItemDataHelper );
	void appendChildByData(CItemStockMinTimeMaxTimeHelper* pItemDataHelper);
	void removeChildByData(CItemStockMinTimeMaxTimeHelper* pItemDataHelper);

	EItemType getItemType();
	QString getNodeKey();
private:
	/*
	if ItemDataType_ROOT itemData is column Name parentItem is NULL
	if ItemDataType_ITEM itemData is one row columns value parentItem have value
	*/	
	QMutex m_mutex_ItemData;
	QList<QVariant> m_ItemData;
	CItemStockMinTimeMaxTime* m_pParentItem;
	EItemType m_nItemType;
private:
	//	QMutexLocker lock(&m_mutex_LstChildItems);	
	QMutex m_mutex_LstChildItems;
	QList<CItemStockMinTimeMaxTime*> m_LstChildItems;
private:
	CItemStockMinTimeMaxTimeHelper* m_pItemUserInstrumentHelper;
private:
	QString m_strNodeKey;
};//


#endif//__CLASS_ITEM_STOCK_MIN_TIME_MAX_TIME_HH__





