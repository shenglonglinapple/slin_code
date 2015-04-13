using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    class FileOperCheckFileNameExtension
    {
        private System.String m_strFileName;//C://Sample//20121220.csv
        private FileNameOper m_pFileNameOper;
        public System.String m_strFileExtenion = System.String.Empty;
        

        public FileOperCheckFileNameExtension()
        {
            m_strFileName = System.String.Empty;
            m_pFileNameOper = new FileNameOper();
        }

        ~FileOperCheckFileNameExtension()
        {

        }



        public void resetFileNameValue(System.String strFileName, System.String strFileExtenion)
        {
            m_strFileName = strFileName;
            m_strFileExtenion = strFileExtenion;
            m_pFileNameOper.reSetFullPath(strFileName);
        }

        public System.Boolean checkExtenion()
        {
            System.Boolean bCheckRes = false;
            System.String strExtension = System.String.Empty;

            strExtension = m_pFileNameOper.getExtension();

            bCheckRes = false;
            if (strExtension.Equals(m_strFileExtenion))
            {
                bCheckRes = true;
            }
            return bCheckRes;
        }
        

    }//class FileSystemCheckExtension
}//namespace WPFToolChangeUserDefType
