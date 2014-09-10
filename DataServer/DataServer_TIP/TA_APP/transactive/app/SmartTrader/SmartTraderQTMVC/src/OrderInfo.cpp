#include "OrderInfo.h"

#include "ProjectUtilityFun.h"
#include <QtCore/QStringList>

#include "BoostLogger.h"
USING_BOOST_LOG;

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE




static const std::string DEFVALUE_String_ColumnName_Data_Key = "Key";//
static const std::string DEFVALUE_String_ColumnName_OrderInfo_OrderID = "OrderID";//





//////////////////////////////////////////////////////////////////////////

COrderInfo::COrderInfo()
{

	_ClearData();

	

	m_pUtilityFun = NULL;
	m_pUtilityFun = new CProjectUtilityFun();

}

COrderInfo::~COrderInfo()
{
	if (NULL != m_pUtilityFun)
	{
		delete m_pUtilityFun;
		m_pUtilityFun = NULL;
	}

}


COrderInfo& COrderInfo::operator=( const COrderInfo& exchangeParam )
{
	this->m_nKey = exchangeParam.m_nKey;


	return *this;
}

void COrderInfo::_ClearData()
{
	
	this->m_nKey = 0;

}




void COrderInfo::setValue( const Order &newValue )
{
	_ClearData();
	m_nKey = newValue.getOrderID();

}





void COrderInfo::logInfo( const QString& strLogInfo ) const
{
	LOG_DEBUG<<"COrderInfo:"
		<<" "<<"m_nKey="<<m_nKey
		<<" "<<"m_nOrderID="<<m_nKey;
}



void COrderInfo::setDefaultValue()
{
	this->m_nKey = 0;
}

QVariant COrderInfo::getValueByName( const QString& strName )
{
	QVariant varValueRes;
	QStringList strlstClumnNameShow;

	strlstClumnNameShow.push_back(strName);


	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_Data_Key.c_str())))
	{
		varValueRes = QVariant(this->m_nKey);
		return varValueRes;
	}

	//
	if (strlstClumnNameShow.contains(QObject::tr(DEFVALUE_String_ColumnName_OrderInfo_OrderID.c_str())))
	{
		varValueRes = QVariant(this->m_nKey);
		return varValueRes;
	}
	


	return varValueRes;
}

unsigned int COrderInfo::getKey()
{
	return m_nKey;
}


//QT_END_NAMESPACE





