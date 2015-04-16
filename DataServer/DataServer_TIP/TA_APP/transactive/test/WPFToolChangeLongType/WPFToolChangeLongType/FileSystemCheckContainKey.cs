using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{
    public class FileSystemCheckContainKey
    {
        private System.String m_strFullPath;//C://Sample//20121220.csv
        private LineCheckContainKey m_LineCheckContainKey;


        public FileSystemCheckContainKey()
        {
            m_LineCheckContainKey = new LineCheckContainKey();
        }
        public FileSystemCheckContainKey(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
            m_LineCheckContainKey = new LineCheckContainKey(strFullPath);
        }

        public void setFullPath(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
        }

        public void reSetFullPath(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
        }


        public System.Boolean checkContainKey()
        {
            System.Boolean bCheckRes = false;
            System.IO.StreamReader fileReadHander = null;

            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);

            fileReadHander = new System.IO.StreamReader(m_strFullPath);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                //check each line
                m_LineCheckContainKey.reSetLine(strGetLineSrc);
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
}//namespace WPFToolChangeLongType
