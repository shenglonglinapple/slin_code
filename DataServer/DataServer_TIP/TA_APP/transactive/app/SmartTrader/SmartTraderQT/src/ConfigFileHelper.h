#ifndef __CLASS_CONFIGFILE_HELPER__HH__
#define __CLASS_CONFIGFILE_HELPER__HH__

#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CConfigFileHelper
{
public:
	CConfigFileHelper();
	virtual ~CConfigFileHelper();
private:
	int _WriteToConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, const QString& strValue);
	/*
	return -1; config file not have key
	return 0; get data ok
	*/
	int _ReadFormConfig(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, QString& strValue);
public:
	void setConfigFile( const QString& strConfigFileName );

	void setFileDBPathToConfig(const QString& strValue);
	QString getFileDBPathFormConfig();

	QString getSQLiteDBPathFormConfig();
	void setSQLiteDBPathToConfig(const QString& strValue);

	QString getLastUpdateTimeFormConfig();
	void setLastUpdateTimeToConfig(const QString& strValue);
private:
	QString m_strConfigFileName;
	QMutex m_mutexConfigFileName;
};
//QT_END_NAMESPACE
#endif  // __CLASS_CONFIGFILE_HELPER__HH__



