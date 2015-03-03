#include "SQLStringXmlParser.h"

#include <QtCore/QFile>
#include <QtXml/QtXml>

#include "SQLData.h"
#include "Log4cppLogger.h"


static const char* DEF_VALUE_STR_ATTRI_TableCount = "TableCount";
static const char* DEF_VALUE_STR_ATTRI_TableName = "TableName";
static const char* DEF_VALUE_STR_ATTRI_SQLKey = "SQLKey";
static const char* DEF_VALUE_STR_ATTRI_DBType = "DBType";



CSQLStringXmlParser::CSQLStringXmlParser()
{
}

CSQLStringXmlParser::~CSQLStringXmlParser()
{

}


qint32 CSQLStringXmlParser::doParse( const QString& strXmlFileName, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;
	QFile xmlFile;
	QString strGetErrorInfo;  
	qint32 nGetErrorRow = 0;
	qint32 nGetErrorColumn = 0;
	QDomDocument domDocumentXml;  

	if (strXmlFileName.isEmpty())
	{
		MYLOG4CPP_ERROR<<"error! strXmlFileName isEmpty";
		nFunRes = -1;
		return nFunRes;  
	}

	xmlFile.setFileName(strXmlFileName);  
	if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
	{  
		MYLOG4CPP_ERROR<<"error! open strXmlFileName="<<strXmlFileName;
		//QMessageBox::information(NULL, QString("title"), QString("open error!"));
		nFunRes = -1;
		return nFunRes;
	}  

	if (!domDocumentXml.setContent(&xmlFile, false, &strGetErrorInfo, &nGetErrorRow, &nGetErrorColumn))
	{  
		MYLOG4CPP_ERROR<<"error! parse file"
			<<" "<<"strXmlFileName="<<strXmlFileName
			<<" "<<"nGetErrorRow="<<nGetErrorRow
			<<" "<<"nGetErrorColumn="<<nGetErrorColumn
			<<" "<<"strGetErrorInfo="<<strGetErrorInfo;
		//QMessageBox::information(NULL, QString("title"), QString("parse file failed at line row and column") + QString::number(row, 10) + QString(",") + QString::number(column, 10));
		nFunRes = -1;
		return nFunRes; 
	}  

	if (domDocumentXml.isNull())
	{  
		MYLOG4CPP_ERROR<<"error! domDocumentXml is null!";
		//QMessageBox::information(NULL, QString("title"), QString("document is null!"));
		nFunRes = -1;
		return nFunRes; 
	}  

	nFunRes = _ParseDocumentXml(domDocumentXml, mapSQLData);

	return nFunRes;
}


qint32 CSQLStringXmlParser::_ParseDocumentXml( const QDomDocument& domDocumentXml, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;

	QDomElement elementRoot;

	QString tagnameRoot;//"Tables"
	QString attriTableCount;//<Tables TableCount="2">

	elementRoot = domDocumentXml.documentElement();  
	//<Tables TableCount="2">
	tagnameRoot = elementRoot.tagName();//tagnameRoot is Tables
	if (elementRoot.hasAttribute(DEF_VALUE_STR_ATTRI_TableCount))
	{
		//TableCount's value is 2
		attriTableCount = elementRoot.attributeNode(DEF_VALUE_STR_ATTRI_TableCount).value(); 
		//attriTableCount = domElementTables.attribute(DEF_VALUE_STR_ATTRI_TableCount);
		//domElementRoot.text();
	}

	nFunRes = _ParseElementRoot(elementRoot, mapSQLData);
	return nFunRes;
}


qint32 CSQLStringXmlParser::_ParseElementRoot( const QDomElement& elementRoot, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;

	QDomNodeList rootChildNodeList;
	qint32 nRootChildNodeListCount = 0;

	rootChildNodeList = elementRoot.childNodes();
	nRootChildNodeListCount = rootChildNodeList.count();

	for (qint32 nIndex = 0; nIndex < nRootChildNodeListCount; nIndex++)
	{
		QDomNode rootChildNode;
		QDomElement elementRootChild;
		QString strTableName;

		rootChildNode = rootChildNodeList.item(nIndex);
		elementRootChild = rootChildNode.toElement();
		if (elementRootChild.hasAttribute(DEF_VALUE_STR_ATTRI_TableName))
		{
			strTableName = elementRootChild.attributeNode(DEF_VALUE_STR_ATTRI_TableName).value();
			//strTableName = elementRootChild.attribute(DEF_VALUE_STR_ATTRI_TableName);
		}
		nFunRes = _ParseElementRootChild(elementRootChild, mapSQLData);
	}//for 

	return nFunRes;
}


