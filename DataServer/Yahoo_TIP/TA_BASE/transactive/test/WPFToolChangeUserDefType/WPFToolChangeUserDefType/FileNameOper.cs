using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    public class FileNameOper
    {
        private System.String m_strFullPath;//C://Sample//20121220.csv
        private System.String m_strDirectoryName;//C://Sample
        private System.String m_strFileName;//20121220.csv
        private System.String m_strFileNameWithoutExtension;//20121220
        private System.String m_strExtension;//csv

        public FileNameOper()
        {
            _ClearInfo();
        }


        ~FileNameOper()
        {

        }


        public void reSetFullPath(System.String strFullPath)
        {
            _ClearInfo();
            m_strFullPath = strFullPath;
            _GetInfo();
        }

        public System.String getExtension()
        {
            return m_strExtension;
        }

        private void _ClearInfo()
        {
            m_strFullPath = System.String.Empty;
            m_strDirectoryName = System.String.Empty;
            m_strFileName = System.String.Empty;
            m_strFileNameWithoutExtension = System.String.Empty;
            m_strExtension = System.String.Empty;
        }

        private void _GetInfo()
        {
            m_strDirectoryName = System.IO.Path.GetDirectoryName(m_strFullPath);
            m_strFileName = System.IO.Path.GetFileName(m_strFullPath);
            m_strFileNameWithoutExtension = System.IO.Path.GetFileNameWithoutExtension(m_strFullPath);
            m_strExtension = System.IO.Path.GetExtension(m_strFullPath);

            //string fullPath = @"\WebSite1\Default.aspx";
            //string filename = System.IO.Path.GetFileName(fullPath);//文件名  “Default.aspx”
            //string extension = System.IO.Path.GetExtension(fullPath);//扩展名 “.aspx”
            //string fileNameWithoutExtension = System.IO.Path.GetFileNameWithoutExtension(fullPath);// 没有扩展名的文件名 “Default”

        }



    }//FileNameOper
}
