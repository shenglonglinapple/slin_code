using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    public class FileOperCheckContainKey
    {
        private System.String m_strFileName = System.String.Empty;//C://Sample//20121220.csv
        private System.String m_strKey = System.String.Empty;

        private LineCheckContainKey m_LineCheckContainKey;

        public FileOperCheckContainKey()
        {
            m_LineCheckContainKey = new LineCheckContainKey();
        }

        public void resetValue(System.String strFileName, System.String strKey)
        {
            m_strFileName = strFileName;
            m_strKey = strKey;
        }


        public System.Boolean checkContainKey()
        {
            System.Boolean bCheckRes = false;
            System.IO.StreamReader fileReadHander = null;

            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);

            fileReadHander = new System.IO.StreamReader(m_strFileName);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                //check each line
                m_LineCheckContainKey.resetValue(strGetLineSrc, m_strKey);
                bCheckRes = m_LineCheckContainKey.checkContainKey();

                if (bCheckRes)
                {
                    break;
                }
            }

            fileReadHander.Close();

            return bCheckRes;
        }

    }//public class FileSystemCheckContainKey
}//namespace WPFToolChangeUserDefType
