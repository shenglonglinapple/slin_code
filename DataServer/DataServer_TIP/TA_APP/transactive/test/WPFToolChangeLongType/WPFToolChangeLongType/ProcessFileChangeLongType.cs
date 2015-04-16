using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;


namespace WPFToolChangeLongType
{
    enum EProcessFileType
    {
        EProcessFileType_Begin,

        EProcessFileType_DoNothing,
        EProcessFileType_Copy,
        EProcessFileType_ChangeLongType,

        EProcessFileType_End,
    };//enum EProcessFileType

    public class ProcessFileChangeLongType
    {
        //
        private FileSystemCheckExtension m_FileSystemCheckExtension;
        private FileSystemCheckContainKey m_FileSystemCheckContainKey;
        //
        private processFileCopy m_processFileCopy;
        private processFileLongToInt32 m_processFileLongToInt32;
        //
        EProcessFileType m_nEProcessFileType;

        public ProcessFileChangeLongType()
        {
            //
            m_FileSystemCheckExtension = new FileSystemCheckExtension();
            m_FileSystemCheckContainKey = new FileSystemCheckContainKey();
            m_processFileCopy = new processFileCopy();
            m_processFileLongToInt32 = new processFileLongToInt32();

            m_nEProcessFileType = EProcessFileType.EProcessFileType_DoNothing;
        }

        ~ProcessFileChangeLongType()
        {

        }


        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            m_nEProcessFileType = _CheckProcessFileType(strDataSrcFile);


//             {
//                 System.Diagnostics.StackTrace StackTraceTmp = new System.Diagnostics.StackTrace(true);
//                 System.Diagnostics.StackFrame StackFrameTmp = StackTraceTmp.GetFrame(0);
//                 NLog.LogManager.GetCurrentClassLogger().Info(" {0}:{1} {2} {3}", StackFrameTmp.GetFileName(), StackFrameTmp.GetFileLineNumber(),
//                     "processFile ", strDataSrcFile);
//             }


            switch (m_nEProcessFileType)
            {
                case EProcessFileType.EProcessFileType_ChangeLongType:
                    log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("processFileLongToInt32 {0}", strDataSrcFile));
                    m_processFileLongToInt32.processFile(strDataSrcFile, strDataDestFile);
                    break;
                default:
                    m_processFileCopy.processFile(strDataSrcFile, strDataDestFile);
                    break;
            }//switch

        }//processFile


        /// ////////////////////////////////////////////////////////////////////
        /// <summary>
        /// ////////////////////////////////////////////////////////////////////
        /// </summary>
        /// <param name="strDataSrcFile"></param>
        private EProcessFileType _CheckProcessFileType(System.String strDataSrcFile)
        {
            bool bCheckExtensionHCCpp = false;
            bool bCheckFileContainKey = false;

            EProcessFileType nEProcessFileType = EProcessFileType.EProcessFileType_DoNothing;

            //check extension  .h .c .cpp
            bCheckExtensionHCCpp = false;
            m_FileSystemCheckExtension.reSetFullPath(strDataSrcFile);
            bCheckExtensionHCCpp = m_FileSystemCheckExtension.checkExtenion_h_c_cpp();
            if (false == bCheckExtensionHCCpp)
            {
                nEProcessFileType = EProcessFileType.EProcessFileType_Copy;
                return nEProcessFileType;
            }

            //check file contain Key
            bCheckFileContainKey = false;
            m_FileSystemCheckContainKey.reSetFullPath(strDataSrcFile);
            bCheckFileContainKey = m_FileSystemCheckContainKey.checkContainKey();
            if (false == bCheckFileContainKey)
            {
                nEProcessFileType = EProcessFileType.EProcessFileType_Copy;
                return nEProcessFileType;
            }

            //need process 
            nEProcessFileType = EProcessFileType.EProcessFileType_ChangeLongType;
            return nEProcessFileType;
        }//processFile






    }//public class ProcessFileChangeLongType
}//namespace WPFToolChangeLongType
