#include "DataTotalInstrument.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "MyInstrument.h"
#include "MyMarketData.h"

#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"
#include "QtTimeHelper.h"


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
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	_FreeData_MapInstrumentIDData();
}

CDataTotalInstrument::~CDataTotalInstrument()
{
	_FreeData_MapInstrumentIDData();
	if (NULL != m_pProjectLogHelper)
	{
		delete m_pProjectLogHelper;
		m_pProjectLogHelper = NULL;
	}
	if (NULL != m_pQtTimeHelper)
	{
		delete m_pQtTimeHelper;
		m_pQtTimeHelper = NULL;
	}
}



void CDataTotalInstrument::onInstrumentDownloaded( const CMyInstrument& instrument )
{
	CMyInstrument* pNewInstrument = NULL;
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		nGetInstrumentID = instrument.getInstrumentID();
		pNewInstrument = new CMyInstrument();
		*pNewInstrument = instrument;
		m_MapInstrumentIDData.insert(nGetInstrumentID, pNewInstrument);
		
		MYLOG4CPP_DEBUG<<"CDataTotalInstrument"
			<<" "<<"onInstrumentDownloaded"
			<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
		strLogInfo = "onInstrumentDownloaded";
		m_pProjectLogHelper->log_Instrument_info(__FILE__, __LINE__, strLogInfo, pNewInstrument);
		pNewInstrument = NULL;		
	}

}//onInstrumentDownloaded


void CDataTotalInstrument::onMarketDataUpdate( const CMyMarketData &marketData )
{

	CMyInstrument* pInstrumentGet = NULL;
	QMap<unsigned int, CMyInstrument*>::iterator  iterFind;
	std::string strLogInfo;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);

		if (false == m_MapInstrumentIDData.contains(marketData.getSecurityID()))
		{
			MYLOG4CPP_ERROR<<"not find getSecurityID="<<marketData.getSecurityID()
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			return;
		}

		iterFind = m_MapInstrumentIDData.find(marketData.getSecurityID());
		//find ok
		pInstrumentGet = iterFind.value();
		pInstrumentGet->setValue(&marketData);

		MYLOG4CPP_DEBUG<<"onMarketDataUpdate reset Instrument data"
			<<" "<<"getInstrumentID="<<pInstrumentGet->getInstrumentID()
			<<" "<<"strInstrumentCode="<<pInstrumentGet->getInstrumentCode()
			<<" "<<"getUpdateTime="<< m_pQtTimeHelper->dateTimeToStr_Qt(pInstrumentGet->getUpdateTime())
			<<" "<<"fLastPrice="<<pInstrumentGet->getLastPrice();
		
		strLogInfo = "onMarketDataUpdate";
		m_pProjectLogHelper->log_Instrument_info(__FILE__, __LINE__, strLogInfo, pInstrumentGet);
	}
}//onMarketDataUpdate

CMyInstrument* CDataTotalInstrument::findInstrumentByID(unsigned int nInstrumentID)
{
	std::string strExchangeName;
	std::string strUnderlyingCode;
	std::string strInstrumentCode;
	CMyInstrument* pInstrumentRef = NULL;
	QMap<unsigned int, CMyInstrument*>::iterator  iterFind;

	{
		//check in total list
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		if (false == m_MapInstrumentIDData.contains(nInstrumentID))
		{
			MYLOG4CPP_ERROR<<"not find nInstrumentID="<<nInstrumentID
				<<" "<<"in m_MapInstrumentIDData"
				<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			pInstrumentRef = NULL;
			return pInstrumentRef;
		}
		iterFind = m_MapInstrumentIDData.find(nInstrumentID);

		//find ok
		pInstrumentRef = iterFind.value();
	}


	return pInstrumentRef;
}



void CDataTotalInstrument::_FreeData_MapInstrumentIDData()
{
	CMyInstrument* pInstrumentRef = NULL;
	QMap<unsigned int, CMyInstrument*>::iterator  iterMap;

	{
		//check in total list
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		iterMap = m_MapInstrumentIDData.begin();
		while (iterMap != m_MapInstrumentIDData.end())
		{
			pInstrumentRef = iterMap.value();

			delete pInstrumentRef;
			pInstrumentRef = NULL;

			iterMap++;
		}//while
		m_MapInstrumentIDData.clear();
	}



}//


