#ifndef __CLASS_SQLSTRING_XML_PARSER_HH__
#define __CLASS_SQLSTRING_XML_PARSER_HH__

#include <QtCore/QString>
#include <QtCore/QMap>

class CSQLData;

class CSQLStringXmlParser 
{ 
public: 
	CSQLStringXmlParser(); 
	~CSQLStringXmlParser();
public:
	qint32 doParse(const QString& strSQLStringXmlFile, QMap<QString, CSQLData*>& mapSQLData);
}; 

#endif//__CLASS_SQLSTRING_XML_PARSER_HH__



