using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeCodeInfile
{
    public class DataProcessParam
    {
        public System.String m_strStringSrc { get; set; }
        public System.String m_strStringDest { get; set; }
        public System.String m_strDataSrcPath { get; set; }
        public System.String m_strDataDestPath { get; set; }

        public DataProcessParam()
        {
            this.m_strStringSrc = "";
            this.m_strStringDest = "";
            this.m_strDataSrcPath = "";
            this.m_strDataDestPath = "";
        }

          // Copy constructor.
        public DataProcessParam(DataProcessParam previousObject)
        {
            this.m_strStringSrc = previousObject.m_strStringSrc;
            this.m_strStringDest = previousObject.m_strStringDest;
            this.m_strDataSrcPath = previousObject.m_strDataSrcPath;
            this.m_strDataDestPath = previousObject.m_strDataDestPath;
        }





    }//public class DataProcessParam
}//namespace WPFToolChangeCodeInfile
