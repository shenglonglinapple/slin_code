#ifndef __CLASS_ITEM_USER_INSTRUMENT_HH__
#define __CLASS_ITEM_USER_INSTRUMENT_HH__


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

class CItemUserInstrumentHelper;

class CItemUserInstrument
{
public:
	enum EItemType
	{ 
		ItemType_ROOT,
		ItemType_ITEM,
	};
public:
	/*init item ROOT*/
	CItemUserInstrument();
	/*init item ITEM*/
	CItemUserInstrument(QList<QVariant>& ItemData, CItemUserInstrument *parent);
	~CItemUserInstrument();

	void appendChild(CItemUserInstrument** ppItem);
	CItemUserInstrument *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CItemUserInstrument *parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
///////////////////
public:
	void findAndResetSubNodeData(CItemUserInstrumentHelper* pItemUserInstrumentHelper );
	void _ResetCurrentNodeData(CItemUserInstrumentHelper* pItemUserInstrumentHelper );
	void appendChildByData(CItemUserInstrumentHelper* pItemUserInstrumentHelper);
	void removeChildByData(CItemUserInstrumentHelper* pItemUserInstrumentHelper);

	EItemType getItemType();
	unsigned int getNodeKey();
private:
	/*
	if ItemDataType_ROOT itemData is column Name parentItem is NULL
	if ItemDataType_ITEM itemData is one row columns value parentItem have value
	*/	
	QMutex m_mutex_ItemData;
	QList<QVariant> m_ItemData;
	CItemUserInstrument* m_pParentItem;
	EItemType m_nItemType;
private:
	//	QMutexLocker lock(&m_mutex_LstChildItems);	
	QMutex m_mutex_LstChildItems;
	QList<CItemUserInstrument*> m_LstChildItems;
private:
	CItemUserInstrumentHelper* m_pItemUserInstrumentHelper;
private:
	unsigned int m_nNodeKey;
};//CItemUserInstrument


#endif//__CLASS_ITEM_USER_INSTRUMENT_HH__





