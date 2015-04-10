#ifndef __CLASS_BASE_EXECPTION_H__
#define __CLASS_BASE_EXECPTION_H__

#include <exception>
#include <QtCore/QString>

//QT_BEGIN_NAMESPACE
//QT_END_NAMESPACE

class CBaseException : public std::exception
{
public:
	CBaseException(const QString& fileName, qint32 lineNumber, const QString& errorMessage) throw();
	CBaseException(CBaseException& objCopy);
	virtual ~CBaseException() throw();
public:
	QString getString();
	qint32 getErrorCode();
	void logInfo(const QString& fileName, qint32 lineNumber);
public:
	//child class imp this fun
	virtual QString errorCodeAsString(qint32 nErrorCode);
private:
	qint32		m_nErrorCode;
	QString		m_strErrorMessage;
	QString     m_strException;
};




#endif //__CLASS_BASE_EXECPTION_H__
