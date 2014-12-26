#ifndef __CLASS_DATA_USER_ORDER__HH__
#define __CLASS_DATA_USER_ORDER__HH__

#include <QtCore/QString>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "OrderData.h"

class CItemUserOrder;
class CItemUserOrderHelper;

class CDataUserOrder
{
public:
	static CDataUserOrder& getInstance();
	static void removeInstance();

private:
	static CDataUserOrder* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CDataUserOrder(void);
	~CDataUserOrder(void);
public:
	CItemUserOrder*  getRootItem();
	void addOrUpdate(const COrderData& order);

private:
	QMutex m_mutex_ItemUserInstrument_Root;
	CItemUserOrder* m_pItemUserOrder_Root;
	CItemUserOrderHelper* m_pItemUserOrdertHelper;
};

//QT_END_NAMESPACE

#endif //__CLASS_DATA_USER_ORDER__HH__


