#ifndef __CLASS_CONTRACT_INFO_HH__
#define __CLASS_CONTRACT_INFO_HH__



//qt sys
#include <QtCore/QChar>
#include <QtCore/QString>

#include "Instrument.h"

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CContractInfo 
{ 
public: 
	CContractInfo();

	virtual ~CContractInfo(); 
	CContractInfo& operator=(const CContractInfo& exchangeParam);

public:
	void setValue( const Instrument &instrument);
	void setValue(
		unsigned int nInstrumentID,
		const std::string& strExchangeName, 
		const std::string& strUnderlyingCode, 
		const std::string& strInstrumentCode);
	void setDefaultValue();

	QString getExchangeName() const;
	QString getUnderlyingCode() const;
	QString getInstrumentCode() const;
	unsigned int getInstrumentID() const;

	void logInfo(const QString& strLogInfo) const;
private:
	QString m_strExchangeName;
	QString m_strUnderlyingCode;
	QString m_strInstrumentCode;
	unsigned int m_nInstrumentID;

}; 


//QT_END_NAMESPACE



#endif//__CLASS_CONTRACT_INFO_HH__



