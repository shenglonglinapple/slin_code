#ifndef __I_QUERYADAPTER_HH__
#define __I_QUERYADAPTER_HH__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QMap>

class IQueryAdapter
{
public:
	IQueryAdapter()
	{
		return;
	}
	virtual ~IQueryAdapter() 
	{
		return;
	}
public:
	virtual QString getQueryUUID() = 0;
public:
	virtual bool hasMore() = 0;
	virtual qint32 getColumnCount() = 0;
	virtual QStringList getLstColumnName() = 0;
	virtual bool isNull ( const QString & fieldName ) = 0;
	virtual QString getStringData(const QString& fieldName, const QString defaultValue = "") = 0;


};
#endif  /// __I_QUERYADAPTER_HH__









