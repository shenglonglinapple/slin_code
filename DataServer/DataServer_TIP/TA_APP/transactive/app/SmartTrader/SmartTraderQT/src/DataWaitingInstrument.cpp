#include "DataWaitingInstrument.h"

#include "ItemWaitingInstrument.h"
#include "ItemWaitingInstrumentHelper.h"
#include "DataTotalInstrument.h"
#include "DataTotalMyInstrument.h"
//
#include "Log4cppLogger.h"



CDataWaitingInstrument* CDataWaitingInstrument::m_pInstance = 0;
QMutex CDataWaitingInstrument::m_mutexInstance;

CDataWaitingInstrument& CDataWaitingInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataWaitingInstrument();
	}
	return (*m_pInstance);
}

void CDataWaitingInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataWaitingInstrument::CDataWaitingInstrument(void)
{	
	QMutexLocker lock(&m_mutex_ItemWaitingInstrument_Root);	
	m_pItemWaitInstrument_Root = NULL;
	m_pItemWaitInstrument_Root = new CItemWaitingInstrument();
	m_pItemWaitingInstrumentHelper = NULL;
	m_pItemWaitingInstrumentHelper = new CItemWaitingInstrumentHelper();
}

CDataWaitingInstrument::~CDataWaitingInstrument(void)
{		
	QMutexLocker lock(&m_mutex_ItemWaitingInstrument_Root);
	if (NULL != m_pItemWaitInstrument_Root)
	{
		delete m_pItemWaitInstrument_Root;
		m_pItemWaitInstrument_Root = NULL;
	}
	if (NULL != m_pItemWaitingInstrumentHelper)
	{
		delete m_pItemWaitingInstrumentHelper;
		m_pItemWaitingInstrumentHelper = NULL;
	}
}

CItemWaitingInstrument* CDataWaitingInstrument::getRootItem()
{
	QMutexLocker lock(&m_mutex_ItemWaitingInstrument_Root);
	return m_pItemWaitInstrument_Root;
}

void CDataWaitingInstrument::addInstrument( unsigned int nInstrumentID )
{	
	QMutexLocker lock(&m_mutex_ItemWaitingInstrument_Root);
	Instrument* pInstrumentRef = NULL;
	CMyInstrument* pMyInstrumentRef = NULL;

	pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef && NULL == pMyInstrumentRef)
	{
		return;
	}

	if (NULL != pInstrumentRef)
	{
		m_pItemWaitingInstrumentHelper->setValue(*pInstrumentRef);
	}

	if (NULL != pMyInstrumentRef)
	{
		m_pItemWaitingInstrumentHelper->setValue(*pMyInstrumentRef);
	}

	/*	
	MYLOG4CPP_DEBUG<<"CDataWaitingInstrument addInstrument"
		<<" "<<"m_nInstrumentID="<<m_pItemWaitingInstrumentHelper->m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_pItemWaitingInstrumentHelper->m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_pItemWaitingInstrumentHelper->m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_pItemWaitingInstrumentHelper->m_strInstrumentCode.toStdString();
	*/	
	m_pItemWaitInstrument_Root->AnalysisAndAppendChild(m_pItemWaitingInstrumentHelper);
}


void CDataWaitingInstrument::removeInstrument( unsigned int nInstrumentID )
{	
	QMutexLocker lock(&m_mutex_ItemWaitingInstrument_Root);
	Instrument* pInstrumentRef = NULL;
	CMyInstrument* pMyInstrumentRef = NULL;

	pInstrumentRef = NULL;
	pInstrumentRef = CDataTotalInstrument::getInstance().findInstrumentByID(nInstrumentID);
	pMyInstrumentRef = NULL;
	pMyInstrumentRef = CDataTotalMyInstrument::getInstance().findInstrumentByID(nInstrumentID);
	if (NULL == pInstrumentRef && NULL == pMyInstrumentRef)
	{
		return;
	}

	if (NULL != pInstrumentRef)
	{
		m_pItemWaitingInstrumentHelper->setValue(*pInstrumentRef);
	}

	if (NULL != pMyInstrumentRef)
	{
		m_pItemWaitingInstrumentHelper->setValue(*pMyInstrumentRef);
	}

	MYLOG4CPP_DEBUG<<"CDataWaitingInstrument removeInstrument"
		<<" "<<"m_nInstrumentID="<<m_pItemWaitingInstrumentHelper->m_nInstrumentID
		<<" "<<"m_strExchangeName="<<m_pItemWaitingInstrumentHelper->m_strExchangeName.toStdString()
		<<" "<<"m_strUnderlyingCode="<<m_pItemWaitingInstrumentHelper->m_strUnderlyingCode.toStdString()
		<<" "<<"m_strInstrumentCode="<<m_pItemWaitingInstrumentHelper->m_strInstrumentCode.toStdString();

	m_pItemWaitInstrument_Root->AnalysisAndRemoveChild(m_pItemWaitingInstrumentHelper);
}


