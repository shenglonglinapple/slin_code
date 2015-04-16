#include "TestXMLFileParser.h"

#include <iostream>
#include <string>

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp> 
#include <boost/foreach.hpp>

using namespace boost;
using namespace boost::property_tree;

// static const std::string XMLATTR = "<xmlattr>";//it's an attribute
// static const std::string XMLCOMMENT = "<xmlcomment>";
// static const std::string XMLATTR_DOT = "<xmlattr>.";
// static const std::string XMLCOMMENT_DOT = "<xmlcomment>.";


CTestXMLFileParser::CTestXMLFileParser()
{

}

CTestXMLFileParser::~CTestXMLFileParser()
{

}

void CTestXMLFileParser::doTest()
{
// 	boost::property_tree::ptree  pt;
// 	boost::property_tree::read_xml("./cfg/ConnectionString.xml", pt);//read xml file
// 
// 	pt.get<std::string>();

	ptree pt; read_xml("./cfg/config.xml",pt); //读入一个xml文件 
	cout<<"ID is "<<pt.get<int>("con.id")<<endl; //读取节点中的信息 
	cout<<"Try Default"<<pt.get<int>("con.no_prop",100)<<endl; //如果取不到，则使用默认值 
	
	ptree child = pt.get_child("con"); //取一个子节点 
	cout<<"name is :"<<child.get<string>("name")<<endl; //对子节点操作，其实跟上面的操作一样  
	child = pt.get_child("con.urls"); 
	
	for(BOOST_AUTO(pos,child.begin()); pos != child.end(); ++pos) //boost中的auto 
	{ 
		cout<<"\t"+pos->second.data()<<endl; 
	} 

	pt.put("con.name","Sword"); //更改某个键值 
	pt.add("con.urls.url","http://www.baidu.com"); //增加某个键值
	write_xml("conf.xml",pt); //写入XML 
	getchar(); 
	//return 0;
}


void CTestXMLFileParser::doTestConfigTwo()
{
	char szXmlFile[] = "./cfg/ConfigTwo.xml";

	string strTmp;

	ptree pt;
	xml_parser::read_xml(szXmlFile, pt);

	BOOST_AUTO(child, pt.get_child("config.file"));
	for (BOOST_AUTO(pos, child.begin()); pos != child.end(); ++pos)
	{
		strTmp.clear();
		if ("<xmlattr>" == pos->first)
		{
			strTmp = pos->second.get<string>("title");		// 输出：windows
			cout<<strTmp<<"\t";

			strTmp = pos->second.get<string>("size");		// 输出：10Mb
			cout<<strTmp<<"\t";

			strTmp = pos->second.get<string>("noexits", "This is default");	
			cout<<strTmp<<endl;  // 输出：This is default
		}
		else if ("<xmlcomment>" == pos->first)
		{
			strTmp = pos->second.data();		// 第一次输出：File First Comment
			cout<<strTmp<<endl;		// 第二次输出：File Second Comment
		}
		else
		{
			BOOST_AUTO(nextchild, pos->second.get_child(""));
			for (BOOST_AUTO(nextpos, nextchild.begin()); nextpos != nextchild.end(); ++nextpos)
			{
				strTmp.clear();
				if ("<xmlattr>" == nextpos->first)
				{
					strTmp = nextpos->second.get<string>("attr");	// 输出：directory
					cout<<strTmp<<endl;
				}
				else if ("<xmlcomment>" == nextpos->first)
				{
					strTmp = nextpos->second.data();		// 输出：Paths Comment
					cout<<strTmp<<endl;
				}
				else
				{
					strTmp = nextpos->second.get<string>("<xmlattr>.title");
					cout<<strTmp<<"\t";

					strTmp = nextpos->second.data();
					cout<<strTmp<<endl;
				}
			}
		}

	}

}

