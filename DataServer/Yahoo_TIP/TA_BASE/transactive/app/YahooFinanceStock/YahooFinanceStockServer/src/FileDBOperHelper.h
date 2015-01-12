#ifndef __CLASS_FILE_DB_OPER_HELPER_H__
#define __CLASS_FILE_DB_OPER_HELPER_H__


#include <QtCore/QString>
#include <QtCore/QStringList>

class CQtTimeHelper;
class CFileDBOper;

class CFileDBOperHelper 
{
public:
	CFileDBOperHelper(const QString& strSymbolUse);
	virtual ~CFileDBOperHelper();
public:
	void saveData(const QString & strHistoryData);
private:
	void _SaveData(const QStringList& strListHistoryDataTmp);
	void _RemoveEmptyString(QStringList& strList);
private:
	CQtTimeHelper* m_pQtTimeHelper;
	CFileDBOper* m_pFileDBOper;
	QString m_strSymbolUse;
};


#endif //__CLASS_FILE_DB_OPER_HELPER_H__
