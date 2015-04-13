using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeUserDefType
{

    public enum ECheckContainKey
    {
        ECheckContainKey_Begin,

        ECheckContainKey_NoKey,
        ECheckContainKey_ContainKey,


        ECheckContainKey_End,
    };

    public class LineCheckContainKey
    {
        private System.String m_strLine = System.String.Empty;
        private System.String m_strKey = System.String.Empty;
        ECheckContainKey m_nECheckContainKey;



        public LineCheckContainKey()
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = System.String.Empty;
            m_strKey = System.String.Empty;
        }


        public void resetValue(System.String strLine, System.String strKey)
        {
            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_strLine = strLine;
            m_strKey = strKey;
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
            m_strLine = m_strLine.ToUpper();
            m_strKey = m_strKey.ToUpper();

            m_nECheckContainKey = checkContainKeyType();
            if (ECheckContainKey.ECheckContainKey_ContainKey == m_nECheckContainKey)
            {
                bCheckRes = true;
            }
            else
            {
                bCheckRes = false;
            }

            return bCheckRes;
        }

        public ECheckContainKey checkContainKeyType()
        {
            ECheckContainKey nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            System.Int32 nIndexOfValue = -1;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;


            nIndexOfValue = m_strLine.IndexOf(m_strKey);
            if (-1 != nIndexOfValue)
            {
                //find key ok
                nECheckContainKey = ECheckContainKey.ECheckContainKey_ContainKey;
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
}//namespace WPFToolChangeUserDefType
