#include "ConfigXmlParser.h"

#include<boost/property_tree/ptree.hpp>
#include<boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp> 
#include <boost/foreach.hpp>

#include "core/DataAccess/src/DbStatusItem.h"
#include "core/DataAccess/src/DbStatusItemList.h"
#include "core/DataAccess/src/DbStatusManager.h"



using namespace boost;
using namespace boost::property_tree;

#include "core/utilities/src/BoostLogger.h"
USING_BOOST_LOG;

NS_BEGIN(TA_Base_Core)

static const std::string XMLATTR = "<xmlattr>";//it's an attribute
static const std::string XMLCOMMENT = "<xmlcomment>";
static const std::string XMLATTR_DOT = "<xmlattr>.";
static const std::string XMLCOMMENT_DOT = "<xmlcomment>.";

static const std::string Def_Config = "Config";
static const std::string Def_Config_configAttr = "configAttr";
static const std::string Def_Config__DataTypeNode = "DataTypeNode";
static const std::string Def_Config__DataTypeNode_NodeIndexAttr = "NodeIndexAttr";
static const std::string Def_Config__DataTypeNode_DataTypesAtrr = "DataTypesAtrr";
static const std::string Def_Config__DataTypeNode__PriorityNode = "PriorityNode";
static const std::string Def_Config__DataTypeNode__PriorityNode_Priority = "Priority";
static const std::string Def_Config__DataTypeNode__PriorityNode_DBType = "DBType";
static const std::string Def_Config__DataTypeNode__PriorityNode_Schema = "Schema";
static const std::string Def_Config__DataTypeNode__PriorityNode_User = "User";
static const std::string Def_Config__DataTypeNode__PriorityNode_Password = "Password";
static const std::string Def_Config__DataTypeNode__PriorityNode_Hostname = "Hostname";


static const std::string Def_Config__DataTypes_DBSYNC = "DBSYNC";
static const std::string Def_Config__DataTypes_ALARM = "ALARM";



CConfigXMLParser::CConfigXMLParser()
{

}

CConfigXMLParser::~CConfigXMLParser()
{

}

EDataTypes CConfigXMLParser::getDataTypesByString(const std::string& strDataTypes)
{
	EDataTypes nDataTypes = DataTypes_DbSync;

	if (Def_Config__DataTypes_DBSYNC == strDataTypes)
	{
		nDataTypes = DataTypes_DbSync;
	}
	else if (Def_Config__DataTypes_ALARM == strDataTypes)
	{
		nDataTypes = DataTypes_Alarm;
	}

	return nDataTypes;
}



EDbServerPriority CConfigXMLParser::getDbServerPriorityByInt(int nPriority)
{
	EDbServerPriority nDbServerPriority = DbServerPriority_0;

	switch (nPriority)
	{
	case DbServerPriority_0:
		nDbServerPriority = DbServerPriority_0;
		break;
	case DbServerPriority_1:
		nDbServerPriority = DbServerPriority_1;
		break;
	case DbServerPriority_2:
		nDbServerPriority = DbServerPriority_2;
		break;
	case DbServerPriority_3:
		nDbServerPriority = DbServerPriority_3;
		break;
	default:
		break;
	}


	return nDbServerPriority;
}

EDbServerType CConfigXMLParser::getDbServerTypeByString(const std::string& strDbServerType)
{
	EDbServerType nEDbServerType= DbServerType_OracleDb;

	if (defOracleDBName == strDbServerType)
	{
		nEDbServerType = DbServerType_OracleDb;
	}
	else if (defMysqlDBName == strDbServerType)
	{
		nEDbServerType = DbServerType_MysqlDb;
	}
	else if (defSQLiteDBName == strDbServerType)
	{
		nEDbServerType = DbServerType_SqliteDb;
	}

	return nEDbServerType;
}


/*
<Config configAttr="configAttriValue">
	<!-- Comment: DBSYNC -->
	<DataTypeNode NodeIndexAttr="0" DataTypesAtrr="DBSYNC">
		<PriorityNode Priority="0" DBType="MYSQL" Schema="tra_occ" User="IT271350_5" Password="IT271350_5" Hostname="192.168.123.43">
		</PriorityNode>
		...
	</DataTypeNode>
	...
</Config>
*/

