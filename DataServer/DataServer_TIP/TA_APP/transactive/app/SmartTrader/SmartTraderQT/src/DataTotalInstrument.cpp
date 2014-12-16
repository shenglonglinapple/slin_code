#include "DataTotalInstrument.h"

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

#include "Instrument.h"

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



void CDataTotalInstrument::onInstrumentDownloaded( const Instrument& instrument )
{
	Instrument* pInstrumentRef = NULL;
	unsigned int nGetInstrumentID = 0;
	std::string strLogInfo;

	{
		QMutexLocker lock(&m_mutexForMapInstrumentIDData);
		nGetInstrumentID = instrument.getInstrumentID();
		pInstrumentRef = instrument.getInstrument(instrument.getInstrumentID());

		m_MapInstrumentIDData.insert(nGetInstrumentID, pInstrumentRef);
		
		//if (m_MapInstrumentIDData.size() == 2298)
		{
			MYLOG4CPP_DEBUG<<"CDataTotalInstrument"
				<<" "<<"onInstrumentDownloaded"
				<<" "<<"m_MapInstrumentIDData.size="<<m_MapInstrumentIDData.size();
		}

		strLogInfo = "onInstrumentDownloaded";
		m_pProjectLogHelper->log_MyInstrument_info(__FILE__, __LINE__, strLogInfo, pInstrumentRef);
	}

}//onInstrumentDownloaded



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
			/*
			MYLOG4CPP_ERROR<<"not find nInstrumentID="<<nInstrumentID
			<<" "<<"in m_MapInstrumentIDData"
			<<" "<<"m_MapInstrumentIDData.size()="<<m_MapInstrumentIDData.size();
			*/
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
	Instrument* pInstrumentRef = NULL;
	QMap<unsigned int, Instrument*>::iterator  iterMap;

	m_MapInstrumentIDData.clear();

}//


