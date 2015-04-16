using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace WPFToolChangeLongType
{
    enum EProcessFileLongToInt32Type
    {
        EProcessFileLongToInt32Type_Copy,
        EProcessFileLongToInt32Type_LongToInt32Type,
    };

    public class processFileLongToInt32
    {
        private System.String m_strDataSrcFile;
        private System.String m_strDataDestFile;
        private LineCheckContainKey m_LineCheckContainKey;
        private processLineLongToInt32 m_processLineLongToInt32;
        private System.Boolean m_bFileContainKeyInclue;
        private System.Boolean m_bNomalInsertKeyInclue;
        private System.String m_str_key_include_type = "#include \"core/types/src/ta_types.h\"";
        private FileSystemCheckExtension m_FileSystemCheckExtension;
        private FileSystemFindKeyLineIndex m_FileSystemFindKeyLineIndex;
        private LineFindKeyIndex m_LineFindKeyIndex;
        private System.String m_Key_jin_include_space = "#include";
        private System.String m_Key_jin_include_space_StdAfxh = "#include \"StdAfx.h\"";
        private System.String m_Key_jin_include_space_stdAfxh = "#include \"stdAfx.h\"";
        private System.String m_Key_jin_include_space_stdafxh = "#include \"stdafx.h\"";
        private System.String m_Key_jin_include_tab_StdAfxh = "#include\t\"StdAfx.h\"";
        private System.String m_Key_namespace = "namespace";
        private System.String m_Key_jin_define = "#define";

        public processFileLongToInt32()
        {
            m_strDataSrcFile = System.String.Empty;
            m_strDataDestFile = System.String.Empty;

            m_LineCheckContainKey = new LineCheckContainKey();
            m_processLineLongToInt32 = new processLineLongToInt32();
            m_FileSystemCheckExtension = new FileSystemCheckExtension();
            m_FileSystemFindKeyLineIndex = new FileSystemFindKeyLineIndex();
            m_LineFindKeyIndex = new LineFindKeyIndex();
            m_bFileContainKeyInclue = false;
            m_bNomalInsertKeyInclue = false;

            //m_str_key_include_type = "#include " + "\"" + "core/types/src/ta_types.h" + "\"";
        }

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            //TODO. insert #include ...
            System.Int32 nLineIndexContainKey = -1;
            m_bFileContainKeyInclue = false;
            m_bNomalInsertKeyInclue = false;

            nLineIndexContainKey = m_FileSystemFindKeyLineIndex.findKeyLineIndex(strDataSrcFile, m_Key_jin_include_space);
            if (-1 == nLineIndexContainKey)
            {
                m_bFileContainKeyInclue = false;
            }
            else
            {
                m_bFileContainKeyInclue = true;
            }

            /*
             * if file.h file.cpp file.c  not have  #include ... line then progam do nothing, 
             * man must insert line  #include "core/types/src/ta_types.h"
            */
            if (false == m_bFileContainKeyInclue)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("you must insert line {0}", strDataDestFile));

                m_bNomalInsertKeyInclue = false;
                _DoProcessFileManInsert(strDataSrcFile, strDataDestFile);

            }
            else
            {
                m_bNomalInsertKeyInclue = true;
                _DoProcessFileNomal(strDataSrcFile, strDataDestFile);
            }

            
        }


        public void _DoProcessFileNomal(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;
            System.Int32 nIndexContainKey = -1;

            m_strDataSrcFile = strDataSrcFile;
            m_strDataDestFile = strDataDestFile;
            
            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile);
            
            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                if (true == m_bNomalInsertKeyInclue)
                {
                    nIndexContainKey = m_LineFindKeyIndex.findUPKeyIndexInUPLine(strGetLineSrc, m_Key_jin_include_space_StdAfxh);
                    if (-1 != nIndexContainKey)
                    {
                        _ProcessEachLine(strGetLineSrc, fileWriterHander);
                        continue;
                    }
                    nIndexContainKey = m_LineFindKeyIndex.findKeyIndexInLine(strGetLineSrc, m_Key_jin_include_tab_StdAfxh);
                    if (-1 != nIndexContainKey)
                    {
                        _ProcessEachLine(strGetLineSrc, fileWriterHander);
                        continue;
                    }
                    

                    nIndexContainKey = m_LineFindKeyIndex.findKeyIndexInLine(strGetLineSrc, m_Key_jin_include_space);                    
                    if (-1 != nIndexContainKey)
                    {
                        fileWriterHander.WriteLine(m_str_key_include_type);
                        m_bNomalInsertKeyInclue = false;
                    }
                }

                _ProcessEachLine(strGetLineSrc, fileWriterHander);
            }//end while

            fileReadHander.Close();
            fileWriterHander.Close();
        }



        public void _DoProcessFileManInsert(System.String strDataSrcFile, System.String strDataDestFile)
        {
            System.IO.StreamReader fileReadHander = null;
            System.IO.StreamWriter fileWriterHander = null;
            System.Boolean bCheckExtenionH = false;
            System.Int32 nInsertPos = 0;
            System.Int32 nReadIndex = 0;
            System.Int32 nLineIndexContainKey = 0;

            m_strDataSrcFile = strDataSrcFile;
            m_strDataDestFile = strDataDestFile;

            m_FileSystemCheckExtension.setFullPath(strDataSrcFile);
            bCheckExtenionH = m_FileSystemCheckExtension.checkExtenion_h();
            if (false == bCheckExtenionH)
            {
                //file.cpp file.c
                nInsertPos = 0;
            }
            else
            {
                //nLineIndexContainKey = m_FileSystemFindKeyLineIndex.findKeyLineIndex(strDataSrcFile, m_Key_jin_include_space);
        
                nLineIndexContainKey = m_FileSystemFindKeyLineIndex.findKeyLineIndex(strDataSrcFile, m_Key_namespace);

                if (-1 == nLineIndexContainKey)
                {
                    nLineIndexContainKey = m_FileSystemFindKeyLineIndex.findKeyLineIndex(strDataSrcFile, m_Key_jin_define);
                    nLineIndexContainKey++;
                }

                nInsertPos = nLineIndexContainKey;
                if (-1 == nInsertPos) 
                {
                    nInsertPos = 0;
                }      
                
            }

            
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format(" I insert line at {0} {1}", nInsertPos, strDataDestFile));


            //System.IO.FileInfo fileinfo = new System.IO.FileInfo(strDataSrcFile);
            fileReadHander = new System.IO.StreamReader(strDataSrcFile);
            fileWriterHander = new System.IO.StreamWriter(strDataDestFile);

            if (0 == nInsertPos)
            {
                fileWriterHander.WriteLine(m_str_key_include_type);
            }

            System.String strGetLineSrc = System.String.Empty;
            // Read and display lines from the file until the end of 
            // the file is reached.
            nReadIndex = 1;
            while ((strGetLineSrc = fileReadHander.ReadLine()) != null)
            {
                if (nReadIndex == nInsertPos)
                {
                    fileWriterHander.WriteLine(m_str_key_include_type);
                }
                _ProcessEachLine(strGetLineSrc, fileWriterHander);
                nReadIndex++;
            }

            fileReadHander.Close();
            fileWriterHander.Close();
        }


        public void _ProcessEachLine(System.String strLineSrc, System.IO.StreamWriter fileWriterHander)
        {
            System.Boolean bCheckContainKey = false;
            System.String strLineDest = System.String.Empty;
            EProcessFileLongToInt32Type nProcessFileLongToInt32Type = EProcessFileLongToInt32Type.EProcessFileLongToInt32Type_Copy;

            
            //log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("_ProcessEachLine {0}", strLineSrc));

            bCheckContainKey = false;
            m_LineCheckContainKey.reSetLine(strLineSrc);
            bCheckContainKey = m_LineCheckContainKey.checkContainKey();
            nProcessFileLongToInt32Type = EProcessFileLongToInt32Type.EProcessFileLongToInt32Type_Copy;
            if (bCheckContainKey)
            {
                nProcessFileLongToInt32Type = EProcessFileLongToInt32Type.EProcessFileLongToInt32Type_LongToInt32Type;
            }
            
            switch (nProcessFileLongToInt32Type)
            {
                case EProcessFileLongToInt32Type.EProcessFileLongToInt32Type_Copy:
                    {
                        strLineDest = strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                case EProcessFileLongToInt32Type.EProcessFileLongToInt32Type_LongToInt32Type:
                    {
                        //process
                        strLineDest = "//";
                        strLineDest += strLineSrc;
                        fileWriterHander.WriteLine(strLineDest);

                        strLineDest = strLineSrc;
                        strLineDest = m_processLineLongToInt32.processLine(strLineSrc);
                        fileWriterHander.WriteLine(strLineDest);
                        break;
                    }
                default:
                    {
                        //copy
                        fileWriterHander.WriteLine(strLineSrc);
                        break;
                    }

            }//switch

            return;
        }


    }//public class processFileLongToInt32
}//namespace WPFToolChangeLongType
