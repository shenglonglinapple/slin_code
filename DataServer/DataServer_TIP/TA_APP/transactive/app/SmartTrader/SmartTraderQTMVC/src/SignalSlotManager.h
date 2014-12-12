#ifndef __CLASS__SIGNALE_SLOT_MANAGER_H__
#define __CLASS__SIGNALE_SLOT_MANAGER_H__


#include <QtCore/QObject>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QString>



//Data
class CUserOrderInfo;
class CItemInstrumentInfo;
class CItemUserInstrumentInfo;
class CTreeItemOrder;
class CHistoryQutoes;
class CClientLoginParam;
class CClientDataManagerWorker;

//UI
class CClientLoginDialog;
class CMidSubWidget;
class CBottomDockWidget;
class CLeftDockWidget;
class CUserInstrumentInfoView;
class CCreateNewOrderDialog;
class CInstrumentInfoView;



class CSignalSlotManager : public QObject
{
	Q_OBJECT
public:
	static CSignalSlotManager& getInstance();
	static void removeInstance();
private:
	static CSignalSlotManager* m_pInstance;
	static QMutex m_mutexInstance;
private:
	CSignalSlotManager(QWidget* parent = 0);
	~CSignalSlotManager();
//////////////////////////////////////////////////////
private:
	CClientLoginDialog* m_pSignal_ClientLoginParamChanged;
	CClientDataManagerWorker* m_pSlot_ClientLoginParamChanged;
public:
	void setSignalSlot_ClientLoginParamChanged(CClientLoginDialog* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	//login in
	void slotClientLoginParamChanged(CClientLoginParam* pParam);
signals:
	//login in
	void signalClientLoginParamChanged(CClientLoginParam* pParam);
public:
	void emit_signalClientLoginParamChanged(CClientLoginParam* pParam);
//////////////////////////////////////////////////////	

	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_HistoryDataChanged;
	CMidSubWidget* m_pSlot_HistoryDataChanged;
public:
	void setSignalSlot_HistoryDataChanged(CClientDataManagerWorker* pSignal, CMidSubWidget* pSlot);
public slots:
	void slotHistoryDataChanged( unsigned int nInstrumentID );
signals:
	void signalHistoryDataChanged(unsigned int nParam);
public:
	void emit_signalHistoryDataChanged( unsigned int nInstrumentID);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_OrderInfoChanged;
	CBottomDockWidget* m_pSlot_OrderInfoChanged;
public:
	void setSignalSlot_OrderInfoChanged(CClientDataManagerWorker* pSignal, CBottomDockWidget* pSlot);
public slots:
	void slotOrderInfoChanged(CTreeItemOrder* pParam);
signals:
	void signalOrderInfoChanged(CTreeItemOrder* pParam);
public:
	void emit_signalOrderInfoChanged(CTreeItemOrder* pParam);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_UserInstrumentInfoChanged;
	CLeftDockWidget* m_pSlot_UserInstrumentInfoChanged;
public:
	void setSignalSlot_UserInstrumentInfoChanged(CClientDataManagerWorker* pSignal, CLeftDockWidget* pSlot);
public slots:
	void slotUserInstrumentInfoChanged(CItemUserInstrumentInfo* pParam);
signals:
	void signalUserInstrumentInfoChanged(CItemUserInstrumentInfo* pParam);
public:
	void emit_signalUserInstrumentInfoChanged(CItemUserInstrumentInfo* pParam);
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CUserInstrumentInfoView* m_pSignal_UserInstrumentViewColumnsChanged;
	CClientDataManagerWorker* m_pSlot_UserInstrumentViewColumnsChanged;
public:
	void setSignalSlot_UserInstrumentViewColumnsChanged(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotUserInstrumentViewColumnsChanged();
signals:
	void signalUserInstrumentViewColumnsChanged();
public:
	void emit_signalUserInstrumentViewColumnsChanged();
	//////////////////////////////////////////////////////	


	//////////////////////////////////////////////////////
private:
	CUserInstrumentInfoView* m_pSignal_RemoveUserInstrument;
	CClientDataManagerWorker* m_pSlot_RemoveUserInstrument;
public:
	void setSignalSlot_RemoveUserInstrument(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotRemoveUserInstrument(unsigned int nParam);
signals:
	void signalRemoveUserInstrument(unsigned int nParam);
public:
	void emit_signalRemoveUserInstrument(unsigned int nParam);
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CUserInstrumentInfoView* m_pSignal_InstrumentViewResetData;
	CClientDataManagerWorker* m_pSlot_InstrumentViewResetData;
public:
	void setSignalSlot_InstrumentViewResetData(CUserInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotInstrumentViewResetData();
signals:
	void signalInstrumentViewResetData();
public:
	void emit_signalInstrumentViewResetData();
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CCreateNewOrderDialog* m_pSignal_NewOrder;
	CClientDataManagerWorker* m_pSlot_NewOrder;
public:
	void setSignalSlot_NewOrder(CCreateNewOrderDialog* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotNewOrder(CUserOrderInfo* pParam);
signals:
	void signalNewOrder(CUserOrderInfo* pParam);
public:
	void emit_signalNewOrder(CUserOrderInfo* pParam);
	//////////////////////////////////////////////////////	



	//////////////////////////////////////////////////////
private:
	CInstrumentInfoView* m_pSignal_AddUserInstrument;
	CClientDataManagerWorker* m_pSlot_AddUserInstrument;
public:
	void setSignalSlot_AddUserInstrument(CInstrumentInfoView* pSignal, CClientDataManagerWorker* pSlot);
public slots:
	void slotAddUserInstrument(unsigned int nParam);
signals:
	void signalAddUserInstrument(unsigned int nParam);
public:
	void emit_signalAddUserInstrument(unsigned int nParam);
	//////////////////////////////////////////////////////	




	//////////////////////////////////////////////////////
private:
	CClientDataManagerWorker* m_pSignal_InstrumentInfoChanged;
	CInstrumentInfoView* m_pSlot_InstrumentInfoChanged;
public:
	void setSignalSlot_InstrumentInfoChanged(CClientDataManagerWorker* pSignal, CInstrumentInfoView* pSlot);
public slots:
	void slotInstrumentInfoChanged(CItemInstrumentInfo* pParam);
signals:
	void signalInstrumentInfoChanged(CItemInstrumentInfo* pParam);
public:
	void emit_signalInstrumentInfoChanged(CItemInstrumentInfo* pParam);
	//////////////////////////////////////////////////////	





};

//QT_END_NAMESPACE

#endif//__CLASS__SIGNALE_SLOT_MANAGER_H__
