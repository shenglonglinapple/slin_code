#ifndef __CLASS_CONFIGFILE_HELPER__HH__
#define __CLASS_CONFIGFILE_HELPER__HH__

#include <QtCore/QString>
#include <boost/thread/mutex.hpp>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CConfigFileHelper
{
public:
	CConfigFileHelper();
	virtual ~CConfigFileHelper();
public:
	void setConfigFile(const QString& strConfigFileName);
	QString getSkinNameFormConfig();
	void setSkinNameToConfig(const QString& strValue);

	QString getUserInstrumentFormConfig();
	void setUserInstrumentToConfig(const QString& strValue);

	QString getUserAllAvailableColumnsDefault();
	QString getUserAllAvailableColumns();
	void setUserAllAvailableColumns(const QString& strValue);

	QString getUserSelectedColumnnsDefault();
	QString getUserSelectedColumnns();
	void setUserSelectedColumns(const QString& strValue);

public:
	int _WriteToConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, const QString& strValue);
	/*
	return -1; config file not have key
	return 0; get data ok
	*/
	int _ReadFormConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, QString& strValue);
private:
	QString m_strConfigFileName;
	boost::mutex m_mutexConfigFileName;
};
//QT_END_NAMESPACE
#endif  // __CLASS_CONFIGFILE_HELPER__HH__



