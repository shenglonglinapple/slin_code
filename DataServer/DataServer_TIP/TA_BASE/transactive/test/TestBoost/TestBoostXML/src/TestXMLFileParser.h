#ifndef __CLASS_TEST_XML_FILE_PARSER_HH__
#define __CLASS_TEST_XML_FILE_PARSER_HH__

#include <iostream>


#include <map>
#include <vector>

using namespace std;


class CTestXMLFileParser
{
public:
	CTestXMLFileParser(); 
	~CTestXMLFileParser();
public:
	void doTest();
	void doTestConfigTwo();
	void doTestConfigConnectionString();
};


#endif//__CLASS_TEST_XML_FILE_PARSER_HH__