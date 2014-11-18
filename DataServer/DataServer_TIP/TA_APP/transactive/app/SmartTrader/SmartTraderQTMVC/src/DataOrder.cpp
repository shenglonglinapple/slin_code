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









