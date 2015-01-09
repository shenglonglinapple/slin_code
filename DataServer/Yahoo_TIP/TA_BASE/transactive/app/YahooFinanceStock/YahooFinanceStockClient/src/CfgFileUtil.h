#ifndef __CLASS_CFG_FILE_UTIL_HH__
#define __CLASS_CFG_FILE_UTIL_HH__

#include <QtCore/QString>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CCfgFileUtil
{
public:
	static CCfgFileUtil& getInstance();
	static void removeInstance();

private:
	static CCfgFileUtil* m_pInstance;
	static QMutex m_mutexInstance;

private:
	CCfgFileUtil();
	~CCfgFileUtil();

public:
	/*
		[config]
		skin=XXX.file
	*/
	void write(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, const QString& strValue);
	/*
	return -1; config file not have key
	return 0; get data ok
	*/
	int read(const QString& strConfigFileName, const QString& strGroup, const QString& strKey, QString& strValue);
};
#endif  // __CLASS_CFG_FILE_UTIL_HH__



