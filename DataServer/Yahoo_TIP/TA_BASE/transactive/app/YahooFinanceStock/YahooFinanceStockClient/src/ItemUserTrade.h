#ifndef __CLASS_ITEM_USER_TRADE_HH__
#define __CLASS_ITEM_USER_TRADE_HH__


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

class CItemUserTradeHelper;

class CItemUserTrade
{
public:
	enum EItemType
	{ 
		ItemType_ROOT,
		ItemType_ITEM,
	};
public:
	/*init item ROOT*/
	CItemUserTrade();
	/*init item ITEM*/
	CItemUserTrade(QList<QVariant>& ItemData, CItemUserTrade *parent);
	~CItemUserTrade();

	void appendChild(CItemUserTrade** ppItem);
	CItemUserTrade *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CItemUserTrade *parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
///////////////////
private:
	void _ResetCurrentNodeData(CItemUserTradeHelper* pItemDataHelper );
public:
	void findAndResetSubNodeData(CItemUserTradeHelper* pItemDataHelper );
	void appendChildByData(CItemUserTradeHelper* pItemDataHelper);
	void removeChildByData(CItemUserTradeHelper* pItemDataHelper);

	EItemType getItemType();
	QString getNodeKey();
private:
	/*
	if ItemDataType_ROOT itemData is column Name parentItem is NULL
	if ItemDataType_ITEM itemData is one row columns value parentItem have value
	*/	
	QMutex m_mutex_ItemData;
	QList<QVariant> m_ItemData;
	CItemUserTrade* m_pParentItem;
	EItemType m_nItemType;
private:
	//	QMutexLocker lock(&m_mutex_LstChildItems);	
	QMutex m_mutex_LstChildItems;
	QList<CItemUserTrade*> m_LstChildItems;
private:
	CItemUserTradeHelper* m_pItemHelper;
private:
	QString m_strNodeKey;//TradeUUID
};//


#endif//__CLASS_ITEM_USER_TRADE_HH__





