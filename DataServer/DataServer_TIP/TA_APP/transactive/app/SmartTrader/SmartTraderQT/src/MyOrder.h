//#pragma once
#ifndef __CLASS__MY_ORDER_H__
#define __CLASS__MY_ORDER_H__


#include <list>
#include "Order.h"

class CMyOrder
{
public:
	CMyOrder(	CMyAccount &account,
			const Instrument &Instrument, 
			CMyOrder::Side side,
			int quantity,
			CMyOrder::OrderType orderType,
			float price = 0);

	CMyOrder();
	CMyOrder(const CMyOrder &order);
	CMyOrder &operator=(const CMyOrder &order);
	
	virtual ~CMyOrder(void);

	/// Clone the order fields including the snapshots
	void clone(CMyOrder &order) const;

    bool isValid() const;
    bool isInvalid() const;
    bool isWorking() const;
    bool isCompleted() const;
    bool isCancelable() const;

    bool isAlgoOrder() const;
    bool isExitOrder() const;
    bool isEntryOrder() const;

	int getCumQty() const;
	int getLastQty() const;
	int getOrderQty() const;
	int getLeavesQty() const;

	float getPrice() const;
	float getPrice2() const;
	float getLastPx() const;
	float getAvgPrice() const;

	CMyOrder::Side getSide() const;
	CMyOrder::OrderType getOrderType() const;
	CMyOrder::OrderStatus getOrderStatus() const;

	int getRejectReason() const;
	const std::string & getText() const;
    const std::string & getExecID() const;

	unsigned int getUserID() const;
	unsigned int getClOrdID() const;
	unsigned int getOrderID() const;
	unsigned int getAccountID() const;
	unsigned int getStrategyID() const;
	unsigned int getInstrumentID() const;
	unsigned int getTransactTime() const;
    unsigned int getLocalTransactTime() const;

	void setPrice(double price);
	void setPrice2(double price2);
	void setOrderQty(int quantity);
	void setLeavesQty(int quantity);
	void setOrderStatus(CMyOrder::OrderStatus status);

	void setUserID(unsigned int id);
	void setClOrdID(unsigned int id);
	void setOrderID(unsigned int id);
	void setStrategyID(unsigned int id);
	void setTransactTime(unsigned int timestamp);

	void setText(const std::string &text);
	void setRejectReason(int rejectReason);
    void setExecID(const std::string &execID);

    void cancel();
	void onRejected();
	void onCancelled();
    void onFill(const Trade &trade);
	void onBust(float lastPx, int lastVol);

	CMyAccount & getAccount() const;
	const Instrument & getInstrument() const;

	void setOrderInfoMask(unsigned int masks);
	unsigned int getOrderInfoMasks() const;

	double getFees() const;
	double getMargin() const;
	double updateFees(double fees);
	double updateMargin(double margin);

    void clear();
	void createSnapshot();
	const std::list<CMyOrder> & getChangeHistory() const;
    const std::list<Trade> & getTransactions() const;

    std::string getReservedData(int slotIndex) const;
    void setReservedData(int slotIndex, const std::string &data);
    const std::vector<std::string> &getReservedData() const;
private:
	CMyOrder::Side m_side;
	int m_cumQty;
	int m_lastQty;
	int m_orderQty;
	int m_leavesQty;
	int m_rejectReason;

	float m_price;
	float m_price2;
	float m_lastPx;
	float m_avgPrice;
	CMyOrder::OrderType m_orderType;
	CMyOrder::OrderStatus m_orderStatus;

	unsigned int m_userID;
	unsigned int m_orderID;
	unsigned int m_clOrdID;
	unsigned int m_strategyID;
	unsigned int m_transactTime;
	unsigned int m_orderInfoMasks;
    unsigned int m_localTransactTime;

	double m_fees;
	double m_margin;

	std::string m_text;
    std::string m_execID;

	CMyAccount* m_account;
	const Instrument * m_instrument;

	std::list<CMyOrder> m_snapshots;
    std::list<Trade> m_transactions;
    std::vector<std::string> m_reservedData;
};

#endif __CLASS__MY_ORDER_H__



