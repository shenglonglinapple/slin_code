#ifndef __CLASS_TREE_ITEM_QUOTES_HH__
#define __CLASS_TREE_ITEM_QUOTES_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "IconDelegate.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CQuotesInfo;


class CTreeItemQuotes
{
public:
	enum enDataTypeSmartQuotes
	{ 
		DataTypeSmartQuotes_NULL,
		DataTypeSmartQuotes_Root,
		DataTypeSmartQuotes_Instrument,

	};
public:
	CTreeItemQuotes();
    CTreeItemQuotes(const QList<QVariant> &data, CTreeItemQuotes *parent = NULL);
    ~CTreeItemQuotes();

public:
	void appendChild(CTreeItemQuotes** ppItem);

	CTreeItemQuotes* child(int row);

    int childCount() const;

    int columnCount() const;

    QVariant data(int column) const;

    int childNumber() const;

    CTreeItemQuotes* parent();
public:
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	bool setData(int column, const QVariant &dataValue);

public:
	int indexOfChildren(CTreeItemQuotes* pChildrenItem) const;

public:
	void rootNodeRetColumnsName();
public:
	void appendChildByData(CQuotesInfo* pExchangeInfo);
	void resetChildrenData(CQuotesInfo* pExchangeInfo);
	void resetCurrentNodeData(CQuotesInfo* pExchangeInfo );
	void resetCurrentNodeDataDefultValue();

	void setDataType(enDataTypeSmartQuotes nDataTypeExchange);
	enDataTypeSmartQuotes getDataType();
	IconDelegate::enInstrumentPriceChange getInstrumentPriceChange();
	unsigned int getInstrumentID();
	QString getInstrumentCode();
	float getLastPrice();

public:
	static void getLstClumnName(QList<QVariant>& lstClumnName );
	static void getLstClumnName(QStringList& strlstClumnName );

private:
	void _GetItemDataFromClass(CQuotesInfo* pExchangeInfo, QList<QVariant>& itemDataTmp);
private:
	CTreeItemQuotes* m_pParentItem;
	QList<CTreeItemQuotes*> m_LstChildItems;
    QList<QVariant> m_ItemData;
	int  m_ItemDataNum;
private:
	enDataTypeSmartQuotes m_nDataType;
private:
	IconDelegate::enInstrumentPriceChange m_nInstrumentPriceChange;
	unsigned int m_nInstrumentID ;
	QString m_strInstrumentCode;
	float m_fLastPrice;

};

//QT_END_NAMESPACE

#endif//__CLASS_TREE_ITEM_CONTRACT_HH__







