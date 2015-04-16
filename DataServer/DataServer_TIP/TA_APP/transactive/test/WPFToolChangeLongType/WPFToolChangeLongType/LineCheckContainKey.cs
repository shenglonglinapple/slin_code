using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{

    public enum ECheckContainKey
    {
        ECheckContainKey_Begin,

        ECheckContainKey_NoKey,


        ECheckContainKey_unsigned_Space_long,
        ECheckContainKey_unsigned_Space_Space_long,
        ECheckContainKey_unsigned_Table_long,

        ECheckContainKey_long_space_int,
        ECheckContainKey_signed_space_long,

        ECheckContainKey_Space_long_Space,
        ECheckContainKey_Table_long_Table,
        ECheckContainKey_Space_long_Table,
        ECheckContainKey_Table_long_Space,

        ECheckContainKey_long_Point,
        ECheckContainKey_long_Space,
        ECheckContainKey_long_Table,


        ECheckContainKey_End,
    };

    public class LineCheckContainKey
    {
        private System.String m_strLine;
        ECheckContainKey m_nECheckContainKey;


        public System.String m_Key_long_space_long = "long long";

        public System.String m_Key_unsigned_Space_long = "unsigned long";
        public System.String m_Key_unsigned_Space_Space_long = "unsigned  long";
        public System.String m_Key_unsigned_Table_long = "unsigned\tlong";

        public System.String m_Key_long_space_int = "long int";
        public System.String m_Key_signed_space_long = "signed long";

        public System.String m_Key_Space_long_Space = " long ";
        public System.String m_Key_Table_long_Table = "\tlong\t";
        public System.String m_Key_Space_long_Table = " long\t";
        public System.String m_Key_Table_long_Space = "\tlong";
        public System.String m_Key_long_Point = "long*";
        public System.String m_Key_long_Space = "long ";
        public System.String m_Key_long_Table = "long\t";
 

        



        public LineCheckContainKey()
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = System.String.Empty;
        }

        public LineCheckContainKey(System.String strLine)
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = strLine;
        }

        public void setLine(System.String strLine)
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = strLine;
        }

        public void reSetLine(System.String strLine)
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = strLine;
        }


        public System.Boolean checkContainKey()
        {
            System.Boolean bCheckRes = false;

            bCheckRes = false;
            if (m_strLine.Length <= 0)
            {                
                return bCheckRes;
            }

            //m_strLine = m_strLine.ToLower();

            m_nECheckContainKey = checkContainKeyType();

            if (ECheckContainKey.ECheckContainKey_unsigned_Space_long == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_unsigned_Space_Space_long == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_unsigned_Table_long == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_long_space_int == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_signed_space_long == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_Space_long_Space == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_Table_long_Table == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_Space_long_Table == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_Table_long_Space == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_long_Point == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_long_Space == m_nECheckContainKey
                || ECheckContainKey.ECheckContainKey_long_Table == m_nECheckContainKey                
                )
            {
                bCheckRes = true;
            }

            return bCheckRes;
        }

        public ECheckContainKey checkContainKeyType()
        {
            ECheckContainKey nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            System.Int32 nIndexOfValue = -1;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;


            nIndexOfValue = m_strLine.IndexOf(m_Key_long_space_long);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_unsigned_Space_long);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_unsigned_Space_long;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_unsigned_Space_Space_long);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_unsigned_Space_Space_long;
                return nECheckContainKey;
            }
            
            nIndexOfValue = m_strLine.IndexOf(m_Key_unsigned_Table_long);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_unsigned_Table_long;
                return nECheckContainKey;
            }


            
            nIndexOfValue = m_strLine.IndexOf(m_Key_long_space_int);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_long_space_int;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_signed_space_long);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_signed_space_long;
                return nECheckContainKey;
            }


            nIndexOfValue = m_strLine.IndexOf(m_Key_Space_long_Space);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_Space_long_Space;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_Table_long_Table);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_Table_long_Table;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_Space_long_Table);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_Space_long_Table;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_Table_long_Space);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_Table_long_Space;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_long_Point);
            if (-1 != nIndexOfValue)
            {
                System.Boolean bCheckCharBeforLongRes = false;
                bCheckCharBeforLongRes = _CheckCharBeforLong(m_strLine, nIndexOfValue);
                if (bCheckCharBeforLongRes)
                {
                    nECheckContainKey = ECheckContainKey.ECheckContainKey_long_Point;
                    return nECheckContainKey;
                }
                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                return nECheckContainKey;
            }

            nIndexOfValue = m_strLine.IndexOf(m_Key_long_Space);
            if (-1 != nIndexOfValue)
            {
                System.Boolean bCheckCharBeforLongRes = false;
                bCheckCharBeforLongRes = _CheckCharBeforLong(m_strLine, nIndexOfValue);
                if (bCheckCharBeforLongRes)
                {
                    nECheckContainKey = ECheckContainKey.ECheckContainKey_long_Space;
                    return nECheckContainKey;
                }
                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                return nECheckContainKey;
            }


            nIndexOfValue = m_strLine.IndexOf(m_Key_long_Table);
            if (-1 != nIndexOfValue)
            {
                System.Boolean bCheckCharBeforLongRes = false;
                bCheckCharBeforLongRes = _CheckCharBeforLong(m_strLine, nIndexOfValue);
                if (bCheckCharBeforLongRes)
                {
                    nECheckContainKey = ECheckContainKey.ECheckContainKey_long_Table;
                    return nECheckContainKey;
                }
                nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
                return nECheckContainKey;
            }




            

            return nECheckContainKey;
        }

        public ECheckContainKey getECheckContainKey()
        {
            return m_nECheckContainKey;
        }


        private System.Boolean _CheckCharBeforLong(System.String strLine, System.Int32 nIndexOfValue)
        {
            System.Boolean bCheckCharBeforLongRes = false;
            System.String strCharBeforeLong;
            System.String strAZazString = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789_";
            char[] szArrayAZazString = strAZazString.ToCharArray();
            System.Int32 nIndex = -1;

            if (0 == nIndexOfValue)
            {
                bCheckCharBeforLongRes = true;
                return bCheckCharBeforLongRes;
            }

            strCharBeforeLong = m_strLine.Substring(nIndexOfValue - 1, 1);

            nIndex = strCharBeforeLong.IndexOfAny(szArrayAZazString);
            
            if (-1 == nIndex)
            {
                bCheckCharBeforLongRes = true;
            }
            else
            {
                bCheckCharBeforLongRes = false;
            }

            return bCheckCharBeforLongRes;
        }

    }//public class LineCheckContainKey
}//namespace WPFToolChangeLongType