void CTestXMLFileParser::doTestConfigConnectionString()
{
	/*
	<Config configAttr="configAttriValue">
	<!-- Comment: DBSYNC -->
	<DataTypeNode NodeIndexAttr="0" DataTypesAtrr="DBSYNC">
	<PriorityNode Priority="0" DBType="MYSQL" Schema="tra_occ" User="IT271350_5" Password="IT271350_5" Hostname="192.168.123.43">
	*/

	std::string strFileName;
	boost::property_tree::ptree  ptree_File;
	boost::property_tree::ptree  ptree_File_Child;
	boost::property_tree::ptree  ptree_File_Config;
	boost::property_tree::ptree  ptree_File_Config_Child;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_Child;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_PriorityNode;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_PriorityNode_Child;

	std::string XMLATTR = "<xmlattr>";//it's an attribute
	std::string XMLCOMMENT = "<xmlcomment>";
	std::string XMLATTR_DOT = "<xmlattr>.";
	std::string XMLCOMMENT_DOT = "<xmlcomment>.";
	std::string Def_Config = "Config";
	std::string Def_Config_configAttr = "configAttr";
	std::string Def_Config__DataTypeNode = "DataTypeNode";
	std::string Def_Config__DataTypeNode_NodeIndexAttr = "NodeIndexAttr";
	std::string Def_Config__DataTypeNode_DataTypesAtrr = "DataTypesAtrr";
	std::string Def_Config__DataTypeNode__PriorityNode = "PriorityNode";
	std::string Def_Config__DataTypeNode__PriorityNode_Priority = "Priority";
	std::string Def_Config__DataTypeNode__PriorityNode_DBType = "DBType";
	std::string Def_Config__DataTypeNode__PriorityNode_Schema = "Schema";
	std::string Def_Config__DataTypeNode__PriorityNode_User = "User";
	std::string Def_Config__DataTypeNode__PriorityNode_Password = "Password";
	std::string Def_Config__DataTypeNode__PriorityNode_Hostname = "Hostname";
	std::string strTmp;


	strFileName = "./cfg/ConnectionString.xml";

	try
	{
		boost::property_tree::read_xml(strFileName.c_str(), ptree_File);//read xml file


		BOOST_AUTO(ptree_File_Config, ptree_File.get_child(Def_Config));
		for (BOOST_AUTO(ptree_File_Config_Child, ptree_File_Config.begin()); 
			ptree_File_Config_Child != ptree_File_Config.end(); 
			++ptree_File_Config_Child)
		{
			strTmp.clear();
			//fisrt <xmlattr>
			//second <xmlcomment>
			//last datanode
			if (XMLATTR == ptree_File_Config_Child->first)
			{
				std::string get_configAttri;
				get_configAttri = ptree_File_Config_Child->second.get<std::string>(Def_Config_configAttr, "This is default");
				cout<<"get_configAttri="<<get_configAttri<<std::endl;
			}
			else if (XMLCOMMENT == ptree_File_Config_Child->first)
			{
				std::string get_Commment;
				get_Commment = ptree_File_Config_Child->second.data();
				cout<<"get_Commment="<<get_Commment<<std::endl;
			}
			else
			{
				//BOOST_AUTO(ptree_File_Config_DataTypeNode, ptree_File_Config_Child->second.get_child(Def_Config__DataTypeNode));//error
				BOOST_AUTO(ptree_File_Config_DataTypeNode, ptree_File_Config_Child->second.get_child(""));//ok
				for (BOOST_AUTO(ptree_File_Config_DataTypeNode_Child, ptree_File_Config_DataTypeNode.begin()); 
					ptree_File_Config_DataTypeNode_Child != ptree_File_Config_DataTypeNode.end();
					++ptree_File_Config_DataTypeNode_Child)
				{
					if (XMLATTR == ptree_File_Config_DataTypeNode_Child->first)
					{
						std::string get_NodeIndxAttri;
						std::string get_DataTypesAtrri;

						get_NodeIndxAttri = ptree_File_Config_DataTypeNode_Child->second.get<std::string>(Def_Config__DataTypeNode_NodeIndexAttr);
						cout<<"get_NodeIndxAttri="<<get_NodeIndxAttri<<endl;
						get_DataTypesAtrri = ptree_File_Config_DataTypeNode_Child->second.get<std::string>(Def_Config__DataTypeNode_DataTypesAtrr);
						cout<<"get_DataTypesAtrri="<<get_DataTypesAtrri<<endl;
					}
					else if (XMLCOMMENT == ptree_File_Config_DataTypeNode_Child->first)
					{
						std::string get_Commment;
						get_Commment = ptree_File_Config_Child->second.data();
						cout<<"get_Commment="<<get_Commment<<std::endl;
					}
					else
					{

						BOOST_AUTO(ptree_File_Config_DataTypeNode_PriorityNode, ptree_File_Config_DataTypeNode_Child->second.get_child(""));//ok
						for (BOOST_AUTO(ptree_File_Config_DataTypeNode_PriorityNode_Child, ptree_File_Config_DataTypeNode_PriorityNode.begin()); 
							ptree_File_Config_DataTypeNode_PriorityNode_Child != ptree_File_Config_DataTypeNode_PriorityNode.end();
							++ptree_File_Config_DataTypeNode_PriorityNode_Child)
						{
							if (XMLATTR == ptree_File_Config_DataTypeNode_PriorityNode_Child->first)
							{
								std::string get_Priority;
								std::string get_DBType;
								std::string get_Schema;
								std::string get_User;
								std::string get_Password;
								std::string get_Hostname;

								get_Priority = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Priority);
								cout<<"get_Priority="<<get_Priority<<endl;

								get_DBType = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_DBType);
								cout<<"get_DBType="<<get_DBType<<endl;

								get_Schema = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Schema);
								cout<<"get_Schema="<<get_Schema<<endl;

								get_User = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_User);
								cout<<"get_User="<<get_User<<endl;

								get_Password = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Password);
								cout<<"get_Password="<<get_Password<<endl;

								get_Hostname = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Hostname);
								cout<<"get_Hostname="<<get_Hostname<<endl;

							}
							else if (XMLCOMMENT == ptree_File_Config_DataTypeNode_PriorityNode_Child->first)
							{
								std::string get_Commment;
								get_Commment = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.data();
								cout<<"get_Commment="<<get_Commment<<std::endl;
							}
							else
							{

							}
						}

					}
				}
			}
		}





	}
	catch (...)
	{
		cout<<"error! read_xml strFileName="<<strFileName<<std::endl;
	}



}


