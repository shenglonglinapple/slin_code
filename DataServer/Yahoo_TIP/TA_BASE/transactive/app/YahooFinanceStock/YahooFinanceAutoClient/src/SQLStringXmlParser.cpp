#include "SQLStringXmlParser.h"

#include "SQLData.h"




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
	QDomElement node_root;

	QDomNodeList node_root_childlist;
	qint32 node_root_childlist_count = 0;


	QString node_root_tagname;
	QString node_root_ArchiveAttriValue;

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

	node_root = document.documentElement();  
	//<Archive ArchiveAttri="ArchiveAttriValue">	
	node_root_tagname = node_root.tagName();//node_root_tagname is Archive
	if (node_root.hasAttribute("ArchiveAttri"))
	{
		//ArchiveAttri's value is ArchiveAttriValue
		node_root_ArchiveAttriValue = node_root.attributeNode("ArchiveAttri").value(); 
	}

	node_root_childlist = node_root.childNodes();
	node_root_childlist_count = node_root_childlist.count();

	for (qint32 nIndex=0; nIndex < node_root_childlist_count; nIndex++)
	{

	}//for



	//获取id="1"的节点
	QDomElement person = node_root.firstChildElement();  
	if(person.isNull()) 
	{
		nFunRes = -1;
		return nFunRes;
	}

	QString person_tag_name = person.tagName();

	//id为1
	QString id = person.attributeNode("id").value();

	//获取子节点，数目为2
	QDomNodeList list = node_root.childNodes();
	int count = list.count();
	for(int i=0; i
	{
		QDomNode dom_node = list.item(i);
		QDomElement element = dom_node.toElement();

		//获取id值，等价
		QString id_1 = element.attributeNode("id").value(); 
		QString id_2 = element.attribute("id");

		//获取子节点，数目为4，包括：name、age、email、website
		QDomNodeList child_list = element.childNodes();
		int child_count = child_list.count();
		for(int j=0; j
		{
			QDomNode child_dom_node = child_list.item(j);
			QDomElement child_element = child_dom_node.toElement();
			QString child_tag_name = child_element.tagName();
			QString child__tag_value = child_element.text();
		}
	}

	//按照name、age、email、website的顺序获取值
	QDomElement element = person.firstChildElement();  
	while(!element.isNull())
	{  
		QString tag_name = element.tagName();
		QString tag_value = element.text();
		element = element.nextSiblingElement();  
	} 

	return nFunRes;
}

