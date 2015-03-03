#include "SQLParam.h"
#include "Log4cppLogger.h"

CSQLParam::CSQLParam()
{
	strParam.clear();
}
CSQLParam::~CSQLParam()
{
	strParam.clear();
}
CSQLParam& CSQLParam::operator=( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
	return *this;
}

CSQLParam::CSQLParam( const CSQLParam& objCopy )
{
	strParam = objCopy.strParam;
}


CSQLParam::CSQLParam( const QString& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char* tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const char& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const qint32& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const qint64& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

CSQLParam::CSQLParam( const double& tmpValue )
{
	strParam = QString("%1").arg(tmpValue);
}

QString CSQLParam::getParam() const
{
	return strParam;
}

