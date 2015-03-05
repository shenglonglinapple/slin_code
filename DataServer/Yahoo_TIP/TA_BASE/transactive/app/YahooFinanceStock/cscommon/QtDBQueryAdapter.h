#ifndef __CLASS_QT_DB_QUERYADAPTER_HH__
#define __CLASS_QT_DB_QUERYADAPTER_HH__

#include <QtCore/QString>
#include <QtCore/QStringList>
#include <QtCore/QList>
#include <QtCore/QObject>
#include <QtCore/QMutex>
#include <QtCore/QMutexLocker>
#include <QtCore/QMap>

#include "IQueryAdapter.h"

class QSqlQuery;

class CQtDBQueryAdapter : public IQueryAdapter
{
public:
	CQtDBQueryAdapter(QSqlQuery* pQuery);
	~CQtDBQueryAdapter();
public:
	QString getQueryUUID();
public:
	qint32 getColumnCount();
	QStringList getLstColumnName();
	bool hasMore();
	QString getStringData(const QString& fieldName, const QString defaultValue = "");
	bool isNull ( const QString & fieldName );

private:
	void _GetAllColumnName();

private:
	QSqlQuery* m_pQuery;
	QString m_strQueryUUID;
	qint32 m_nColumnCount;
	QStringList m_LstColumnName;
	QMap<QString, QString> m_mapColumnNameValue;
};
#endif  /// __CLASS_QT_DB_QUERYADAPTER_HH__









