using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{
    public class LineOperChangeUserDefType
    {
        private LineCheckContainKey m_LineCheckContainKey;

        private System.String m_strCurrentLine = System.String.Empty;
        private System.String m_strFindWhat = System.String.Empty;
        private System.String m_strReplaceWith = System.String.Empty;


        public LineOperChangeUserDefType()
        {
            m_LineCheckContainKey = new LineCheckContainKey();
        }

        public System.String getReplacedLine(System.String strLine, System.String strFindWhat, System.String strReplaceWith)
        {
            System.String strReplacedLine;
            ECheckContainKey nECheckContainKey;

            //m_strCurrentLine = strLine;
            m_strFindWhat = strFindWhat;
            m_strReplaceWith = strReplaceWith;

            strReplacedLine = strLine;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_LineCheckContainKey.resetValue(strReplacedLine, strFindWhat);
            nECheckContainKey = m_LineCheckContainKey.checkContainKeyType();

            while (true)
            {
                strReplacedLine = _CheckAndGetReplacedLine(strReplacedLine, nECheckContainKey);

                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                m_LineCheckContainKey.resetValue(strReplacedLine, strFindWhat);
                nECheckContainKey = m_LineCheckContainKey.checkContainKeyType();
                if (ECheckContainKey.ECheckContainKey_NoKey == nECheckContainKey)
                {
                    break;//while
                }
            }
 
            return strReplacedLine;
        }

        private System.String _CheckAndGetReplacedLine(System.String strLine, ECheckContainKey nECheckContainKey)
        {
            System.String strReplacedLine;
           
            switch (nECheckContainKey)
            {
                case ECheckContainKey.ECheckContainKey_NoKey:
                    strReplacedLine = strLine;
                    break;
                case ECheckContainKey.ECheckContainKey_ContainKey:
                    strReplacedLine = _GetReplacedLineByKey(strLine, m_strFindWhat, m_strReplaceWith);
                    break;              
                default:
                    strReplacedLine = strLine;
                    break;
            }

            return strReplacedLine;
        }
                
        private System.String _GetReplacedLineByKey(System.String strLine, System.String strFindWhat, System.String strReplaceWith)
        {
            System.String strDestLine;

            System.String strLineLeft;
            System.String strLineRight;
            int nIndexOfKey = -1;
            int nStartIndex = 0;
            int nLength = 0;

            nIndexOfKey = strLine.IndexOf(strFindWhat);

            nStartIndex = 0;
            nLength = nIndexOfKey + strFindWhat.Length;
            strLineLeft = strLine.Substring(nStartIndex, nLength);

            nStartIndex = nLength;
            strLineRight = strLine.Substring(nStartIndex);

            strLineLeft = strLineLeft.Replace(strFindWhat, strReplaceWith);
            strDestLine = strLineLeft + strLineRight;

            return strDestLine;
        }




    }//LineOperChangeUserDefType
}//WPFToolChangeUserDefType
