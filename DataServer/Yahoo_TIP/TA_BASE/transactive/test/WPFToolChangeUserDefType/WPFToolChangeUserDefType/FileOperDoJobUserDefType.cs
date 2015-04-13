using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    enum EProcessLineWorkType
    {
        LineWorkType_Copy,
        LineWorkType_ChangeUserDefType,
    };

    public class FileOperDoJobUserDefType
    {
        private DataChangeUserDefType m_pDataChangeUserDefType;
        
        private LineCheckContainKey m_pLineCheckContainKey;
        private LineOperChangeUserDefType m_pLineOperChangeUserDefType;
        private System.Boolean m_bFileContainKey;
        private FileOperCheckFileNameExtension m_pFileOperCheckFileNameExtension;
        private FileOperFindKeyLineIndex m_pFileOperFindKeyLineIndex;
        private LineOperFindKeyIndex m_pLineOperFindKeyIndex;


        public FileOperDoJobUserDefType()
        {
            m_pDataChangeUserDefType = new DataChangeUserDefType();

            m_pLineCheckContainKey = new LineCheckContainKey();
            m_pLineOperChangeUserDefType = new LineOperChangeUserDefType();
            m_pFileOperCheckFileNameExtension = new FileOperCheckFileNameExtension();
            m_pFileOperFindKeyLineIndex = new FileOperFindKeyLineIndex();
            m_pLineOperFindKeyIndex = new LineOperFindKeyIndex();
            m_bFileContainKey = false;

        }

        public void changeUserDefType(DataChangeUserDefType pData)
        {
            System.Int32 nLineIndexContainKey = -1;

            m_pDataChangeUserDefType = pData;

            log4net.LogManager.GetLogger("ExeLogger").Info(
                System.String.Format("JobType_ChangeUserDefType m_strCurrentFileFrom={0} m_strCurrentFileTo={1} m_strFindWhat={2} m_strReplaceWith={3}",
                                m_pDataChangeUserDefType.m_strCurrentFileFrom, m_pDataChangeUserDefType.m_strCurrentFileTo,
                                m_pDataChangeUserDefType.m_strFindWhat, m_pDataChangeUserDefType.m_strReplaceWith));
            
            nLineIndexContainKey = -1;
            m_bFileContainKey = false;

            nLineIndexContainKey = m_pFileOperFindKeyLineIndex.findKeyLineIndex(
                m_pDataChangeUserDefType.m_strCurrentFileFrom, m_pDataChangeUserDefType.m_strFindWhat);
            if (-1 == nLineIndexContainKey)
            {
                m_bFileContainKey = false;
            }
            else
            {
                m_bFileContainKey = true;
            }

            if (false == m_bFileContainKey)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("not have key m_strCurrentFileFrom={0} m_strFindWhat={1}",
                    m_pDataChangeUserDefType.m_strCurrentFileFrom, m_pDataChangeUserDefType.m_strFindWhat));
            }
            else
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("have key m_strCurrentFileFrom={0} m_strFindWhat={1}",
                    m_pDataChangeUserDefType.m_strCurrentFileFrom, m_pDataChangeUserDefType.m_strFindWhat));

                _DoProcessFileNomal();
            }

            
        }


        public void _DoProcessFileNomal()
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;
            
            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            fileReadHander = new System.IO.StreamReader(m_pDataChangeUserDefType.m_strCurrentFileFrom);
            fileWriterHander = new System.IO.StreamWriter(m_pDataChangeUserDefType.m_strCurrentFileTo);
            
            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {               
                _ProcessEachLine(strGetLineSrc, fileWriterHander);
            }//end while

            fileReadHander.Close();
            fileWriterHander.Close();
        }





        public void _ProcessEachLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander)
        {
            System.Boolean bCheckContainKey = false;
            System.String strLineDest = System.String.Empty;
            EProcessLineWorkType nProcessLineWorkType = EProcessLineWorkType.LineWorkType_Copy;


            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine strLineSrc={0}", strLineSrc));

            bCheckContainKey = false;
            m_pLineCheckContainKey.resetValue(strLineSrc, m_pDataChangeUserDefType.m_strFindWhat);
            bCheckContainKey = m_pLineCheckContainKey.checkContainKey();

            nProcessLineWorkType = EProcessLineWorkType.LineWorkType_Copy;
            if (bCheckContainKey)
            {
                nProcessLineWorkType = EProcessLineWorkType.LineWorkType_ChangeUserDefType;
            }
            
            switch (nProcessLineWorkType)
            {
                case EProcessLineWorkType.LineWorkType_Copy:
                    {
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                case EProcessLineWorkType.LineWorkType_ChangeUserDefType:
                    {
                        //process
                        //strLineDest = "//";
                        //strLineDest += strLineSrc;
                        //fileWriterHander.WriteLine(strLineDest);

                        strLineDest = strLineSrc;
                        strLineDest = m_pLineOperChangeUserDefType.getReplacedLine(
                            strLineSrc, m_pDataChangeUserDefType.m_strFindWhat, m_pDataChangeUserDefType.m_strReplaceWith);

                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                default:
                    {
                        //copy
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }

            }//switch

            return;
        }


    }//public class processFileLongToInt32
}//namespace WPFToolChangeUserDefType
