#include "ConfigInfo.h"

#include "ConfigFileHelper.h"

#include "BoostLogger.h"
USING_BOOST_LOG;





//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE


static const std::string DEFAULT_STRING_VALUE_STRING_SPLIT = ",";
static const std::string DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange = "Change";//Change//变动//价格变化颜色





CConfigInfo* CConfigInfo::m_pInstance = 0;
boost::mutex CConfigInfo::m_mutexInstance;

CConfigInfo& CConfigInfo::getInstance()
{	
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL == m_pInstance)
	{
		m_pInstance = new CConfigInfo();
	}
	return (*m_pInstance);
}

void CConfigInfo::removeInstance()
{
	boost::mutex::scoped_lock lock(m_mutexInstance);	
	if (NULL != m_pInstance)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}


CConfigInfo::CConfigInfo()
{
	m_strSkinName.clear();
	m_LstUserInstrument.clear();
	m_pConfigFileHelper = NULL;

	m_pConfigFileHelper = new CConfigFileHelper();
	loadDataFromConfig();
}

CConfigInfo::~CConfigInfo()
{
	if (NULL != m_pConfigFileHelper)
	{
		delete m_pConfigFileHelper;
		m_pConfigFileHelper = NULL;
	}
	
}

QString CConfigInfo::getSkinName()
{
	return m_strSkinName;
}

QStringList CConfigInfo::getLstUserInstrument()
{
	return m_LstUserInstrument;
}

QStringList CConfigInfo::getLstAllAvailableColums()
{
	return m_LstAllAvailableColums;
}
QStringList CConfigInfo::getLstSelectedColumns()
{
	return m_LstSelectedColumns;
}


void CConfigInfo::loadDataFromConfig()
{
	QString strValueGet;
	m_strSkinName = m_pConfigFileHelper->getSkinNameFormConfig();

	m_LstUserInstrument.clear();
	strValueGet = m_pConfigFileHelper->getUserInstrumentFormConfig();
	if (!strValueGet.isEmpty())
	{
		m_LstUserInstrument = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}
	strValueGet.clear();
	
	m_LstAllAvailableColums.clear();
	strValueGet = m_pConfigFileHelper->getUserAllAvailableColumns();
	if (!strValueGet.isEmpty())
	{
		m_LstAllAvailableColums = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}
	strValueGet.clear();

	m_LstSelectedColumns.clear();
	strValueGet = m_pConfigFileHelper->getUserSelectedColumnns();
	if (!strValueGet.isEmpty())
	{
		m_LstSelectedColumns = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}

	m_nColumnIndex_Change = -1;
	if (m_LstSelectedColumns.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str())))
	{
		m_nColumnIndex_Change = m_LstSelectedColumns.indexOf(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str()), 0);
	}
	strValueGet.clear();


}



void CConfigInfo::setLstUserInstrument( QStringList& lstStringValue )
{
	QString strValue;
	QString strValueGet;

	strValue = lstStringValue.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	m_pConfigFileHelper->setUserInstrumentToConfig(strValue);

	//refush memory data
	strValueGet = m_pConfigFileHelper->getUserInstrumentFormConfig();
	m_LstUserInstrument.clear();
	if (!strValueGet.isEmpty())
	{
		m_LstUserInstrument = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}


}

void CConfigInfo::setLstAllAvailableColums( QStringList& lstStringValue )
{
	QString strValue;
	QString strValueGet;

	strValue = lstStringValue.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	
	//refush db data
	m_pConfigFileHelper->setUserAllAvailableColumns(strValue);

	//refush memory data
	m_LstAllAvailableColums.clear();
	strValueGet = m_pConfigFileHelper->getUserAllAvailableColumns();
	if (!strValueGet.isEmpty())
	{
		m_LstAllAvailableColums = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}
	strValueGet.clear();

}

void CConfigInfo::setLstSelectedColumns( QStringList& lstStringValue )
{
	QString strValue;
	QString strValueGet;

	strValue = lstStringValue.join(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	m_pConfigFileHelper->setUserSelectedColumns(strValue);
	
	//refush memory data
	m_LstSelectedColumns.clear();
	strValueGet = m_pConfigFileHelper->getUserSelectedColumnns();
	if (!strValueGet.isEmpty())
	{
		m_LstSelectedColumns = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}

	m_nColumnIndex_Change = -1;
	if (m_LstSelectedColumns.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str())))
	{
		m_nColumnIndex_Change = m_LstSelectedColumns.indexOf(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str()), 0);
	}

	strValueGet.clear();

}

QStringList CConfigInfo::getLstAllAvailableColumsDefault()
{
	QString strValueGet; 
	m_LstAllAvailableColums.clear();
	strValueGet = m_pConfigFileHelper->getUserAllAvailableColumnsDefault();
	if (!strValueGet.isEmpty())
	{
		m_LstAllAvailableColums = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}
	strValueGet.clear();

	return m_LstAllAvailableColums;
}

QStringList CConfigInfo::getLstSelectedColumnsDefault()
{
	QString strValueGet; 
	m_LstSelectedColumns.clear();
	strValueGet = m_pConfigFileHelper->getUserSelectedColumnnsDefault();
	if (!strValueGet.isEmpty())
	{
		m_LstSelectedColumns = strValueGet.split(DEFAULT_STRING_VALUE_STRING_SPLIT.c_str());//","
	}

	m_nColumnIndex_Change = -1;
	if (m_LstSelectedColumns.contains(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str())))
	{
		m_nColumnIndex_Change = m_LstSelectedColumns.indexOf(QObject::tr(DEFVALUE_String_ColumnName_SmartQuotes_InstrumentPriceChange.c_str()), 0);
	}

	strValueGet.clear();

	return m_LstSelectedColumns;
}

int CConfigInfo::getColumnIndex_Change()
{
	return m_nColumnIndex_Change;
}

//QT_END_NAMESPACE

