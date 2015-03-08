#ifndef __CLASS_SQL_PARAM_H__
#define __CLASS_SQL_PARAM_H__

#include <QtCore/QString>
#include <QtCore/QStringList>

class CSQLParam
{
public:
	CSQLParam();
	virtual ~CSQLParam();
public:
	CSQLParam(const CSQLParam& objCopy);
	CSQLParam(const QString& tmpValue);
	CSQLParam(const char* tmpValue);
	CSQLParam(const char& tmpValue);
	CSQLParam(const qint32& tmpValue);
	CSQLParam(const qint64& tmpValue);
	CSQLParam( const float& tmpValue);
	CSQLParam(const double& tmpValue);
	

public:
	CSQLParam& operator=(const CSQLParam& objCopy);
public:
	QString getParam() const;
	QString do_fraction(long double value, int decplaces);
private:
	QString strParam;
};


#endif //__CLASS_SQL_PARAM_H__
