#include "SQLStringXmlParser.h"

#include <QtCore/QFile>
#include <QtXml/QtXml>

#include "SQLData.h"
#include "Log4cppLogger.h"



CSQLStringXmlParser::CSQLStringXmlParser()
{
}

CSQLStringXmlParser::~CSQLStringXmlParser()
{

}

qint32 CSQLStringXmlParser::doParse( const QString& strSQLStringXmlFile, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;
	QFile fileSQLStringXml;
	QString strGetError;  
	qint32 nGetRow = 0;
	qint32 nGetColumn = 0;

	QDomDocument document;  
	QDomElement node_Tables;

	QDomNodeList node_Tables_childlist;
	qint32 node_Tables_childlist_count = 0;


	QString node_Tables_tagname;//"Tables"
	QString node_Tables_TableCount;//<Tables TableCount="2">

	if (strSQLStringXmlFile.isEmpty())
	{
		MYLOG4CPP_ERROR<<"error! strSQLStringXmlFile.isEmpty";
		nFunRes = -1;
		return nFunRes;  
	}

	fileSQLStringXml.setFileName(strSQLStringXmlFile);  
	if (!fileSQLStringXml.open(QFile::ReadOnly | QFile::Text))
	{  
		MYLOG4CPP_ERROR<<"error! open strSQLStringXmlFile="<<strSQLStringXmlFile;
		//QMessageBox::information(NULL, QString("title"), QString("open error!"));
		nFunRes = -1;
		return nFunRes;
	}  
 
	if (!document.setContent(&fileSQLStringXml, false, &strGetError, &nGetRow, &nGetColumn))
	{  
		MYLOG4CPP_ERROR<<"error! parse file strSQLStringXmlFile="<<strSQLStringXmlFile
			<<" "<<"parse file failed at line row="<<nGetRow
			<<" "<<"column="<<nGetColumn
			<<" "<<"strGetError="<<strGetError;
		//QMessageBox::information(NULL, QString("title"), QString("parse file failed at line row and column") + QString::number(row, 10) + QString(",") + QString::number(column, 10));
		nFunRes = -1;
		return nFunRes; 
	}  

	if (document.isNull())
	{  
		MYLOG4CPP_ERROR<<"error! document is null!";
		//QMessageBox::information(NULL, QString("title"), QString("document is null!"));
		nFunRes = -1;
		return nFunRes; 
	}  

	node_Tables = document.documentElement();  
	//<Tables TableCount="2">
	node_Tables_tagname = node_Tables.tagName();//node_Tables_tagname is Tables
	if (node_Tables.hasAttribute("TableCount"))
	{
		//TableCount's value is 2
		node_Tables_TableCount = node_Tables.attributeNode("TableCount").value(); 
	}

	node_Tables_childlist = node_Tables.childNodes();
	node_Tables_childlist_count = node_Tables_childlist.count();


	for (qint32 nIndex = 0; nIndex < node_Tables_childlist_count; nIndex++)
	{
		QDomNode Table;
		QDomElement node_Table;
		QString strTableName;
		QDomNodeList node_Table_childlist;
		qint32 node_Table_childlist_count = 0;

		Table = node_Tables_childlist.item(nIndex);
		node_Table = Table.toElement();
		if (node_Table.hasAttribute("TableName"))
		{
			strTableName = node_Table.attributeNode("TableName").value();
			//strTableName = node_Table.attribute("TableName");
		}

		node_Table_childlist = Table.childNodes();
		node_Table_childlist_count = node_Table_childlist.count();

		for (qint32 nIndexSQL = 0; nIndexSQL < node_Table_childlist_count; nIndexSQL++)
		{
			QDomNode SQL;
			QDomElement node_SQL;
			QString strSQLKey;
			QDomNodeList node_SQL_childlist;
			qint32 node_SQL_childlist_count = 0;
			CSQLData sqlData;

			SQL = node_Table_childlist.item(nIndexSQL);
			node_SQL = SQL.toElement();
			if (node_SQL.hasAttribute("SQLKey"))
			{
				strSQLKey = node_SQL.attributeNode("SQLKey").value();
			}
			sqlData.setSQLKeyValue(strSQLKey);

			node_SQL_childlist = SQL.childNodes();
			node_SQL_childlist_count = node_SQL_childlist.count();

			for (qint32 nIndexSQLStr = 0; nIndexSQLStr < node_SQL_childlist_count; nIndexSQLStr++)
			{
				QDomNode SQLStr;
				QDomElement node_SQLStr;
				QString strDBType;
				QString strTagName;
				QString strSQL;

				SQLStr = node_SQL_childlist.item(nIndexSQLStr);
				node_SQLStr = SQLStr.toElement();

				if (node_SQLStr.hasAttribute("DBType"))
				{
					strDBType = node_SQLStr.attribute("DBType");
					strTagName = node_SQLStr.tagName();//"DBType"
					strSQL = node_SQLStr.text();
					sqlData.setValue(strDBType, strSQL);
				}

			}//for node_SQL_childlist
			
			if (!strSQLKey.isEmpty())
			{
				CSQLData* pData = NULL;
				pData = new CSQLData();
				*pData = sqlData;
				mapSQLData.insert(sqlData.getSQLKey(), pData);
				pData = NULL;
			}


		}//for node_Table_childlist
	}//for node_root_childlist

	return nFunRes;
}