int CConfigXMLParser::parserConfigFile(
	const std::string& strFileName, 
	CDbStatusManager::MapDataTypeDbStautsListItemT& mapDataTypeDbStautsList)
{
	int nFunRes = 0;

	boost::property_tree::ptree  ptree_File;
	boost::property_tree::ptree  ptree_File_Child;
	boost::property_tree::ptree  ptree_File_Config;
	boost::property_tree::ptree  ptree_File_Config_Child;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_Child;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_PriorityNode;
	boost::property_tree::ptree  ptree_File_Config_DataTypeNode_PriorityNode_Child;

	EDataTypes nDataTypes = DataTypes_DbSync;
	CDbStatusItemList* pDBStatusItemList = NULL;
	EDbServerPriority nDbServerPriority = DbServerPriority_0; 
	CDbStatusItem* pDbStatusItem = NULL;
	EDbServerType nDbServerType = DbServerType_OracleDb;
	EDbServerState nDbServerState = DbServerState_Online;

	try
	{
		boost::property_tree::read_xml(strFileName.c_str(), ptree_File);//read xml file


		BOOST_AUTO(ptree_File_Config, ptree_File.get_child(Def_Config));
		for (BOOST_AUTO(ptree_File_Config_Child, ptree_File_Config.begin()); 
			ptree_File_Config_Child != ptree_File_Config.end(); 
			++ptree_File_Config_Child)
		{
			//fisrt <xmlattr>
			//second <xmlcomment>
			//last datanode
			if (XMLATTR == ptree_File_Config_Child->first)
			{
				std::string get_configAttri;
				get_configAttri = ptree_File_Config_Child->second.get<std::string>(Def_Config_configAttr, "This is default");
				LOG_DEBUG<<"get_configAttri="<<get_configAttri;
			}
			else if (XMLCOMMENT == ptree_File_Config_Child->first)
			{
				std::string get_Commment;
				get_Commment = ptree_File_Config_Child->second.data();
				LOG_DEBUG<<"get_Commment="<<get_Commment;
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

						get_NodeIndxAttri = ptree_File_Config_DataTypeNode_Child->second.get<std::string>(Def_Config__DataTypeNode_NodeIndexAttr, "This is default");
						LOG_DEBUG<<"get_NodeIndxAttri="<<get_NodeIndxAttri;
						get_DataTypesAtrri = ptree_File_Config_DataTypeNode_Child->second.get<std::string>(Def_Config__DataTypeNode_DataTypesAtrr, "This is default");
						LOG_DEBUG<<"get_DataTypesAtrri="<<get_DataTypesAtrri;

						nDataTypes = getDataTypesByString(get_DataTypesAtrri);
						pDBStatusItemList = new CDbStatusItemList();
						pDBStatusItemList->m_nDataTypes = nDataTypes;

						mapDataTypeDbStautsList.insert(CDbStatusManager::MapDataTypeDbStautsListItemTypeT(
							nDataTypes, pDBStatusItemList));
						
					}
					else if (XMLCOMMENT == ptree_File_Config_DataTypeNode_Child->first)
					{
						std::string get_Commment;
						get_Commment = ptree_File_Config_Child->second.data();
						LOG_DEBUG<<"get_Commment="<<get_Commment;
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
								int get_Priority;
								std::string get_DBType;
								std::string get_Schema;
								std::string get_User;
								std::string get_Password;
								std::string get_Hostname;
								std::string strConString;
								nDbServerPriority = DbServerPriority_0;
								nDbServerType = DbServerType_OracleDb;
								pDbStatusItem = new CDbStatusItem();

								get_Priority = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<int>(Def_Config__DataTypeNode__PriorityNode_Priority, 0);
								LOG_DEBUG<<"get_Priority="<<get_Priority;

								get_DBType = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_DBType, "This is default");
								LOG_DEBUG<<"get_DBType="<<get_DBType;

								get_Schema = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Schema, "This is default");
								LOG_DEBUG<<"get_Schema="<<get_Schema;

								get_User = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_User, "This is default");
								LOG_DEBUG<<"get_User="<<get_User;

								get_Password = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Password, "This is default");
								LOG_DEBUG<<"get_Password="<<get_Password;

								get_Hostname = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.get<std::string>(Def_Config__DataTypeNode__PriorityNode_Hostname, "This is default");
								LOG_DEBUG<<"get_Hostname="<<get_Hostname;


								nDbServerPriority = getDbServerPriorityByInt(get_Priority);
								nDbServerType = getDbServerTypeByString(get_DBType);
								pDbStatusItem->m_nDataTypes = nDataTypes;
								pDbStatusItem->m_nDbServerPriority = nDbServerPriority;
								pDbStatusItem->m_nDbServerType = nDbServerType;
								pDbStatusItem->m_nDbServerState = nDbServerState;
								pDbStatusItem->m_strDbType = get_DBType;
								pDbStatusItem->m_strSchema = get_Schema;
								pDbStatusItem->m_strUser = get_User;
								pDbStatusItem->m_strPassword = get_Password;
								pDbStatusItem->m_strIP = get_Hostname;
								strConString = pDbStatusItem->getConnectionString();

								pDBStatusItemList->addItem(nDbServerPriority, pDbStatusItem);
								pDbStatusItem = NULL;

							}
							else if (XMLCOMMENT == ptree_File_Config_DataTypeNode_PriorityNode_Child->first)
							{
								std::string get_Commment;
								get_Commment = ptree_File_Config_DataTypeNode_PriorityNode_Child->second.data();
								LOG_DEBUG<<"get_Commment="<<get_Commment;
							}
							else
							{

							}
						}//BOOST_AUTO(ptree_File_Config_DataTypeNode_PriorityNode_Child
					}

				}//BOOST_AUTO(ptree_File_Config_DataTypeNode_Child
			}

		}//BOOST_AUTO(ptree_File_Config_Child





	}
	catch (...)
	{
		nFunRes = -1;
		LOG_ERROR<<"error! read_xml strFileName="<<strFileName;
	}


	return nFunRes;
}

NS_END(TA_Base_Core)

