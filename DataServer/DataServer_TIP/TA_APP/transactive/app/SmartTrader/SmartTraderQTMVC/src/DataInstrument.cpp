#include "DataInstrument.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"

#include "ProjectLogHelper.h"

#include "InstrumentInfoHelper.h"
#include "ItemInstrumentInfo.h"

#include "Log4cppLogger.h"



CDataInstrument* CDataInstrument::m_pInstance = 0;
QMutex CDataInstrument::m_mutexInstance;

CDataInstrument& CDataInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataInstrument();
	}
	return (*m_pInstance);
}

void CDataInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataInstrument::CDataInstrument()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();

	m_pContractInfo = NULL;
	m_pTreeItemContract_Root = NULL;
	_InitMVCDataForContract();

}

CDataInstrument::~CDataInstrument()
{
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}

	_UnInitMVCDataForContract();
}



void CDataInstrument::_InitMVCDataForContract()
{
	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		if (NULL != m_pTreeItemContract_Root)
		{
			delete m_pTreeItemContract_Root;
			m_pTreeItemContract_Root = NULL;
		}

		QList<QVariant> dataColumn;
		QString strMapKey;
		dataColumn.clear();
		dataColumn.push_back("DataType_Root");
		m_pTreeItemContract_Root = new CItemInstrumentInfo(dataColumn, NULL);
		m_pTreeItemContract_Root->setDataType(CItemInstrumentInfo::DataTypeContract_Root);
		m_pTreeItemContract_Root->setInstrumentID(0);
		m_pContractInfo = new CInstrumentInfoHelper();
	}




}
void CDataInstrument::_UnInitMVCDataForContract()
{
	QMutexLocker lock(&m_mutexForNodeRootContract);	

	if (NULL != m_pTreeItemContract_Root)
	{
		delete m_pTreeItemContract_Root;
		m_pTreeItemContract_Root = NULL;
	}

	if (NULL != m_pContractInfo)
	{
		delete m_pContractInfo;
		m_pContractInfo = NULL;
	}

}



void CDataInstrument::onInstrumentDownloaded( const Instrument& instrument )
{
	Instrument* pGetInstrument = NULL;
	unsigned int nGetInstrumentID = 0;

	nGetInstrumentID = instrument.getInstrumentID();
	pGetInstrument = instrument.getInstrument(nGetInstrumentID);

	addByData(pGetInstrument);
}


void CDataInstrument::addByData(Instrument* pInstrument)
{
	//add
	{		
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		m_pContractInfo->setValue(*pInstrument);

		MYLOG4CPP_DEBUG<<"CDataContract addByData CContractInfo"
			<<" "<<"InstrumentID="<<m_pContractInfo->getInstrumentID()
			<<" "<<"ExchangeName="<<m_pContractInfo->getExchangeName().toStdString()
			<<" "<<"strInstrumentCode="<<m_pContractInfo->getInstrumentCode().toStdString();

		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);
	}
}


void CDataInstrument::removeByData(Instrument* pInstrument)
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;

	{
		//find ok
		m_pContractInfo->setValue(*pInstrument);
		strExchangeName = m_pContractInfo->getExchangeName().toStdString();
		strUnderlyingCode = m_pContractInfo->getUnderlyingCode().toStdString();
		strInstrumentCode = m_pContractInfo->getInstrumentCode().toStdString();
		MYLOG4CPP_DEBUG<<"CDataContract removeByData"
			<<" "<<"InstrumentID="<<m_pContractInfo->getInstrumentID()
			<<" "<<"ExchangeName="<<strExchangeName
			<<" "<<"strInstrumentCode="<<strInstrumentCode;

		//remove nInstrumentID from m_pTreeItemContract_Root
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		m_pTreeItemContract_Root->removeChildrenByData(m_pContractInfo);
	}//if
}

CItemInstrumentInfo* CDataInstrument::getRootHandle()
{
	QMutexLocker lock(&m_mutexForNodeRootContract);	

	return m_pTreeItemContract_Root;
}



void CDataInstrument::_Test()
{
	{
		QMutexLocker lock(&m_mutexForNodeRootContract);	
		m_pContractInfo->setDefaultValue();
		m_pTreeItemContract_Root->appendThreeChild(m_pContractInfo);
	}
}

