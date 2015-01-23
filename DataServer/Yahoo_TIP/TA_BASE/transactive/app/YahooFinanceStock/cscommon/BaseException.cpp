#include "BaseException.h"

#include <QtCore/QString>

#include "Log4cppLogger.h"


CBaseException::CBaseException(const QString& fileName, qint32 lineNumber, const QString& errorMessage) throw()
{
	m_nErrorCode = 0;
	m_strErrorMessage.clear();
	m_strException.clear();

	m_strErrorMessage = errorMessage;

	m_strException = QString("Exception: fileName=%1 lineNumber=%2 errorCode=%3 errorMessage=%4")
		.arg(fileName).arg(lineNumber).arg(m_nErrorCode).arg(m_strErrorMessage);

}

CBaseException::CBaseException( CBaseException& objCopy )
{
	m_nErrorCode = objCopy.m_nErrorCode;
	m_strErrorMessage = objCopy.m_strErrorMessage;
	m_strException = objCopy.m_strException;
}


CBaseException::~CBaseException() throw()
{
	m_nErrorCode = 0;
	m_strErrorMessage.clear();
	m_strException.clear();
}

qint32 CBaseException::getErrorCode()
{
	return m_nErrorCode;
}
QString CBaseException::getString()
{
	return m_strException;
}


void CBaseException::logInfo( const QString& fileName, qint32 lineNumber )
{
	MYLOG4CPP_ERROR_Base<<" "<<"["<<fileName<<":"<<lineNumber<<"]"
		<<" "<<"CBaseException:"<<" "<<m_strException;
}

QString CBaseException::errorCodeAsString(qint32 nErrorCode)
{
	QString strErrorCode = "error! child class need this fun";
	MYLOG4CPP_ERROR<<strErrorCode;
	return strErrorCode;
}







