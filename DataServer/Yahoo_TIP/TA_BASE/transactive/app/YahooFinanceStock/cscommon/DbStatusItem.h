#ifndef _CLASS_DB_STATUS_ITEM_H__
#define _CLASS_DB_STATUS_ITEM_H__

#include <QtCore/QString>

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
class CDbStatusItem
{
public:

	// the database server type support in the system
	enum EDBType
	{
		DBType_QSQLITE,
		DBType_QMYSQL,
	};

	enum EDBState
	{
		EDBState_Pending,
		EDBState_Online,
		EDBState_Offline,		
	};


	enum EDataTypes
	{
		DataTypes_CSData,
		DataTypes_YahuoData,
	};

	enum EDBPriority
	{
		DBPriority_0 = 0,
		DBPriority_1,
	};


public:
	CDbStatusItem();
	~CDbStatusItem();
public:
	CDbStatusItem& operator=(const CDbStatusItem& objectCopy);
public:
	EDataTypes m_nDataType;
	EDBPriority m_nDBPriority;
	EDBType m_nDBType;
	EDBState m_nDBState;
	QString m_strDBConnectionString;
	
	QString m_strDbType;
	QString m_strSchema;
	QString m_strUser;
	QString m_strPassword;
	QString m_strIP;
	

public:
	void clear();
	void logInfo( const QString& file, qint32 line );
	QString getConnectionString();
	bool isValid();
public:
	QString getString(EDBType nValue);
	QString getString(EDBState nValue);
	QString getString(EDataTypes nValue);
	QString getString(EDBPriority nValue);
	
	
	
};//class 



#endif //_CLASS_DB_STATUS_ITEM_H__



