using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeCodeInfile
{
    public class processLineChaneCode
    {
        private LineCheckContainKey m_LineCheckContainKey;

        public processLineChaneCode()
        {
            m_LineCheckContainKey = new LineCheckContainKey();
        }

        public System.String processLine(System.String strLine, DataProcessParam pDataProcessParam)
        {
            System.String strDestLine;
            ECheckContainKey nECheckContainKey;

            strDestLine = strLine;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_LineCheckContainKey.setLine(strDestLine);
            nECheckContainKey = m_LineCheckContainKey.checkContainKeyType(pDataProcessParam);

            while (true)
            {
                strDestLine = _ProcessLineByType(strDestLine, nECheckContainKey, pDataProcessParam);

                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                m_LineCheckContainKey.setLine(strDestLine);
                nECheckContainKey = m_LineCheckContainKey.checkContainKeyType(pDataProcessParam);
                if (ECheckContainKey.ECheckContainKey_NoKey == nECheckContainKey)
                {
                    break;//while
                }
            }
 
            return strDestLine;
        }

        private System.String _ProcessLineByType(System.String strLine, ECheckContainKey nECheckContainKey, DataProcessParam pDataProcessParam)
        {
            System.String strDestLine;
            System.String strOldValueForReplace;
            System.String strNewValueForReplace;


            switch (nECheckContainKey)
            {
                case ECheckContainKey.ECheckContainKey_NoKey:
                    strDestLine = strLine;
                    break;
                case ECheckContainKey.ECheckContainKey_HaveKey:
                    strOldValueForReplace = pDataProcessParam.m_strStringSrc;
                    strNewValueForReplace = pDataProcessParam.m_strStringDest;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                default:
                    strDestLine = strLine;
                    break;
            }

            return strDestLine;
        }


 

        
        private System.String _Process_ECheckContainKey(System.String strLine, System.String strOldValueForReplace, System.String strNewValueForReplace)
        {
            System.String strDestLine;

            System.String strLineLeft;
            System.String strLineRight;
            int nIndexOfKey = -1;
            int nStartIndex = 0;
            int nLength = 0;

            nIndexOfKey = strLine.IndexOf(strOldValueForReplace);

            nStartIndex = 0;
            nLength = nIndexOfKey + strOldValueForReplace.Length;
            strLineLeft = strLine.Substring(nStartIndex, nLength);

            nStartIndex = nLength;
            strLineRight = strLine.Substring(nStartIndex);

            strLineLeft = strLineLeft.Replace(strOldValueForReplace, strNewValueForReplace);
            strDestLine = strLineLeft + strLineRight;

            return strDestLine;
        }




    }
}
