#include "DataUserContract.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"
#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"

#include "QuotesInfo.h"
#include "TreeItemQuotes.h"

CDataUserContract* CDataUserContract::m_pInstance = 0;
QMutex CDataUserContract::m_mutexInstance;

CDataUserContract& CDataUserContract::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserContract();
	}
	return (*m_pInstance);
}

void CDataUserContract::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserContract::CDataUserContract()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();

	m_pQuotesInfo = NULL;
	m_pTreeItemQuotes_Root = NULL;
	_InitMVCDataForQuotes();
}

CDataUserContract::~CDataUserContract()
{
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}
	_UnInitMVCDataForQuotes();

}


void CDataUserContract::_InitMVCDataForQuotes()
{
	QMutexLocker lock(&m_mutexForNodeRootQuotes);	
	if (NULL != m_pTreeItemQuotes_Root)
	{
		delete m_pTreeItemQuotes_Root;
		m_pTreeItemQuotes_Root = NULL;
	}

	//root node save all column Names
	QList<QVariant> dataTreeItem;
	CTreeItemQuotes::getLstClumnName(dataTreeItem);
	m_pTreeItemQuotes_Root = new CTreeItemQuotes(dataTreeItem, NULL);
	m_pTreeItemQuotes_Root->setDataType(CTreeItemQuotes::ItemDataType_ROOT);
	m_pTreeItemQuotes_Root->rootNodeRetColumnsName();

	m_pQuotesInfo = new CQuotesInfo();


}
void CDataUserContract::_UnInitMVCDataForQuotes()
{
	QMutexLocker lock(&m_mutexForNodeRootQuotes);	

	if (NULL != m_pTreeItemQuotes_Root)
	{
		delete m_pTreeItemQuotes_Root;
		m_pTreeItemQuotes_Root = NULL;
	}

	if (NULL != m_pQuotesInfo)
	{
		delete m_pQuotesInfo;
		m_pQuotesInfo = NULL;
	}

}

CTreeItemQuotes* CDataUserContract::getRootHandle()
{
	QMutexLocker lock(&m_mutexForNodeRootQuotes);	

	return m_pTreeItemQuotes_Root;
}

void CDataUserContract::onMarketDataUpdate(const Instrument& instrument)
{

	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);	
		m_pQuotesInfo->setValue(instrument);
		m_pTreeItemQuotes_Root->resetChildrenData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
	}

}

void CDataUserContract::addByData(Instrument* pInstrument)
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;

	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);	
		m_pQuotesInfo->setValue(*pInstrument);

		strExchangeName = m_pQuotesInfo->m_strExchangeName.toStdString();
		strUnderlyingCode = m_pQuotesInfo->m_strUnderlyingCode.toStdString();
		strInstrumentCode = m_pQuotesInfo->m_strInstrumentCode.toStdString();
		MYLOG4CPP_DEBUG<<"slotAddContractToSmartQuotes add contract to SmartQuotes"
			<<" "<<"InstrumentID="<<m_pQuotesInfo->getInstrumentID()
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
	}
}

void CDataUserContract::removeByData( Instrument* pInstrument )
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;

	//remove
	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);
		m_pQuotesInfo->setValue(*pInstrument);
		strExchangeName = m_pQuotesInfo->m_strExchangeName.toStdString();
		strUnderlyingCode = m_pQuotesInfo->m_strUnderlyingCode.toStdString();
		strInstrumentCode = m_pQuotesInfo->m_strInstrumentCode.toStdString();

		MYLOG4CPP_DEBUG<<"CDataUserContract removeByData"
			<<" "<<"InstrumentID="<<m_pQuotesInfo->getInstrumentID()
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		m_pTreeItemQuotes_Root->removeChildByData(m_pQuotesInfo);
	}

}


void CDataUserContract::_Test()
{
	{
		QMutexLocker lock(&m_mutexForNodeRootQuotes);
		m_pQuotesInfo->setDefaultValue();
		m_pTreeItemQuotes_Root->appendChildByData(m_pQuotesInfo);
		m_pTreeItemQuotes_Root->rootNodeRetColumnsName();
	}
}



