#include "DataTotalInstrument.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include "Instrument.h"
#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"


CDataTotalInstrument* CDataTotalInstrument::m_pInstance = 0;
QMutex CDataTotalInstrument::m_mutexInstance;

CDataTotalInstrument& CDataTotalInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataTotalInstrument();
	}
	return (*m_pInstance);
}

void CDataTotalInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataTotalInstrument::CDataTotalInstrument()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();
}

CDataTotalInstrument::~CDataTotalInstrument()
{
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}
}



void CDataTotalInstrument::onInstrumentDownloaded( const Instrument& instrument )
{
	Instrument* pGetInstrument = NULL;
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		nGetInstrumentID = instrument.getInstrumentID();
		pGetInstrument = instrument.getInstrument(nGetInstrumentID);
		m_MapInstrumentIDData.insert(nGetInstrumentID, pGetInstrument);
		MYLOG4CPP_DEBUG<<"CDataTotalInstrument"
			<<" "<<"onInstrumentDownloaded"
			<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
		strLogInfo = "onInstrumentDownloaded";
		m_pProjectLogHelper->log_Instrument_info(LOG4CPPFLInfo, strLogInfo, instrument);
	}

}//onInstrumentDownloaded



void CDataTotalInstrument::onMarketDataUpdate(const Instrument& instrument)
{

	Instrument* pInstrumentGet = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;
	std::string strLogInfo;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);

		if (false == m_MapInstrumentIDData.contains(instrument.getInstrumentID()))
		{
			MYLOG4CPP_ERROR<<"not find nInstrumentID="<<instrument.getInstrumentID()
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			//TODO.
			return;
		}

		iterFind = m_MapInstrumentIDData.find(instrument.getInstrumentID());
		//find ok
		pInstrumentGet = iterFind.value();
		*pInstrumentGet = instrument;//reset value
		MYLOG4CPP_DEBUG<<"onMarketDataUpdate reset contract to SmartQuotes"
			<<" "<<"strInstrumentCode="<<instrument.getInstrumentCode()
			<<" "<<"getTickSize="<<instrument.getTickSize();
		strLogInfo = "onMarketDataUpdate reset contract to SmartQuotes";
		m_pProjectLogHelper->log_Instrument_info(LOG4CPPFLInfo, strLogInfo, instrument);
	}

}//onMarketDataUpdate

Instrument* CDataTotalInstrument::findInstrumentByID(unsigned int nInstrumentID)
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	Instrument* pInstrumentRef = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterFind;

	{
		//check in total list
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(nInstrumentID))
		{
			MYLOG4CPP_ERROR<<"not find nInstrumentID="<<nInstrumentID
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			//TODO.
			pInstrumentRef = NULL;
			return pInstrumentRef;
		}
		iterFind = m_MapInstrumentIDData.find(nInstrumentID);

		//find ok
		pInstrumentRef = iterFind.value();
	}


	return pInstrumentRef;
}



void CDataTotalInstrument::_Test()
{
	Instrument* pGetInstrument = NULL;
	unsigned int nGetInstrumentID = 0;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		nGetInstrumentID = 1;
		pGetInstrument = NULL;
		m_MapInstrumentIDData.insert(nGetInstrumentID, pGetInstrument);
		MYLOG4CPP_DEBUG<<"CClientDataManagerWorker"
			<<" "<<"_Test"
			<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
	}
}//_Test


