//#pragma once
#ifndef __CLASS__MY_ACCOUNT_H__
#define __CLASS__MY_ACCOUNT_H__

#include "API.h"
#include "Position.h"

#include <list>
#include <string>

class CMyOrder;
class Currency;
class Instrument;

class SEAPI CMyAccount
{
public:
	static std::list<CMyAccount*> getAccountList();
	static CMyAccount * getAccount(unsigned int accountID);
	static CMyAccount * getAccount(const std::string &accountCode);
	virtual ~CMyAccount(void);

	virtual int getAccountID() const = 0;   
	virtual const char * getAccountCode() const = 0;
	virtual const Currency & getCurrency() const = 0;

	virtual double getEquity() const = 0;
	virtual double getInitialEquity() const = 0;
	virtual double getTotalProfitLoss() const = 0;
	virtual double getRealizedProfitLoss() const = 0;
	virtual double getUnRealizedProfitLoss() const = 0;

	virtual std::list<CMyOrder *> getOrders() const = 0;
	virtual std::list<CMyPosition *> getPositions() const = 0;
	virtual CMyPosition * getPosition(const Instrument &instrument, int positionType = CMyPosition::NET) = 0;
	virtual void closeAllPosition(CMyPosition::CloseStrategy strategy) = 0;

    virtual void cancelOrder(unsigned int orderID) = 0;

    virtual void admendOrderVolume(unsigned int orderID, int newQty) = 0;
    virtual void admendOrderPrice(unsigned int orderID, double price) = 0;


    /// Place a buy market order against specific instrument
    virtual const CMyOrder & buyMarket(const Instrument &instrument, int quantity , int strategyID = 0, int masks = 0) = 0;

    /// Place a sell market order against specific instrument
    virtual const CMyOrder & sellMarket(const Instrument &instrument, int quantity , int strategyID = 0, int masks = 0) = 0;

    /// Place a buy limit order against specific instrument
    virtual const CMyOrder & buyLimit(const Instrument &instrument, double price, int quantity, int strategyID = 0, int masks = 0) = 0;

    /// Place a sell limit order against specific instrument
    virtual const CMyOrder & sellLimit(const Instrument &instrument, double price, int quantity , int strategyID = 0, int masks = 0) = 0;

    /// Place a buy stop order against specific instrument
    virtual const CMyOrder & buyStop(const Instrument &instrument, double stopPx, int quantity , int strategyID = 0, int masks = 0) = 0;

    /// Place a sell stop order against specific instrument
    virtual const CMyOrder & sellStop(const Instrument &instrument, double stopPx, int quantity , int strategyID = 0, int masks = 0) = 0;

    virtual double getFees() const = 0;
    virtual double getMargin() const = 0;

    virtual void addFees(double feeDelta) = 0;
    virtual void addMargin(double marginDelta) = 0;
};
