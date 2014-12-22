#pragma once

#include <vector>
#include <memory>
#include "Position.h"

class Instrument;
class CMyAccount;
class Trade;

class SEAPI CMyPosition
{
public:
	enum CloseStrategy 
	{
		MARKET_ORDER,
		BEST_SAME_SIDE,
		BEST_OPPOSITE_SIDE,
	};

	enum Type 
	{
		NET = 0,
		LONG = 1,
		SHORT = 2,
		NEW_LONG = 3,
		NEW_SHORT = 4,
		OLD_LONG = 5,
		OLD_SHORT = 6,
	};

	virtual ~CMyPosition(void);
	virtual double getFxRate() const;
	virtual CMyAccount & getAccount() const = 0;
	virtual const Instrument &getInstrument() const = 0;
    virtual std::auto_ptr<CMyPosition> duplicate() const = 0;

	virtual void dump() = 0;
	virtual void onFill(const Trade & fill) = 0;
	virtual void closePosition(CloseStrategy strategy) = 0;

	virtual int getQty() const = 0;
	virtual int getLongQty() const = 0;
	virtual int getShortQty() const = 0; 

	virtual double getAvgPrice() const = 0;
	virtual double getMarketPrice() const = 0;
	virtual double getLongAvgPrice() const = 0;
	virtual double getShortAvgPrice() const = 0;

	virtual double getInitialEquity() const = 0;
	virtual double getCurrentEquity() const = 0;
	virtual double getTotalProfitLoss() const = 0;
	virtual double getRealizedProfitLoss() const = 0;
	virtual double getUnRealizedProfitLoss() const = 0;

	virtual int getSubPositionNumber() const = 0;
	virtual CMyPosition * getSubPosition(int index) const = 0;

	virtual int getPositionType() const = 0;

    virtual double getFees() const = 0;
    virtual double getMargin() const = 0;

	virtual void addFees(double feeDelta) = 0;
	virtual void addMargin(double marginDelta) = 0;
};
