using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{
    class FileSystemFindKeyLineIndex
    {

        private LineFindKeyIndex m_LineFindKeyIndex;
        
        public FileSystemFindKeyLineIndex()
        {
            m_LineFindKeyIndex = new LineFindKeyIndex();
        }

        /// <summary>
        /// 
        /// </summary>
        /// <param name="strFullPath"></param>
        /// <param name="strFindKey"></param>
        /// <returns>-1 or 1 2 3</returns>
        public System.Int32 findKeyLineIndex(System.String strFullPath, System.String strFindKey)
        {
            System.IO.StreamReader fileReadHander = null;
            System.Int32 nLineInFileIndex = -1;
            System.Int32 nKeyInLineIndex = -1;
            System.Boolean bFindKey = false;

            fileReadHander = new System.IO.StreamReader(strFullPath);

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            nLineInFileIndex = 1;
            bFindKey = false;
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                //check each line
                nKeyInLineIndex = m_LineFindKeyIndex.findKeyIndexInLine(strGetLineSrc, strFindKey);

                if (-1 != nKeyInLineIndex)
                {
                    bFindKey = true;
                    break;
                }
                nLineInFileIndex++;
            }

            fileReadHander.Close();

            if (false == bFindKey)
            {
                nLineInFileIndex = -1;
            }

            return nLineInFileIndex;
        }


        




    }
}
