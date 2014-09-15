#ifndef __CLASS_TREE_ITEM_CONTRACT_HH__
#define __CLASS_TREE_ITEM_CONTRACT_HH__


#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>



//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CContractInfo;

class CTreeItemContract
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
	CTreeItemContract();
    CTreeItemContract(const QList<QVariant> &data, CTreeItemContract *parent = NULL);
    ~CTreeItemContract();

public:
	void appendChild(const QString& strMapKey, CTreeItemContract** ppItem);
	CTreeItemContract* child(int row);
    int childCount() const;
    int columnCount() const;
    QVariant data(int column) const;
    int row() const;
    CTreeItemContract* parent();
public:
	int indexOfChildren(CTreeItemContract* pChildrenItem) const;
	void appendThreeChild(const CContractInfo* pExchangeInfo);
	void appendChildUnderlyingCode( const CContractInfo* pExchangeInfo );
	void appendChildInstrumentCode( const CContractInfo* pExchangeInfo );
	void setDataType(enDataTypeContract nDataTypeExchange);
	CTreeItemContract::enDataTypeContract getDataType();
	void setInstrumentID(unsigned int nInstrumentID);
	unsigned int getInstrumentID();

private:
	void _AppendChildExchangeName( const CContractInfo* pExchangeInfo );

public:
	bool removeChildren(int position);
	bool removeChildrenByData(const CContractInfo* pExchangeInfo);
private:
	//use map for sort string
	QMap<QString, CTreeItemContract*> m_MapStringChildren;
    QList<QVariant> m_ItemData;
    CTreeItemContract* m_pParentItem;
private:
	enDataTypeContract m_nDataTypeExchange;
	unsigned int m_nInstrumentID ;
};


//QT_END_NAMESPACE

#endif//__CLASS_TREE_ITEM_CONTRACT_HH__
