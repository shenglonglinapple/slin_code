using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolProcessFile
{
    class FileSystemCheckExtension
    {
        private System.String m_strFullPath;//C://Sample//20121220.csv
        private FileSystemItem m_FileSystemItem;
        //file.h file.H
        private System.String m_Key_Extension_h = ".h";
        private System.String m_Key_Extension_H = ".H";
        //file.c file.C
        private System.String m_Key_Extension_c = ".c";
        private System.String m_Key_Extension_C = ".C";
        //file.cpp file.Cpp file.CPP file.cPP
        private System.String m_Key_Extension_cpp = ".cpp";
        private System.String m_Key_Extension_Cpp = ".Cpp";
        private System.String m_Key_Extension_CPP = ".CPP";
        private System.String m_Key_Extension_cPP = ".cPP";

        public FileSystemCheckExtension()
        {
            m_strFullPath = System.String.Empty;
            m_FileSystemItem = new FileSystemItem();
        }

        public FileSystemCheckExtension(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
            m_FileSystemItem = new FileSystemItem(strFullPath);
        }

        ~FileSystemCheckExtension()
        {

        }

        public void setFullPath(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
            m_FileSystemItem.setFullPath(strFullPath);
        }

        public void reSetFullPath(System.String strFullPath)
        {
            m_strFullPath = strFullPath;
            m_FileSystemItem.reSetFullPath(strFullPath);
        }


        public System.Boolean checkExtenion_h_c_cpp()
        {
            System.Boolean bCheckRes = false;

            bCheckRes = false;
            if (checkExtenion_h() || checkExtenion_c() || checkExtenion_cpp())
            {
                bCheckRes = true;
            }

            return bCheckRes;
        }



        /// <summary>
        /// 
        /// </summary>
        /// <returns></returns>
        public System.Boolean checkExtenion_h()
        {
            System.Boolean bCheckRes = false;
            System.String strExtension = System.String.Empty;

            strExtension = m_FileSystemItem.getExtension();

            bCheckRes = false;
            if (strExtension.Equals(m_Key_Extension_h) || strExtension.Equals(m_Key_Extension_H))
            {
                bCheckRes = true;
            }
            return bCheckRes;
        }

        public System.Boolean checkExtenion_c()
        {
            System.Boolean bCheckRes = false;
            System.String strExtension = System.String.Empty;

            strExtension = m_FileSystemItem.getExtension();

            bCheckRes = false;
            if (strExtension.Equals(m_Key_Extension_c) || strExtension.Equals(m_Key_Extension_C))
            {
                bCheckRes = true;
            }
            return bCheckRes;
        }

        public System.Boolean checkExtenion_cpp()
        {
            System.Boolean bCheckRes = false;
            System.String strExtension = System.String.Empty;

            strExtension = m_FileSystemItem.getExtension();

            bCheckRes = false;
            if (strExtension.Equals(m_Key_Extension_cpp) 
                || strExtension.Equals(m_Key_Extension_Cpp)
                || strExtension.Equals(m_Key_Extension_CPP)
                || strExtension.Equals(m_Key_Extension_cPP)
                )
            {
                bCheckRes = true;
            }
            return bCheckRes;
        }



    }
}
