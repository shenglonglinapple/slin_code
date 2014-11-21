#ifndef __CLASS_ITEM_INSTRUMENT_INFO_HH__
#define __CLASS_ITEM_INSTRUMENT_INFO_HH__


#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>





class CInstrumentInfoHelper;

class CItemInstrumentInfo
{
public:
	enum enDataTypeContract 
	{ 
		DataTypeContract_NULL,
		DataTypeContract_Root,
		DataTypeContract_ExchangeName,
		DataTypeContract_UnderlyingCode,
		DataTypeContract_InstrumentCode,
	};

public:
	CItemInstrumentInfo();
    CItemInstrumentInfo(const QList<QVariant> &data, CItemInstrumentInfo *parent = NULL);
    ~CItemInstrumentInfo();

public:
	void appendChild(const QString& strMapKey, CItemInstrumentInfo** ppItem);
	CItemInstrumentInfo* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    CItemInstrumentInfo* parent();
public:
	int indexOfChildren(CItemInstrumentInfo* pChildrenItem) const;
	void appendThreeChild(const CInstrumentInfoHelper* pExchangeInfo);
	void appendChildUnderlyingCode( const CInstrumentInfoHelper* pExchangeInfo );
	void appendChildInstrumentCode( const CInstrumentInfoHelper* pExchangeInfo );
	void setDataType(enDataTypeContract nDataTypeExchange);
	CItemInstrumentInfo::enDataTypeContract getDataType();
	void setInstrumentID(unsigned int nInstrumentID);
	unsigned int getInstrumentID();

private:
	void _AppendChildExchangeName( const CInstrumentInfoHelper* pExchangeInfo );

public:
	bool removeChildren(int position);
	bool removeChildrenByData(const CInstrumentInfoHelper* pExchangeInfo);
private:
	//use map for sort string
	QMap<QString, CItemInstrumentInfo*> m_MapStringChildren;
    QList<QVariant> m_ItemData;
    CItemInstrumentInfo* m_pParentItem;
private:
	enDataTypeContract m_nDataTypeExchange;
	unsigned int m_nInstrumentID ;
};




#endif//__CLASS_ITEM_INSTRUMENT_INFO_HH__
