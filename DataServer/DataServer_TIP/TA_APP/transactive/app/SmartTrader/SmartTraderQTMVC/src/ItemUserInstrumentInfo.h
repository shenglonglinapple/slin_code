#ifndef __CLASS_ITEM_USER_INSTRUMENT_INFO_HH__
#define __CLASS_ITEM_USER_INSTRUMENT_INFO_HH__


#include <QtCore/QObject>
#include <QtCore/QMap>
#include <QtCore/QList>
#include <QtCore/QVariant>
#include <QtCore/QString>

#include "IconDelegate.h"


//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


class CUserInstrumentInfoHelper;


class CItemUserInstrumentInfo
{
public:
	enum enItemDataType
	{ 
		ItemDataType_NULL,
		ItemDataType_ROOT,
		ItemDataType_ITEM,

	};
public:
	CItemUserInstrumentInfo();
    CItemUserInstrumentInfo(const QList<QVariant> &data, CItemUserInstrumentInfo *parent = NULL);
    ~CItemUserInstrumentInfo();

public:
	void appendChild(CItemUserInstrumentInfo** ppItem);

	CItemUserInstrumentInfo* child(int row);

    int childCount() const;

    int columnCount() const;

    QVariant data(int column) const;

    int childNumber() const;

    CItemUserInstrumentInfo* parent();
public:
	bool insertChildren(int position, int count, int columns);
	bool insertColumns(int position, int columns);
	bool removeChildren(int position, int count);
	bool removeColumns(int position, int columns);
	bool setData(int column, const QVariant &dataValue);

public:
	int indexOfChildren(CItemUserInstrumentInfo* pChildrenItem) const;

public:
	void rootNodeRetColumnsName();
public:
	void appendChildByData(CUserInstrumentInfoHelper* pExchangeInfo);
	void removeChildByData(CUserInstrumentInfoHelper* pExchangeInfo);

	void resetChildrenData(CUserInstrumentInfoHelper* pExchangeInfo);
	void resetCurrentNodeData(CUserInstrumentInfoHelper* pExchangeInfo );
	void resetCurrentNodeDataDefultValue();

	void setDataType(enItemDataType nDataTypeExchange);
	enItemDataType getDataType();
	IconDelegate::enInstrumentPriceChange getInstrumentPriceChange();
	unsigned int getInstrumentID();
	QString getExchangeName();
	QString getInstrumentCode();
	float getLastPrice();
	unsigned int getHotInstrumentIDByCode(const QString& strInstrumentCode);

public:
	static void getLstClumnName(QList<QVariant>& lstClumnName );
	static void getLstClumnName(QStringList& strlstClumnName );

private:
	void _GetItemDataFromClass(CUserInstrumentInfoHelper* pData, QList<QVariant>& itemDataTmp);
private:
	CItemUserInstrumentInfo* m_pParentItem;
	QList<CItemUserInstrumentInfo*> m_LstChildItems;
    QList<QVariant> m_ItemData;
	int  m_ItemDataNum;
private:
	enItemDataType m_nDataType;
private:
	IconDelegate::enInstrumentPriceChange m_nInstrumentPriceChange;
	unsigned int m_nInstrumentID ;
	QString m_strExchangeName;
	QString m_strInstrumentCode;
	float m_fLastPrice;

};

//QT_END_NAMESPACE

#endif//__CLASS_ITEM_USER_INSTRUMENT_INFO_HH__







