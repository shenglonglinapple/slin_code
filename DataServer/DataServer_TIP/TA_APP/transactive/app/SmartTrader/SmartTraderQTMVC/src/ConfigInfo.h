#ifndef __CLASS_CONFIGINFO__HH__
#define __CLASS_CONFIGINFO__HH__

#include <QtCore/QString>
#include <QtCore/QStringList>

#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>

//QT_BEGIN_NAMESPACE
////QT_END_NAMESPACE

class CConfigFileHelper;

class CConfigInfo
{
public:
	static CConfigInfo& getInstance();
	static void removeInstance();

private:
	static CConfigInfo* m_pInstance;
	static QMutex m_mutexInstance;

public:
	CConfigInfo();
	virtual ~CConfigInfo();
public:
	QString getSkinName();

	QStringList getLstUserInstrument();
	void setLstUserInstrument(QStringList& lstStringValue);

	QStringList getLstAllAvailableColumsDefault();
	QStringList getLstAllAvailableColums();
	void setLstAllAvailableColums(QStringList& lstStringValue);

	QStringList getLstSelectedColumnsDefault();
	QStringList getLstSelectedColumns();
	void setLstSelectedColumns(QStringList& lstStringValue);

	int getColumnIndex_Change();

public:
	void loadDataFromConfig();
private:
	QString m_strSkinName;
	QStringList m_LstUserInstrument;
	QStringList m_LstAllAvailableColums;
	QStringList m_LstSelectedColumns;
	int m_nColumnIndex_Change;//-1 means not have column "Change"
private:
	CConfigFileHelper* m_pConfigFileHelper;
};
//QT_END_NAMESPACE
#endif  // __CLASS_CONFIGINFO__HH__



