using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.ComponentModel;
using System.IO;


namespace WPFToolChangeLongType
{
    class processFileCopy
    {
        public processFileCopy()
        {

        }

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.File.Copy(strDataSrcFile, strDataDestFile, true);

        }//processFile
    }
}
