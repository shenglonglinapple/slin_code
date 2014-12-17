#ifndef __CLASS_ITEM_WAITING_INSTRUMENT_HH__
#define __CLASS_ITEM_WAITING_INSTRUMENT_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>
#include <QtCore/QStringList>

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

class CItemWaitingInstrumentHelper;

class CItemWaitingInstrument
{
public:
	enum EItemType
	{ 
		ItemType_ROOT,
		ItemType_ITEM1_ExchangeName,
		ItemType_ITEM2_UnderlyingCode,
		ItemType_ITEM3_InstrumentCode,
	};
public:
	/*init item ROOT*/
	CItemWaitingInstrument();
	/*init item ITEM*/
	CItemWaitingInstrument(QList<QVariant>& ItemData, CItemWaitingInstrument *parent);
	~CItemWaitingInstrument();

	void appendChild(CItemWaitingInstrument** ppItem);
	CItemWaitingInstrument *child(int number);
	int childCount() const;
	int columnCount() const;
	QVariant data(int column) const;
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	CItemWaitingInstrument *parent();
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	int childNumber() const;
	bool setData(int column, const QVariant &value);
///////////////////
public:
	void AnalysisAndAppendChild( CItemWaitingInstrumentHelper* pHelper);
	void resetCurrentNodeData(CItemWaitingInstrumentHelper* pHelper );
	void appendChildByData(CItemWaitingInstrumentHelper* pHelper);
	EItemType getItemType();
	void setItemType(EItemType nType);
	unsigned int getNodeKey();
	void AnalysisAndRemoveChild(CItemWaitingInstrumentHelper* pHelper);
private:
	/*
	if ItemDataType_ROOT itemData is column Name parentItem is NULL
	if ItemDataType_ITEM itemData is one row columns value parentItem have value
	*/
	QList<QVariant> m_ItemData;
	CItemWaitingInstrument* m_pParentItem;
	EItemType m_nItemType;
private:
	QList<CItemWaitingInstrument*> m_LstChildItems;
private:
	CItemWaitingInstrumentHelper* m_pItemWaitingInstrumentHelper;
private:
	unsigned int m_nNodeKey;
};//CItemWaitingInstrument


#endif//__CLASS_ITEM_USER_INSTRUMENT_HH__





