using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.International.Converters.PinYinConverter;//导入拼音相关



namespace WPFToolProcessFile
{
    public class ProcessFileSSSZStock
    {

        public ProcessFileSSSZStock()
        {
            
        }
        
        //API
        public string GetFirstPinyin(string strHanZiArray)
        {
            string strFirstPinYinArray = string.Empty;
            foreach (char obj in strHanZiArray)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);

                    string strTemp = chineseChar.Pinyins[0].ToString();
                    //PU
                    //P
                    strFirstPinYinArray += strTemp.Substring(0, 1);
                }
                catch
                {
                    strFirstPinYinArray += obj.ToString();
                }
            }
            return strFirstPinYinArray;
        }

        //API
        /// <summary> 
        /// 汉字转化为拼音
        /// </summary> 
        /// <param name="str">汉字</param> 
        /// <returns>全拼</returns> 
        public string GetHanZi_PinYin_Full_0(string strOneHanZi)
        {
            string strOneHanZiPinYinFull_0 = string.Empty;
            foreach (char obj in strOneHanZi)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);
                    //PU3
                    //PU5
                    string strTemp = chineseChar.Pinyins[0].ToString();
                    //PU
                    strOneHanZiPinYinFull_0 += strTemp.Substring(0, strTemp.Length - 1);
                }
                catch
                {
                    strOneHanZiPinYinFull_0 += obj.ToString();
                }
                break;//
            }
            return strOneHanZiPinYinFull_0;
        }
        //API
        public string GetHanZiArray_PinYin_Full_0(string strHanZiArray)
        {
            string strPinYinFull_0 = string.Empty;
            foreach (char obj in strHanZiArray)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);
                    //PU3
                    //PU5
                    string strTemp = chineseChar.Pinyins[0].ToString();
                    //PU
                    strPinYinFull_0 += strTemp.Substring(0, strTemp.Length - 1);
                    strPinYinFull_0 += " ";
                }
                catch
                {
                    strPinYinFull_0 += obj.ToString();
                }
            }
            return strPinYinFull_0;
        }
        //API
        public string GetHanZi_PinYin_Full_4(string strOneHanZi)
        {
            string strPinYinFull_4 = string.Empty;
            foreach (char obj in strOneHanZi)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);
                    //PU3
                    //PU5
                    string strTemp = chineseChar.Pinyins[0].ToString();
                    //PU3
                    strPinYinFull_4 += strTemp;                    
                }
                catch
                {
                    strPinYinFull_4 += obj.ToString();
                }
                break;
            }
            return strPinYinFull_4;
        }
        //API
        public string GetHanZiArray_PinYin_Full_4(string strHanZiArray)
        {
            string strPinYinFull_4 = string.Empty;
            foreach (char obj in strHanZiArray)
            {
                try
                {
                    Microsoft.International.Converters.PinYinConverter.ChineseChar chineseChar =
                        new Microsoft.International.Converters.PinYinConverter.ChineseChar(obj);
                    //PU3
                    //PU5
                    string strTemp = chineseChar.Pinyins[0].ToString();
                    //PU3
                    strPinYinFull_4 += strTemp;
                    strPinYinFull_4 += " ";
                }
                catch
                {
                    strPinYinFull_4 += obj.ToString();
                }
            }
            return strPinYinFull_4;
        }


        /// <summary>
        /// 
        /// </summary>
        /// <param name="strDataSrcFile"></param>
        /// <param name="strDataDestFile"></param>

        public void processFile(StocksDbOper pStocksDbOper, System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;
            System.String str_Symbol_Extern = ".SS";


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
                    str_Symbol_Extern = ".SS";
                }
                else if (strDataSrcFile.Contains("SZ"))
                {
                    str_Symbol_Extern = ".SZ";
                }
                else
                {
                    str_Symbol_Extern = "";
                }
                _ProcessEachLine(pStocksDbOper, strGetLineSrc, fileWriterHander, str_Symbol_Extern);
            }//end while

            fileReadHander.Close();
            fileWriterHander.Close();

        }


        public void _ProcessEachLine(StocksDbOper pStocksDbOper, System.String strLineSrc, System.IO.StreamWriter fileWriterHander, System.String str_Symbol_Extern)
        {
            System.String strLineDest = System.String.Empty;
            System.String strLineCopy = strLineSrc;
            System.Int32 nFindFisrt = 0;
            System.Int32 nFindSecond = 0;
            System.String str_symbol = System.String.Empty;//201009
            //System.String str_symbolExtern = System.String.Empty;//.SS
            System.String str_symboluse = System.String.Empty;//201009.SS
            System.String str_namePinYinFirst = System.String.Empty;
            System.String str_namePinYinFull_0 = System.String.Empty;
            System.String str_namePinYinFull_4 = System.String.Empty;
            System.String str_name_utf8 = System.String.Empty;

            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine {0}", strLineSrc));
            strLineCopy = strLineSrc.Trim();
            if (strLineCopy.Length <= 0)
            {
                return;
            }
            //R002(201009)
            nFindFisrt = strLineCopy.IndexOf("(");
            nFindSecond = strLineCopy.IndexOf(")");

            str_name_utf8 = strLineCopy.Substring(0, nFindFisrt);//m_n_Name
            str_name_utf8 = str_name_utf8.Trim();
            str_namePinYinFirst = GetFirstPinyin(str_name_utf8);
            str_namePinYinFirst = str_namePinYinFirst.Trim();
            str_namePinYinFull_0 = GetHanZiArray_PinYin_Full_0(str_name_utf8);
            str_namePinYinFull_0 = str_namePinYinFull_0.Trim();
            str_namePinYinFull_4 = GetHanZiArray_PinYin_Full_4(str_name_utf8);
            str_namePinYinFull_4 = str_namePinYinFull_4.Trim();

            str_symbol = strLineCopy.Substring(nFindFisrt + 1, nFindSecond - nFindFisrt - 1);//m_s_Symbol
            str_symbol = str_symbol.Trim();
            str_symboluse = str_symbol + str_Symbol_Extern;

            strLineDest = "{";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest =  "\t"+ "/*Symbol*/" + "(\"" + str_symbol + "\"),";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest = "\t" + "/*SymbolExtern*/" + "(\"" + str_Symbol_Extern + "\"),";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest = "\t" + "/*SymbolUse*/" + "(\"" + str_symboluse + "\"),";
            fileWriterHander.WriteLine(strLineDest);


            strLineDest = "\t" + "/*NamePinYinFirst*/" + "(\"" + str_namePinYinFirst + "\"),";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest = "\t" + "/*NamePinYinFull0*/" + "(\"" + str_namePinYinFull_0 + "\"),";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest = "\t" + "/*NamePinYinFull4*/" + "(\"" + str_namePinYinFull_4 + "\"),";
            fileWriterHander.WriteLine(strLineDest);

            strLineDest = "\t" + "/*NameUtf8*/" + "(L\"" + str_name_utf8 + "\")";
            fileWriterHander.WriteLine(strLineDest);
            
             strLineDest = "},";
            fileWriterHander.WriteLine(strLineDest);


            // {
            // 	/*Symbol*/("600652"),
            // 	/*SymbolExtern*/(".SS"),
            // 	/*SymbolUse*/("600652.SS"),
            // 	/*NamePinYinFirst*/("ASGF"),
            // 	/*NamePinYinFull0*/("AI SI GU FEN"),
            // 	/*NamePinYinFull4*/("AI4 SI3 GU3 FEN4"),
            // 	/*NameUtf8*/(L"爱使股份")
            // },

            pStocksDbOper.AddToSQLArray(str_symboluse, str_namePinYinFirst, str_namePinYinFull_0, str_namePinYinFull_4, str_name_utf8);

            return;
        }
        
    }//class ProcessFileSSSZStock
}//namespace WPFToolProcessFile
