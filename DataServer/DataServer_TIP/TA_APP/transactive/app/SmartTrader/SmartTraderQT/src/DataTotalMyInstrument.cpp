#include "DataTotalMyInstrument.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "MyInstrument.h"
#include "MyMarketData.h"

#include "ProjectLogHelper.h"
#include "Log4cppLogger.h"
#include "QtTimeHelper.h"


CDataTotalMyInstrument* CDataTotalMyInstrument::m_pInstance = 0;
QMutex CDataTotalMyInstrument::m_mutexInstance;

CDataTotalMyInstrument& CDataTotalMyInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataTotalMyInstrument();
	}
	return (*m_pInstance);
}

void CDataTotalMyInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataTotalMyInstrument::CDataTotalMyInstrument()
{
	m_pProjectLogHelper = NULL;
	m_pProjectLogHelper = new CProjectLogHelper();
	m_pQtTimeHelper = NULL;
	m_pQtTimeHelper = new CQtTimeHelper();
	_FreeData_MapInstrumentIDData();
}

CDataTotalMyInstrument::~CDataTotalMyInstrument()
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



void CDataTotalMyInstrument::onInstrumentDownloaded( const CMyInstrument& instrument )
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
		m_pProjectLogHelper->log_MyInstrument_info(__FILE__, __LINE__, strLogInfo, pNewInstrument);
		pNewInstrument = NULL;		
	}

}//onInstrumentDownloaded


void CDataTotalMyInstrument::onMarketDataUpdate( const CMyMarketData &marketData )
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
		m_pProjectLogHelper->log_MyInstrument_info(__FILE__, __LINE__, strLogInfo, pInstrumentGet);
	}
}//onMarketDataUpdate

CMyInstrument* CDataTotalMyInstrument::findInstrumentByID(unsigned int nInstrumentID)
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



void CDataTotalMyInstrument::_FreeData_MapInstrumentIDData()
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


