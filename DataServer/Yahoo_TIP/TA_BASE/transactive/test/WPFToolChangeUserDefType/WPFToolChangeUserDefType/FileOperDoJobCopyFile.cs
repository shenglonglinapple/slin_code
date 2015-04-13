using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ComponentModel;
using System.IO;


namespace WPFToolChangeUserDefType
{
    class FileOperDoJobCopyFile
    {
        public FileOperDoJobCopyFile()
        {

        }

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            log4net.LogManager.GetLogger("ExeLogger").Info(
    System.String.Format("JobType_DoJobCopyFile strDataSrcFile={0} strDataDestFile={1}",
                    strDataSrcFile,
                    strDataDestFile));

            System.IO.File.Copy(strDataSrcFile, strDataDestFile, true);

        }//processFile
    }
}
