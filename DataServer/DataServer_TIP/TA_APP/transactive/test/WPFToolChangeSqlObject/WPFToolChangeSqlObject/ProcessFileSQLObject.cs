using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeSqlObject
{
    enum EProcessLineType
    {
        EProcessLineType_Copy,
        EProcessLineType_Disable,
        EProcessLineType_ConvertToObject,
    };

    class SQLLineToSQLObject
    {
        private System.String m_strLine1_DisableSrc = System.String.Empty;
        private System.String m_strLine2_AssignSqlObject = System.String.Empty;
        private System.String m_strLine3_SqlObject = System.String.Empty;


        private System.String m_strSQLine_Src = System.String.Empty;
        private System.String m_strSQLine_Src_Part_1_AssigenStrSQL = System.String.Empty;
        private System.String m_strSQLine_Src_Part_2_DatabaseHandle = "databaseConnection";

        private System.String m_strSQLine_Src_Part_3_SQLParam = System.String.Empty;
        private System.Int32 m_nType = 0;
        
        

        public SQLLineToSQLObject(System.String strSQLLine)
        {
            m_nType = 0;
            m_strLine1_DisableSrc = "//" + strSQLLine;

            m_strSQLine_Src = strSQLLine;
            m_strSQLine_Src_Part_1_AssigenStrSQL = get_AssigenStrSQL(m_strSQLine_Src);//strSql
            m_strSQLine_Src_Part_2_DatabaseHandle = get_DatabaseHandle(m_strSQLine_Src);
            m_strSQLine_Src_Part_3_SQLParam = get_SQLParam(m_strSQLine_Src);


            m_strLine2_AssignSqlObject = "\t\tSQLStatement" + " " + m_strSQLine_Src_Part_1_AssigenStrSQL + ";";

            m_strLine3_SqlObject = "\t\t" + m_strSQLine_Src_Part_2_DatabaseHandle +"->prepareSQLStatement("
                + m_strSQLine_Src_Part_1_AssigenStrSQL + ","
                + m_strSQLine_Src_Part_3_SQLParam;

        }

        public void writeToFile(System.IO.StreamWriter fileWriterHander)
        {
            if (0 == m_nType)
            {
                fileWriterHander.WriteLine(m_strLine1_DisableSrc);
                fileWriterHander.WriteLine(m_strLine2_AssignSqlObject);
                fileWriterHander.WriteLine(m_strLine3_SqlObject);
            }
            else if (1 == m_nType)
            {
                fileWriterHander.WriteLine(m_strLine1_DisableSrc);
                fileWriterHander.WriteLine(m_strLine3_SqlObject);
            }

        }

        public System.String get_AssigenStrSQL(System.String strSQLLine)
        {
            System.String strGet = System.String.Empty;
            System.String strPartAssigen = System.String.Empty;
            Int32 nIndex = 0;
            m_nType = 0;


            //std::string strSql  = databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,
            string[] splitStrObject = strSQLLine.Split(new Char[] { '=' });
            //std::string strSql  
            //databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,

            strPartAssigen = splitStrObject[0];
            strPartAssigen = strPartAssigen.Trim();

            nIndex = strPartAssigen.IndexOf(" ");
            if (-1 == nIndex)
            {
                strGet = strPartAssigen;
            }
            else
            {
                strGet = strPartAssigen.Substring(nIndex + 1);
                strGet = strGet.Trim();
            }

            nIndex = strPartAssigen.IndexOf("std::string");
            if (-1 == nIndex)
            {
                m_nType = 1;
            }
            

            return strGet;
        }


        public System.String get_DatabaseHandle(System.String strSQLLine)
        {
            System.String strPartDatabaseSQL = System.String.Empty;
            System.String strPartDatabase = System.String.Empty;
            Int32 nIndex = 0;

            //std::string strSql  = databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,
            string[] splitStrObject = strSQLLine.Split(new Char[] { '=' });
            //std::string strSql  
            //databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,

            strPartDatabaseSQL = splitStrObject[1];
            strPartDatabaseSQL = strPartDatabaseSQL.Trim();

            nIndex = strPartDatabaseSQL.IndexOf("->");
            if (-1 == nIndex)
            {
                strPartDatabase = "databaseConnection";
            }
            else
            {
                strPartDatabase = strPartDatabaseSQL.Substring(0, nIndex);
                strPartDatabase = strPartDatabase.Trim();
            }

            return strPartDatabase;
        }


        public System.String get_SQLParam(System.String strSQLLine)
        {
            System.String strGet = System.String.Empty;
            Int32 nIndex = 0;

            //std::string strSql  = databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,
            nIndex = strSQLLine.IndexOf("(");
            //ALARMRULE_SELECT_1008,
            strGet = strSQLLine.Substring(nIndex + 1);

            return strGet;
        }
        
    }


    class ProcessFileSQLObject
    {


        private System.String m_strLineKey_prepareSQLStatement = System.String.Empty;
        private System.String m_strLineKey_AssigenStrSQL = "strSql";
        private System.String m_strLineKey_strSql_size = System.String.Empty;

        

        public ProcessFileSQLObject()
        {
            m_strLineKey_prepareSQLStatement = "->prepareSQLStatement(";
            m_strLineKey_strSql_size = "TA_ASSERT(" + m_strLineKey_AssigenStrSQL + ".size";
        }


        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;

            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                processOneLine(strGetLineSrc, fileWriterHander);
            }

            fileReadHander.Close();
            fileWriterHander.Close();

        }//processFile



        public void processOneLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander)
        {
            System.String strLineDest = System.String.Empty;
            EProcessLineType nProcessLineType = EProcessLineType.EProcessLineType_Copy;

            nProcessLineType = CheckProcessLineType(strLineSrc);

            switch (nProcessLineType)
            {
                case EProcessLineType.EProcessLineType_Copy:
                    {
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                case EProcessLineType.EProcessLineType_Disable:
                    {
                        strLineDest = "//";
                        strLineDest += strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        m_strLineKey_AssigenStrSQL = "strSql";
                        m_strLineKey_strSql_size = "TA_ASSERT(" + m_strLineKey_AssigenStrSQL + ".size";
                        break;
                    }
                case EProcessLineType.EProcessLineType_ConvertToObject:
                    {
                        processLineTypeConverToObject(strLineSrc, fileWriterHander);
                        m_strLineKey_AssigenStrSQL = get_AssigenStrSQL(strLineSrc);
                        m_strLineKey_strSql_size = "TA_ASSERT(" + m_strLineKey_AssigenStrSQL + ".size";

                        break;
                    }
                default:
                    {
                        fileWriterHander.WriteLine(strLineSrc);
                        break;
                    }

            }//switch
            
            return;
        }

        public EProcessLineType CheckProcessLineType(System.String strLineSrc)
        {
            EProcessLineType nProcessLineType = EProcessLineType.EProcessLineType_Copy;
            System.String strLineSrcTmp = strLineSrc;

            //lsl -- if line with "//" "/*" begin, then just copy
            strLineSrcTmp = strLineSrcTmp.Trim();
            if (0 == strLineSrcTmp.IndexOf("//") || 0 == strLineSrcTmp.IndexOf("/*"))
            {
                nProcessLineType = EProcessLineType.EProcessLineType_Copy;
                return nProcessLineType;
            }

            if (strLineSrc.Contains(m_strLineKey_strSql_size))
            {
                nProcessLineType = EProcessLineType.EProcessLineType_Disable;
                return nProcessLineType;
            }

            if (strLineSrc.Contains(m_strLineKey_prepareSQLStatement))
            {
                nProcessLineType = EProcessLineType.EProcessLineType_ConvertToObject;
                return nProcessLineType;
            }

            nProcessLineType = EProcessLineType.EProcessLineType_Copy;

            return nProcessLineType;
        }//CheckProcessLineType

        public void processLineTypeConverToObject(System.String strLineSrc, System.IO.StreamWriter fileWriterHander)
        {
            SQLLineToSQLObject sqlToObject = new SQLLineToSQLObject(strLineSrc);
            sqlToObject.writeToFile(fileWriterHander);
        }




        public System.String get_AssigenStrSQL(System.String strSQLLine)
        {
            System.String strGet = System.String.Empty;
            System.String strPartAssigen = System.String.Empty;
            Int32 nIndex = 0;

            //std::string strSql  = databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,
            string[] splitStrObject = strSQLLine.Split(new Char[] { '=' });
            //std::string strSql  
            //databaseConnection->prepareSQLStatement(ALARMRULE_SELECT_1008,

            strPartAssigen = splitStrObject[0];
            strPartAssigen = strPartAssigen.Trim();

            nIndex = strPartAssigen.IndexOf(" ");
            if (-1 == nIndex)
            {
                strGet = strPartAssigen;
            }
            else
            {
                strGet = strPartAssigen.Substring(nIndex + 1);
                strGet.Trim();
            }

            return strGet;
        }


    }//class ProcessFileSQLObject
}//namespace WPFToolChangeSqlObject
