#ifndef __CLASS_BASE_EXECPTION_H__
#define __CLASS_BASE_EXECPTION_H__

#include <string>
#include <exception>


class CBaseException : public std::exception
{
public:
	CBaseException(int nErrorCode,	const std::string strReason) throw();
	CBaseException(CBaseException& e);
	virtual ~CBaseException() throw();
public:
	CBaseException(const std::string &fileName, 
		unsigned lineNumber, 
		const std::string &errorMessage) throw();
public:
	void logInfo();
public:
	std::string getErrorMsg();
	std::string getErrorString();
	std::string getReason();
	int getErrorCode();
	void logInfo(const std::string& file, int line);

public:
	virtual std::string errorCodeAsString(int nErrCode);
private:
	int				m_nErrorCode;
	std::string     m_strReason;

	std::string		m_strErrMessage;
	std::string     m_strErrorString;

};




#endif //__CLASS_BASE_EXECPTION_H__