qint32 CSQLStringXmlParser::_ParseElementRootChild( const QDomElement& elementRootChild, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;

	QDomNodeList rootChildChildNodeList;
	qint32 rootChildChildNodeListCount = 0;

	rootChildChildNodeList = elementRootChild.childNodes();
	rootChildChildNodeListCount = rootChildChildNodeList.count();

	for (qint32 nIndex = 0; nIndex < rootChildChildNodeListCount; nIndex++)
	{
		QDomNode rootChildChildNode;
		QDomElement elementRootChildChild;
		QString strSQLKey;
		CSQLData sqlData;

		rootChildChildNode = rootChildChildNodeList.item(nIndex);
		elementRootChildChild = rootChildChildNode.toElement();
		strSQLKey.clear();
		if (elementRootChildChild.hasAttribute(DEF_VALUE_STR_ATTRI_SQLKey))
		{
			strSQLKey = elementRootChildChild.attributeNode(DEF_VALUE_STR_ATTRI_SQLKey).value();
		}
		if (!strSQLKey.isEmpty())
		{
			sqlData.setSQLKeyValue(strSQLKey);
			_ParseElementRootChildChild(elementRootChildChild, sqlData);

			CSQLData* pData = NULL;
			pData = new CSQLData();
			*pData = sqlData;
			mapSQLData.insert(sqlData.getSQLKey(), pData);
			pData = NULL;
		}

	}//for node_Table_childlist

	return nFunRes;
}


qint32 CSQLStringXmlParser::_ParseElementRootChildChild( const QDomElement& elementRootChildChild, CSQLData& sqlData)
{
	qint32 nFunRes = 0;

	QDomNodeList rootChildChildChildNodeList;
	qint32 rootChildChildChildNodeListCount = 0;
	
	rootChildChildChildNodeList = elementRootChildChild.childNodes();
	rootChildChildChildNodeListCount = rootChildChildChildNodeList.count();

	for (qint32 nIndex = 0; nIndex < rootChildChildChildNodeListCount; nIndex++)
	{
		QDomNode rootChildChildChildNode;
		QDomElement elementRootChildChildChild;
		QString strDBType;
		QString strTagName;
		QString strSQL;

		rootChildChildChildNode = rootChildChildChildNodeList.item(nIndex);
		elementRootChildChildChild = rootChildChildChildNode.toElement();

		if (elementRootChildChildChild.hasAttribute(DEF_VALUE_STR_ATTRI_DBType))
		{
			strDBType = elementRootChildChildChild.attribute(DEF_VALUE_STR_ATTRI_DBType);
			strTagName = elementRootChildChildChild.tagName();//"DBType"
			strSQL = elementRootChildChildChild.text();
			sqlData.setXMLValue(strDBType, strSQL);
		}

	}//for node_SQL_childlist

	return nFunRes;
}


#if 0

qint32 CSQLStringXmlParser::doParse( const QString& strXmlFileName, QMap<QString, CSQLData*>& mapSQLData )
{
	qint32 nFunRes = 0;
	QFile xmlFile;
	QString strGetErrorInfo;  
	qint32 nGetErrorRow = 0;
	qint32 nGetErrorColumn = 0;

	QDomDocument domDocumentXml;  
	QDomElement domElementTables;

	QDomNodeList domNodeListTable;
	qint32 domNodeListTableCount = 0;


	QString tagnameTables;//"Tables"
	QString attriTableCount;//<Tables TableCount="2">

	if (strXmlFileName.isEmpty())
	{
		MYLOG4CPP_ERROR<<"error! strXmlFileName isEmpty";
		nFunRes = -1;
		return nFunRes;  
	}

	xmlFile.setFileName(strXmlFileName);  
	if (!xmlFile.open(QFile::ReadOnly | QFile::Text))
	{  
		MYLOG4CPP_ERROR<<"error! open strXmlFileName="<<strXmlFileName;
		//QMessageBox::information(NULL, QString("title"), QString("open error!"));
		nFunRes = -1;
		return nFunRes;
	}  

	if (!domDocumentXml.setContent(&xmlFile, false, &strGetErrorInfo, &nGetErrorRow, &nGetErrorColumn))
	{  
		MYLOG4CPP_ERROR<<"error! parse file"
			<<" "<<"strXmlFileName="<<strXmlFileName
			<<" "<<"nGetErrorRow="<<nGetErrorRow
			<<" "<<"nGetErrorColumn="<<nGetErrorColumn
			<<" "<<"strGetErrorInfo="<<strGetErrorInfo;
		//QMessageBox::information(NULL, QString("title"), QString("parse file failed at line row and column") + QString::number(row, 10) + QString(",") + QString::number(column, 10));
		nFunRes = -1;
		return nFunRes; 
	}  

	if (domDocumentXml.isNull())
	{  
		MYLOG4CPP_ERROR<<"error! domDocumentXml is null!";
		//QMessageBox::information(NULL, QString("title"), QString("document is null!"));
		nFunRes = -1;
		return nFunRes; 
	}  

	domElementTables = domDocumentXml.documentElement();  
	//<Tables TableCount="2">
	tagnameTables = domElementTables.tagName();//node_Tables_tagname is Tables
	if (domElementTables.hasAttribute("TableCount"))
	{
		//TableCount's value is 2
		attriTableCount = domElementTables.attributeNode("TableCount").value(); 
	}

	domNodeListTable = domElementTables.childNodes();
	domNodeListTableCount = domNodeListTable.count();


	for (qint32 nIndex = 0; nIndex < domNodeListTableCount; nIndex++)
	{
		QDomNode Table;
		QDomElement node_Table;
		QString strTableName;
		QDomNodeList node_Table_childlist;
		qint32 node_Table_childlist_count = 0;

		Table = domNodeListTable.item(nIndex);
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
#endif