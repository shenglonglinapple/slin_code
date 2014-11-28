using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeCodeInfile
{
    public enum EProcessLineType
    {
        EProcessLineType_Begin,

        EProcessLineType_Copy,
        EProcessLineType_ChangeCode,

        EProcessLineType_End,
    };


    public class processFileChaneCode
    {
        private System.String m_strDataSrcFile;
        private System.String m_strDataDestFile;
        private LineCheckContainKey m_LineCheckContainKey;
        private processLineChaneCode m_processLineLongToInt32;


        public processFileChaneCode()
        {
            m_strDataSrcFile = System.String.Empty;
            m_strDataDestFile = System.String.Empty;

            m_LineCheckContainKey = new LineCheckContainKey();
            m_processLineLongToInt32 = new processLineChaneCode();
        }

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile, DataProcessParam pDataProcessParam)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;

            m_strDataSrcFile = strDataSrcFile;
            m_strDataDestFile = strDataDestFile;
            
            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile);
            
            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                _ProcessEachLine(strGetLineSrc, fileWriterHander, pDataProcessParam);
            }//end while

            fileReadHander.Close();
            fileWriterHander.Close();
        }



        public void _ProcessEachLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander, DataProcessParam pDataProcessParam)
        {
            System.Boolean bCheckContainKey = false;
            System.String strLineDest = System.String.Empty;
            EProcessLineType nProcessLineType = EProcessLineType.EProcessLineType_Copy;
           
            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine {0}", strLineSrc));

            bCheckContainKey = false;
            m_LineCheckContainKey.reSetLine(strLineSrc);
            bCheckContainKey = m_LineCheckContainKey.checkContainKey(pDataProcessParam);
            if (bCheckContainKey)
            {
                nProcessLineType = EProcessLineType.EProcessLineType_ChangeCode;
            }

            switch (nProcessLineType)
            {
                case EProcessLineType.EProcessLineType_Copy:
                    {
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                case EProcessLineType.EProcessLineType_ChangeCode:
                    {
                        //process
                        strLineDest = "//";
                        strLineDest += strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);

                        strLineDest = strLineSrc;
                        strLineDest = m_processLineLongToInt32.processLine(strLineSrc, pDataProcessParam);
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                default:
                    {
                        //copy
                        fileWriterHander.WriteLine(strLineSrc);
                        break;
                    }

            }//switch

            return;
        }


    }//public class processFileLongToInt32
}//namespace WPFToolChangeLongType
