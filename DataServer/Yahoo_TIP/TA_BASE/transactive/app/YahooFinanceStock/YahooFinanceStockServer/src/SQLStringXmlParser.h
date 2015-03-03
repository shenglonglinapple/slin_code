#ifndef __CLASS_SQLSTRING_XML_PARSER_HH__
#define __CLASS_SQLSTRING_XML_PARSER_HH__

#include <QtCore/QString>
#include <QtCore/QMap>
#include <QtXml/QtXml>

class CSQLData;

class CSQLStringXmlParser 
{ 
public: 
	CSQLStringXmlParser(); 
	~CSQLStringXmlParser();
public:
	qint32 doParse(const QString& strXmlFileName, QMap<QString, CSQLData*>& mapSQLData);
private:
	qint32 _ParseDocumentXml( const QDomDocument& domDocumentXml, QMap<QString, CSQLData*>& mapSQLData );
	qint32 _ParseElementRoot( const QDomElement& elementRoot, QMap<QString, CSQLData*>& mapSQLData );
	qint32 _ParseElementRootChild( const QDomElement& elementRootChild, QMap<QString, CSQLData*>& mapSQLData );
	qint32 _ParseElementRootChildChild( const QDomElement& elementRootChildChild, CSQLData& sqlData);
}; 

#endif//__CLASS_SQLSTRING_XML_PARSER_HH__



