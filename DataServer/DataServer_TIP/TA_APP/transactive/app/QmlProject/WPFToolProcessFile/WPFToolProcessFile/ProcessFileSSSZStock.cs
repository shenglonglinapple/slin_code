using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.International.Converters.PinYinConverter;//导入拼音相关



namespace WPFToolProcessFile
{
    class ProcessFileSSSZStock
    {

        public ProcessFileSSSZStock()
        {

        }


        /// <summary> 
        /// 汉字转化为拼音
        /// </summary> 
        /// <param name="str">汉字</param> 
        /// <returns>全拼</returns> 
        public string GetPinyin(string str)
        {
            string r = string.Empty;
            foreach (char obj in str)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);

                    string t = chineseChar.Pinyins[0].ToString();

                    r += t.Substring(0, t.Length - 1);

                }
                catch
                {
                    r += obj.ToString();
                }
            }
            return r;
        }

        /// <summary> 
        /// 汉字转化为拼音首字母
        /// </summary> 
        /// <param name="str">汉字</param> 
        /// <returns>首字母</returns> 
        public string GetFirstPinyin(string str)
        {
            string r = string.Empty;
            foreach (char obj in str)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);

                    string t = chineseChar.Pinyins[0].ToString();

                    r += t.Substring(0, 1);

                }
                catch
                {
                    r += obj.ToString();
                }
            }
            return r;
        }

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;
            System.String m_s_Symbol_Extern = ".SS";


            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                if (strDataSrcFile.Contains("SS"))
                {
                    m_s_Symbol_Extern = ".SS";
                }
                else if (strDataSrcFile.Contains("SZ"))
                {
                    m_s_Symbol_Extern = ".SZ";
                }
                _ProcessEachLine(strGetLineSrc, fileWriterHander, m_s_Symbol_Extern);
            }//end while

            fileReadHander.Close();
            fileWriterHander.Close();
        }

        public System.String _GetFirstCHSPinYin(System.String strName)
        {
            System.String strNameFirstCHSPinYin = System.String.Empty;
            System.Int32 nNameLen = 0;
            System.Int32 nIndex = 0;

            System.String strOneCHSPinYin;

            nNameLen = strName.Length;

            foreach (char strOneCHS in strName)
            {
                try
                {
                    strOneCHSPinYin = GetPinyin(strOneCHS.ToString());
                    strNameFirstCHSPinYin += strOneCHSPinYin.Substring(0, 1);

                }
                catch
                {
                    strNameFirstCHSPinYin += strOneCHS.ToString();
                }
            }
            return strNameFirstCHSPinYin;
        }
        
        public void _ProcessEachLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander, System.String m_s_Symbol_Extern)
        {
            System.String strLineDest = System.String.Empty;
            System.String strLineCopy = strLineSrc;
            System.Int32 nFindFisrt = 0;
            System.Int32 nFindSecond = 0;
            System.String m_n_Name = System.String.Empty;
            System.String m_s_Symbol = System.String.Empty;
            System.String m_n_NamePinYin = System.String.Empty;
            //System.String m_s_Symbol_Extern = ".SS";



            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine {0}", strLineSrc));
            strLineCopy = strLineSrc.Trim();
            if (strLineCopy.Length <= 0)
            {
                return;
            }
            //R002(201009)
            nFindFisrt = strLineCopy.IndexOf("(");
            nFindSecond = strLineCopy.IndexOf(")");
            m_n_Name = strLineCopy.Substring(0, nFindFisrt);//m_n_Name
            m_n_NamePinYin = _GetFirstCHSPinYin(m_n_Name);
            m_s_Symbol = strLineCopy.Substring(nFindFisrt + 1, nFindSecond - nFindFisrt - 1);//m_s_Symbol

            strLineDest = "{";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest =  "\t"+ "/*Symbol*/" + "(\"" + m_s_Symbol + "\"),";
            fileWriterHander.WriteLine(strLineDest);
            //strLineDest = "\t" + "/*Name*/" + "(\"" + m_n_Name + "\"),";
            //fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "/*NamePinYin*/" + "(\"" + m_n_NamePinYin + "\"),";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "/*SymbolExtern*/" + "(\"" + m_s_Symbol_Extern + "\")";
            fileWriterHander.WriteLine(strLineDest);
             strLineDest = "},";
            fileWriterHander.WriteLine(strLineDest);


// {
// 	/*Symbol*/("600652"),
// 	/*Name*/("爱使股份"),
// 	/*NamePinYin*/("ASGF")
// },

            return;
        }
        

/*
        public void _ProcessEachLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander, System.String m_s_Symbol_Extern)
        {
            System.String strLineDest = System.String.Empty;
            System.String strLineCopy = strLineSrc;
            System.Int32 nFindFisrt = 0;
            System.Int32 nFindSecond = 0;
            System.String m_n_Name = System.String.Empty;
            System.String m_s_Symbol = System.String.Empty;
            System.String m_n_NamePinYin = System.String.Empty;
            //System.String m_s_Symbol_Extern = ".SS";



            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine {0}", strLineSrc));
            strLineCopy = strLineSrc.Trim();
            if (strLineCopy.Length <= 0)
            {
                return;
            }
            //R002(201009)
            nFindFisrt = strLineCopy.IndexOf("(");
            nFindSecond = strLineCopy.IndexOf(")");
            m_n_Name = strLineCopy.Substring(0, nFindFisrt);//m_n_Name
            m_n_NamePinYin = _GetFirstCHSPinYin(m_n_Name);
            m_s_Symbol = strLineCopy.Substring(nFindFisrt + 1, nFindSecond - nFindFisrt - 1);//m_s_Symbol
            strLineDest = "ListElement";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "{";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "m_n_Name:" + "\"" + m_n_Name + "\"" + ";";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "m_s_Symbol:" + "\"" + m_s_Symbol + m_s_Symbol_Extern + "\"" + ";";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "m_s_Symbol_Extern:" + "\"" + m_s_Symbol_Extern + "\"";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "\t" + "m_n_NamePinYin:" + "\"" + m_n_NamePinYin + "\"";
            fileWriterHander.WriteLine(strLineDest);
            strLineDest = "}";
            fileWriterHander.WriteLine(strLineDest);
            
//                 ListElement
//                 {
//                     m_n_Name: "Apple Inc.";
//                     m_s_Symbol: "AAPL";
//                     m_s_Symbol_Extern: "",     
//                     m_l1_Last_Trade_Price_Only: "0.0";
//                     m_c6_Change_Realtime: "0.0";
//                     m_p2_Change_in_Percent: "0%"
//                 }
            

            return;
        }//_ProcessEachLine

   
*/

    }//class ProcessFileSSSZStock
}//namespace WPFToolChangeLongType
