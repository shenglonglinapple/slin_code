#pragma once
#include <string>

class CMyAccount;
class Instrument;

#ifdef __linux__
	typedef long int64 ;
#else 
	typedef long long int64 ;
#endif

class SEAPI CMyTrade
{
public:
	CMyTrade();
	CMyTrade(	const Instrument &instrument,
			const CMyAccount &account,
			const std::string &execID, 
			long long transactTime, 
			int qty, double price,
			unsigned int orderInfoMask);

	virtual ~CMyTrade(void);

	virtual int getQty() const;
	virtual double getPrice() const;
	virtual double getAmount() const;
	virtual const CMyAccount &getAccount() const;
	virtual int64 getTransactTime() const;
	virtual const char * getExecutionID() const;
	virtual const Instrument &getInstrument() const;

	virtual int getStrategyID() const;
	virtual void setStrategyID(int strategyID);
	virtual int getPositionType() const;

    virtual bool algoTrade() const;
    virtual bool exitTrade() const;
    virtual bool entryTrade() const;
private:
	int m_qty;
	double m_price;
	int m_strategyID;
	int64 m_transactTime;
	unsigned int m_orderMasks;
	std::string m_executionID;
	const CMyAccount * m_account;
	const Instrument *m_instrument;
};
