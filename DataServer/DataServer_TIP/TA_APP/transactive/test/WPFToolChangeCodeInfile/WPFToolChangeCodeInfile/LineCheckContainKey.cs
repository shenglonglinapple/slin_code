using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeCodeInfile
{

    public enum ECheckContainKey
    {
        ECheckContainKey_Begin,

        ECheckContainKey_NoKey,

        ECheckContainKey_HaveKey,


        ECheckContainKey_End,
    };

    public class LineCheckContainKey
    {
        private System.String m_strLine;
        ECheckContainKey m_nECheckContainKey;

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


        public System.Boolean checkContainKey(DataProcessParam pDataProcessParam)
        {
            System.Boolean bCheckRes = false;

            bCheckRes = false;
            if (m_strLine.Length <= 0)
            {                
                return bCheckRes;
            }
            //m_strLine = m_strLine.ToLower();

            m_nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            m_nECheckContainKey = checkContainKeyType(pDataProcessParam);

            if (ECheckContainKey.ECheckContainKey_HaveKey == m_nECheckContainKey)
            {
                bCheckRes = true;
            }

            return bCheckRes;
        }

        public ECheckContainKey checkContainKeyType(DataProcessParam pDataProcessParam)
        {
            ECheckContainKey nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            System.Int32 nIndexOfValue = -1;

            nECheckContainKey = ECheckContainKey.ECheckContainKey_NoKey;
            
            nIndexOfValue = m_strLine.IndexOf(pDataProcessParam.m_strStringSrc);
            if (-1 != nIndexOfValue)
            {
                nECheckContainKey = ECheckContainKey.ECheckContainKey_HaveKey;
                return nECheckContainKey;
            }      

            return nECheckContainKey;
        }

        public ECheckContainKey getECheckContainKey()
        {
            return m_nECheckContainKey;
        }



    }//public class LineCheckContainKey
}//namespace WPFToolChangeLongType
