using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolFindKeyLine
{
    enum EProcessLineType
    {
        EProcessLineType_InValidline,
        EProcessLineType_NotHaveKey,
        EProcessLineType_HaveKey,
    };


    class ProcessEachFile
    {
        private System.String m_strLineKey_Key = System.String.Empty;
   

        public ProcessEachFile()
        {
            //m_strLineKey_prepareSQLStatement = "->prepareSQLStatement(";
            m_strLineKey_Key = "prepareSQLStatement";
        }

        public void setLineKey(System.String strLineKey)
        {
            this.m_strLineKey_Key = strLineKey;
        }


        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;

            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile, true);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                processOneLine(strGetLineSrc, fileWriterHander);
            }

            fileReadHander.Close();
            fileWriterHander.Flush();
            fileWriterHander.Close();

        }//processFile



        public void processOneLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander)
        {
            System.String strLineDest = System.String.Empty;
            EProcessLineType nProcessLineType = EProcessLineType.EProcessLineType_NotHaveKey;

            nProcessLineType = CheckProcessLineType(strLineSrc);

            switch (nProcessLineType)
            {
                case EProcessLineType.EProcessLineType_NotHaveKey:
                    {
                        break;
                    }
                case EProcessLineType.EProcessLineType_InValidline:
                    {
                        break;
                    }
                case EProcessLineType.EProcessLineType_HaveKey:
                    {
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                default:
                    {
                        //fileWriterHander.WriteLine(strLineSrc);
                        break;
                    }

            }//switch
            
            return;
        }

        public EProcessLineType CheckProcessLineType(System.String strLineSrc)
        {
            EProcessLineType nProcessLineType = EProcessLineType.EProcessLineType_NotHaveKey;
            System.String strLineSrcTmp = strLineSrc;

            //lsl -- if line with "//" "/*" begin, then just copy
            strLineSrcTmp = strLineSrcTmp.Trim();
            if (0 == strLineSrcTmp.IndexOf("//") || 0 == strLineSrcTmp.IndexOf("/*"))
            {
                nProcessLineType = EProcessLineType.EProcessLineType_InValidline;
                return nProcessLineType;
            }

            if (strLineSrc.Contains(m_strLineKey_Key))
            {
                nProcessLineType = EProcessLineType.EProcessLineType_HaveKey;
                return nProcessLineType;
            }

            nProcessLineType = EProcessLineType.EProcessLineType_NotHaveKey;

            return nProcessLineType;
        }//CheckProcessLineType







    }//class ProcessFileSQLObject
}//namespace WPFToolFindKeyLine
