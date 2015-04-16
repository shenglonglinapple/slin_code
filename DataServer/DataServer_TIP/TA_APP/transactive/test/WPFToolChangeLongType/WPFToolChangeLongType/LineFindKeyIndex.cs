using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{
    public class LineFindKeyIndex
    {
        public LineFindKeyIndex()
        {

        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="strLine"></param>
        /// <param name="strKey"></param>
        /// <returns>-1 or 0 1 2</returns>
        public System.Int32 findKeyIndexInLine(System.String strLine, System.String strKey)
        {
            System.Int32 nKeyIndexInLine = -1;

            if (strLine.Length <= 0)
            {
                // IndexOf Returns:
                //     The zero-based index position of value if that string is found, or -1 if
                //     it is not. If value is System.String.Empty, the return value is 0.

                nKeyIndexInLine = -1;
                return nKeyIndexInLine;
            }


            nKeyIndexInLine = strLine.IndexOf(strKey);
            if (-1 != nKeyIndexInLine)
            {
                return nKeyIndexInLine;
            }

            return nKeyIndexInLine;
        }

        /// <summary>
        /// ToUpper then find
        /// </summary>
        /// <param name="strLine"></param>
        /// <param name="strKey"></param>
        /// <returns></returns>
        public System.Int32 findUPKeyIndexInUPLine(System.String strLine, System.String strKey)
        {
            System.Int32 nKeyIndexInLine = -1;
            System.String strLineUp;
            System.String strKeyUp;

            if (strLine.Length <= 0)
            {
                // IndexOf Returns:
                //     The zero-based index position of value if that string is found, or -1 if
                //     it is not. If value is System.String.Empty, the return value is 0.

                nKeyIndexInLine = -1;
                return nKeyIndexInLine;
            }

            strLineUp = strLine.ToUpper();
            strKeyUp = strKey.ToUpper();

            nKeyIndexInLine = strLineUp.IndexOf(strKeyUp);
            if (-1 != nKeyIndexInLine)
            {
                return nKeyIndexInLine;
            }

            return nKeyIndexInLine;
        }

    }
}
