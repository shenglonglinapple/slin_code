#ifndef __CLASS_ITEM_USER_INSTRUMENT_HELPER_HH__
#define __CLASS_ITEM_USER_INSTRUMENT_HELPER_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>
#include <QtCore/QVariant>
#include <QtCore/QStringList>

#include "Instrument.h"
#include "MyInstrument.h"


class CItemUserInstrumentHelper 
{ 
public: 
	CItemUserInstrumentHelper();

	virtual ~CItemUserInstrumentHelper(); 
	CItemUserInstrumentHelper& operator=(const CItemUserInstrumentHelper& objCopy);

public:
	void setValue( const Instrument &instrument);
	void setValue( const CMyInstrument &instrument);

public:
	unsigned int getInstrumentID() const;
	QString getInstrumentCode() const;

	void logInfo(const std::string& file, int line, const QString& strLogInfo);
public:
	QVariant getColumnValueByName(const QString& strName);
public:
	void getLstClumnName(QStringList& lstClumnName );
	void getLstClumnName(QList<QVariant>& lstClumnName);
	void getItemNodeData(QList<QVariant>& itemDataTmp);

private:
	void _ClearData();
public:
	unsigned int m_nInstrumentID;
	QString m_strInstrumentCode;//Contract Name//InstrumentCode//合约名称

	QString m_strExchangeName;//Exchange Name//ExchangeName//交易所
	QString m_strUnderlyingCode;

	float m_fLastTradePrice;
	unsigned int m_nUpdateTime;//更新时间
	QString m_strUpdateTime;

}; 


//QT_END_NAMESPACE


#endif//__CLASS_ITEM_USER_INSTRUMENT_HELPER_HH__



