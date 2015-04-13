using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    enum EJobType
    {
        JobType_Begin,

        JobType_DoNothing,

        JobType_CopyFile,
        JobType_ChangeUserDefType,

        JobType_End,
    };//enum EChangeFileType

    class FileOperChangeUserDefType
    {
        DataChangeUserDefType m_pDataChangeUserDefType;
         //
        private FileOperCheckFileNameExtension m_pFileOperCheckFileNameExtension;
        private FileOperCheckContainKey m_pFileOperCheckContainKey;
        //
        private FileOperDoJobCopyFile m_pFileOperDoJobCopyFile;
        private FileOperDoJobUserDefType m_pFileOperDoJobUserDefType;
        //
        EJobType m_nDoJobType;

        public FileOperChangeUserDefType()
        {
            m_pDataChangeUserDefType = new DataChangeUserDefType();
            //
            m_pFileOperCheckFileNameExtension = new FileOperCheckFileNameExtension();
            m_pFileOperCheckContainKey = new FileOperCheckContainKey();
            m_pFileOperDoJobCopyFile = new FileOperDoJobCopyFile();
            m_pFileOperDoJobUserDefType = new FileOperDoJobUserDefType();

            m_nDoJobType = EJobType.JobType_DoNothing;
        }

        ~FileOperChangeUserDefType()
        {

        }

        public void processFile(DataChangeUserDefType pData)
        {
            m_pDataChangeUserDefType = pData;

            //FileExtenion
            if (m_pDataChangeUserDefType.m_strFileExtenion.Length > 0)
            {
                bool isFileExtenion = false;
                m_pFileOperCheckFileNameExtension.resetFileNameValue(m_pDataChangeUserDefType.m_strCurrentFileFrom, m_pDataChangeUserDefType.m_strFileExtenion);
                isFileExtenion = m_pFileOperCheckFileNameExtension.checkExtenion();
                if (false == isFileExtenion)
                {
                    //not process this file
                    return;
                }
            }

            m_nDoJobType = _CheckJobType(m_pDataChangeUserDefType);//m_pDataChangeUserDefType.m_strCurrentFileFrom

            switch (m_nDoJobType)
            {
                case EJobType.JobType_ChangeUserDefType:
                    m_pFileOperDoJobUserDefType.changeUserDefType(m_pDataChangeUserDefType);
                    break;
                case EJobType.JobType_CopyFile:
                    m_pFileOperDoJobCopyFile.processFile(
                        m_pDataChangeUserDefType.m_strCurrentFileFrom,
                        m_pDataChangeUserDefType.m_strCurrentFileTo);
                    break;
                default:
                    m_pFileOperDoJobCopyFile.processFile(
                        m_pDataChangeUserDefType.m_strCurrentFileFrom,
                        m_pDataChangeUserDefType.m_strCurrentFileTo);
                    break;
            }//switch

        }//processFile


        /// ////////////////////////////////////////////////////////////////////
        /// <summary>
        /// ////////////////////////////////////////////////////////////////////
        /// </summary>
        /// <param name="strDataSrcFile"></param>
        private EJobType _CheckJobType(DataChangeUserDefType pData)
        {
            EJobType nEProcessFileType = EJobType.JobType_DoNothing;
            bool bCheckFileContainKey = false;

            //check file contain Key
            bCheckFileContainKey = false;
            m_pFileOperCheckContainKey.resetValue(pData.m_strCurrentFileFrom, pData.m_strFindWhat);

            bCheckFileContainKey = m_pFileOperCheckContainKey.checkContainKey();
            if (false == bCheckFileContainKey)
            {
                nEProcessFileType = EJobType.JobType_CopyFile;
                return nEProcessFileType;
            }

            //need process 
            nEProcessFileType = EJobType.JobType_ChangeUserDefType;
            return nEProcessFileType;
        }//processFile

    }//class ProcessFileChangeUserDefType
}//namespace WPFToolChangeUserDefType
