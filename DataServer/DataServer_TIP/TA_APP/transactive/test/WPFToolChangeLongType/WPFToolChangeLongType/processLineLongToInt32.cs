using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{
    public class processLineLongToInt32
    {
        private LineCheckContainKey m_LineCheckContainKey;

        public processLineLongToInt32()
        {
            m_LineCheckContainKey = new LineCheckContainKey();
        }

        public System.String processLine(System.String strLine)
        {
            System.String strDestLine;
            ECheckContainKey nECheckContainKey;

            strDestLine = strLine;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_LineCheckContainKey.setLine(strDestLine);
            nECheckContainKey = m_LineCheckContainKey.checkContainKeyType();

            while (true)
            {
                strDestLine = _ProcessLineByType(strDestLine, nECheckContainKey);

                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                m_LineCheckContainKey.setLine(strDestLine);
                nECheckContainKey = m_LineCheckContainKey.checkContainKeyType();
                if (ECheckContainKey.ECheckContainKey_NoKey == nECheckContainKey)
                {
                    break;//while
                }
            }
 
            return strDestLine;
        }

        private System.String _ProcessLineByType(System.String strLine, ECheckContainKey nECheckContainKey)
        {
            System.String strDestLine;
            System.String strOldValueForReplace;
            System.String strNewValueForReplace;

            System.String strNewValueForReplace_ta_int32 = " ta_int32 ";
            System.String strNewValueForReplace_ta_int32_Point = " ta_int32* ";
            System.String strNewValueForReplace_ta_uint32 = " ta_uint32 ";

            switch (nECheckContainKey)
            {
                case ECheckContainKey.ECheckContainKey_NoKey:
                    strDestLine = strLine;
                    break;
                case ECheckContainKey.ECheckContainKey_unsigned_Space_long:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_unsigned_Space_long;
                    strNewValueForReplace = strNewValueForReplace_ta_uint32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_unsigned_Space_Space_long:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_unsigned_Space_Space_long;
                    strNewValueForReplace = strNewValueForReplace_ta_uint32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_unsigned_Table_long:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_unsigned_Table_long;
                    strNewValueForReplace = strNewValueForReplace_ta_uint32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_long_space_int:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_long_space_int;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_signed_space_long:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_signed_space_long;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_Space_long_Space:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_Space_long_Space;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_Table_long_Table:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_Table_long_Table;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_Space_long_Table:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_Space_long_Table;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_Table_long_Space:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_Table_long_Space;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_long_Point:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_long_Point;
                    strNewValueForReplace = strNewValueForReplace_ta_int32_Point;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_long_Space:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_long_Space;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
                    strDestLine = _Process_ECheckContainKey(strLine, strOldValueForReplace, strNewValueForReplace);
                    break;
                case ECheckContainKey.ECheckContainKey_long_Table:
                    strOldValueForReplace = m_LineCheckContainKey.m_Key_long_Table;
                    strNewValueForReplace = strNewValueForReplace_ta_int32;
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
