#ifndef __CLASS_SQL_DATA_H__
#define __CLASS_SQL_DATA_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CSQLData
{
public:
	CSQLData();
	virtual ~CSQLData();
public:
	CSQLData& operator=(const CSQLData& objectCopy);
private:
	QString m_strDataKey;
};


#endif //__CLASS_SQL_DATA_H__
