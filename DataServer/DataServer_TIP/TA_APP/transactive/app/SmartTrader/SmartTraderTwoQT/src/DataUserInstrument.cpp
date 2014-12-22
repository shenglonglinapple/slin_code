#include "DataUserInstrument.h"

#include "ItemUserInstrument.h"
#include "ItemUserInstrumentHelper.h"
#include "DataTotalInstrument.h"
#include "DataTotalMyInstrument.h"
//
#include "Log4cppLogger.h"



CDataUserInstrument* CDataUserInstrument::m_pInstance = 0;
QMutex CDataUserInstrument::m_mutexInstance;

CDataUserInstrument& CDataUserInstrument::getInstance()
{	
	QMutexLocker lock(&m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CDataUserInstrument();
	}
	return (*m_pInstance);
}

void CDataUserInstrument::removeInstance()
{
	QMutexLocker lock(&m_mutexInstance);	
	delete m_pInstance;
	m_pInstance = NULL;

}

CDataUserInstrument::CDataUserInstrument(void)
{	
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);	
	m_pItemUserInstrument_Root = NULL;
	m_pItemUserInstrument_Root = new CItemUserInstrument();
	m_pItemUserInstrumentHelper = NULL;
	m_pItemUserInstrumentHelper = new CItemUserInstrumentHelper();
}

CDataUserInstrument::~CDataUserInstrument(void)
{		
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
	if (NULL != m_pItemUserInstrument_Root)
	{
		delete m_pItemUserInstrument_Root;
		m_pItemUserInstrument_Root = NULL;
	}
	if (NULL != m_pItemUserInstrumentHelper)
	{
		delete m_pItemUserInstrumentHelper;
		m_pItemUserInstrumentHelper = NULL;
	}
}

CItemUserInstrument* CDataUserInstrument::getRootItem()
{
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
	return m_pItemUserInstrument_Root;
}

void CDataUserInstrument::addUserInstrument( unsigned int nInstrumentID )
{	
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
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
		m_pItemUserInstrumentHelper->setValue(*pInstrumentRef);
	}

	if (NULL != pMyInstrumentRef)
	{
		m_pItemUserInstrumentHelper->setValue(*pMyInstrumentRef);
	}

	MYLOG4CPP_DEBUG<<"CDataUserInstrument addUserInstrument"
		<<" "<<"getInstrumentID="<<m_pItemUserInstrumentHelper->getInstrumentID()
		<<" "<<"getInstrumentCode="<<m_pItemUserInstrumentHelper->getInstrumentCode().toStdString();

	m_pItemUserInstrument_Root->appendChildByData(m_pItemUserInstrumentHelper);
}


void CDataUserInstrument::updateDataUserInstrument( unsigned int nInstrumentID )
{	
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
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
		m_pItemUserInstrumentHelper->setValue(*pInstrumentRef);
	}

	if (NULL != pMyInstrumentRef)
	{
		m_pItemUserInstrumentHelper->setValue(*pMyInstrumentRef);
	}

	MYLOG4CPP_DEBUG<<"CDataUserInstrument updateDataUserInstrument"
		<<" "<<"getInstrumentID="<<m_pItemUserInstrumentHelper->getInstrumentID()
		<<" "<<"getInstrumentCode="<<m_pItemUserInstrumentHelper->getInstrumentCode().toStdString();

	m_pItemUserInstrument_Root->findAndResetSubNodeData(m_pItemUserInstrumentHelper);
}


void CDataUserInstrument::removeUserInstrument( unsigned int nInstrumentID )
{	
	QMutexLocker lock(&m_mutex_ItemUserInstrument_Root);
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
		m_pItemUserInstrumentHelper->setValue(*pInstrumentRef);
	}

	if (NULL != pMyInstrumentRef)
	{
		m_pItemUserInstrumentHelper->setValue(*pMyInstrumentRef);
	}

	MYLOG4CPP_DEBUG<<"CDataUserInstrument removeUserInstrument"
		<<" "<<"getInstrumentID="<<m_pItemUserInstrumentHelper->getInstrumentID()
		<<" "<<"getInstrumentCode="<<m_pItemUserInstrumentHelper->getInstrumentCode().toStdString();

	m_pItemUserInstrument_Root->removeChildByData(m_pItemUserInstrumentHelper);
}