using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using Microsoft.International.Converters.PinYinConverter;//导入拼音相关
using Microsoft.International.Converters.TraditionalChineseToSimplifiedConverter;//繁简体互转

namespace WPFToolChangeLongType
{
    /*
       GetPinyin("风影");//获取全拼
        GetFirstPinyin("风影");//获取首字母
     */
    class CHSPinYinHelper
    {
        public CHSPinYinHelper()
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

        /// <summary> 
        /// 简体转换为繁体
        /// </summary> 
        /// <param name="str">简体字</param> 
        /// <returns>繁体字</returns> 
        public string GetTraditional(string str)
        {
            string r = string.Empty;
            r = ChineseConverter.Convert(str, ChineseConversionDirection.SimplifiedToTraditional);
            return r;
        }
        /// <summary> 
        /// 繁体转换为简体
        /// </summary> 
        /// <param name="str">繁体字</param> 
        /// <returns>简体字</returns> 
        public string GetSimplified(string str)
        {
            string r = string.Empty;
            r = ChineseConverter.Convert(str, ChineseConversionDirection.TraditionalToSimplified);
            return r;
        }


    }//CHSPinYinHelper
}//WPFToolChangeLongType



