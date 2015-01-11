using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

using System.ComponentModel; 
using System.IO;



namespace AnalyselogFileWPF
{
    /// <summary>
    /// Interaction logic for AnalyseLogFile.xaml
    /// </summary>
    public partial class AnalyseLogFile : Window
    {
        private System.String m_strButtonRunInitText = System.String.Empty;
		private System.String m_strButtonRunClickText = System.String.Empty;
		private System.String m_strLogPath = System.String.Empty;
		private System.String m_strLogFileExtenName = System.String.Empty;
		private System.String m_strDstLogPath = System.String.Empty;
		private System.String m_strSysLog = System.String.Empty;
        private System.IO.StreamWriter m_logHandle = null;
        private FileInfo[] m_lstLogFileInfos;
        private IDictionary<int, string> m_mapLogIndexAndFileName; 
        private int m_nLogFileCount = 0;
        private IDictionary<string, StreamWriter> m_mapThreadNumAndFileName; 
        private System.ComponentModel.BackgroundWorker m_backgroundWorkerAnalystFile;



        public AnalyseLogFile()
        {
            InitializeComponent();          
            
            InitializeData();
            InitializeEvent();

        }

        
        //////////////////////////////////////////////////////////////////////////

        private void InitializeData()
        {
            this.m_strButtonRunInitText = "OneThreadOneFile";
            this.m_strButtonRunClickText = "Run...";
            this.m_strLogPath = "";//"D:\\Temp\\logPath\\";
            this.m_strLogFileExtenName = "*.*";//"*.log";
            this.m_strDstLogPath = "./DstLogPath/";
            this.m_strSysLog = "./DstLogPath/ThreadInfoLog.log";
            this.m_logHandle = null;
            this.m_lstLogFileInfos = null;
            this.m_mapLogIndexAndFileName = null;
            this.m_nLogFileCount = 0;
            this.m_mapThreadNumAndFileName = null;
            this.m_backgroundWorkerAnalystFile = null;

            this.m_backgroundWorkerAnalystFile = new System.ComponentModel.BackgroundWorker();

            m_mapLogIndexAndFileName = new Dictionary<int, string>();
            m_mapThreadNumAndFileName = new Dictionary<string, StreamWriter>();


        }//InitializeData
		
		private void InitializeEvent()
        {
            //create one thread to do work
			//register event  DoWork  RunWorkerCompleted

            this.m_backgroundWorkerAnalystFile.DoWork +=
                new System.ComponentModel.DoWorkEventHandler(this.BackgroundWorkerAnalystFile_DoWork);

            this.m_backgroundWorkerAnalystFile.RunWorkerCompleted +=
                new System.ComponentModel.RunWorkerCompletedEventHandler(this.BackgroundWorkerAnalystFile_RunWorkerCompleted);
		
        }//InitializeEvent
		
		


        private void buttonOneThreadOnefile_Click(object sender, System.Windows.RoutedEventArgs e)
        {
            this.buttonOneThreadOnefile.IsEnabled = false;
            //this.buttonOneThreadOnefile.Background = Brushes.Red;
            this.buttonOneThreadOnefile.Content = m_strButtonRunClickText;//"Run...";
              
            this.m_strLogPath = this.textBoxPath.Text;
            this.m_strLogFileExtenName = this.textBoxFileName.Text;

            //lsl for test         
            this.m_backgroundWorkerAnalystFile.RunWorkerAsync();

		}//buttonRun_Click

        private void BackgroundWorkerAnalystFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            //MessageBox.Show("Run begin");

            //CreateDirectory DstLogPath
            CreateDirectory(this.m_strDstLogPath);

            if (null == this.m_logHandle)
            {
				//System.IO.File.Delete(m_strSysLog);
                //this.m_logHandle = new StreamWriter(File.Open(m_strSysLog, System.IO.FileMode.Append, FileAccess.Write));
                //this.m_logHandle = new System.IO.StreamWriter(m_strSysLog);
            }  

            //get all File name in path
            this.m_lstLogFileInfos = getFiles(this.m_strLogPath, this.m_strLogFileExtenName);
  			if (null == this.m_lstLogFileInfos)
            {
				return;
            }
            
            //get index in file name
            getLogIndexFileMap(this.m_lstLogFileInfos, this.m_mapLogIndexAndFileName);

            //Analyse all file 
            this.m_nLogFileCount = this.m_mapLogIndexAndFileName.Count;
            AnalyseAllFiles(this.m_mapLogIndexAndFileName, m_mapThreadNumAndFileName);
            
            this.m_mapLogIndexAndFileName.Clear();
            m_mapThreadNumAndFileName.Clear();

        }//BackgroundWorkerAnalystFile_DoWork
        
        private void BackgroundWorkerAnalystFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            //this.buttonOneThreadOnefile.Background = Brushes.Green;
            this.buttonOneThreadOnefile.Content = m_strButtonRunInitText;//"Run";
            this.buttonOneThreadOnefile.IsEnabled = true;

			MessageBox.Show("Analyst To Thread File Work end");
		}//BackgroundWorkerAnalystFile_RunWorkerCompleted

		private void AnalyselogFileWPF_Loaded(object sender, System.Windows.RoutedEventArgs e)
        {
            //this.buttonOneThreadOnefile.Background = Brushes.Green;
            this.buttonOneThreadOnefile.Content = m_strButtonRunInitText;//"Run";
            this.buttonOneThreadOnefile.IsEnabled = true;
            
            //获取应用程序的当前工作目录
            var varCurrentPath = AppDomain.CurrentDomain.BaseDirectory;  
            this.textBoxPath.Text = varCurrentPath.ToString();

		}//ThreadInfoWindow_Loaded

        //////////////////////////////////////////////////////////////////////////
        /// <summary>
        /// get all file names in Path
        /// </summary>
        /// <param name="strPath"></param>
        /// <param name="strFileType"></param>
        /// <returns></returns>
        private FileInfo[] getFiles(string strPath, string strFileType)
        {
            System.IO.DirectoryInfo dirInfo;
            FileInfo[] filelist = null;

            // Specify the directories you want to manipulate.
            dirInfo = new System.IO.DirectoryInfo(strPath);

            try
            {
                // Determine whether the directory exists.
                if (!dirInfo.Exists)
                {
                    // Indicate that the directory already exists.

                    System.String strLog = String.Format("Error: That path not exists  strPath ={0}", strPath);
                    //this.m_logHandle.WriteLine(strLog);
                    return null;
                }

                //get all file
                filelist = dirInfo.GetFiles(strFileType);//"*.log"
               
            }
            catch
            {
				//this.m_logHandle.WriteLine("The process failed  catch");  
            }
            finally
            {
            }

            return filelist;

        }//getFiles


		/// <summary>
		/// getLogIndexFileMap
		/// AnalyseAllFileName in filelist, and add in map
		/// eg. 11	"D:\\Temp\\logPath\\s_SynchEngineLog.3004.11.log"
		/// </summary>
		/// <param name="filelist"></param>
		/// <param name="logIndexFileMap"></param>
		/// <returns></returns>
        private int getLogIndexFileMap(FileInfo[] filelist, IDictionary<int, string> logIndexFileMap)
        {
            int nFunRes = 0;
            System.String strLogFullName = "";//D:\\Temp\\logPath\\Sever_log.log.002 Sever_log.log
            System.String strLogFileName = "";   //Sever_log.log.002
            System.String strLogFileExtern = "";//002
            int nLogFileExtern = -1;//2

            int nLogIndex = -1;//2
            int nMaxTemp = 10000;

            //Sever_log.log      2015-01-21
            //Sever_log.log.001  2015-01-20
            //Sever_log.log.002  2015-01-19
            //[2015-01-09 18:14:45:528:][DEBUG][9768]

            try
            {

                foreach (FileInfo item in filelist)
                {
                    strLogFullName = item.FullName;
					strLogFileName = item.Name;
                    strLogFileExtern = item.Extension;

                    //D:\\Temp\\logPath\\Sever_log.log.002 Sever_log.log
                    if (".log" == strLogFileExtern)
                    {
                        nLogFileExtern = nMaxTemp;
                        nLogIndex = nLogFileExtern;
                    }
                    else
                    {
                        strLogFileExtern = strLogFileExtern.Substring(strLogFileExtern.IndexOf(".")+1);
                        nLogFileExtern = int.Parse(strLogFileExtern);
                        nLogIndex = nMaxTemp - nLogFileExtern;
                    }
                    

                    //add to map
                    {
                        //002
                        //10000
                        //D:\\Temp\\logPath\\Sever_log.log.002 Sever_log.log
                        logIndexFileMap.Add(nLogIndex, strLogFullName);                   
                    }


                }//foreach

            }
            catch
            {
                Console.WriteLine("The process failed  catch");
                nFunRes = -1;
            }
            finally
            {
                //
                //Console.WriteLine("finally");
            } 
            
            return nFunRes;
		}//getLogIndexFileMap


		/// <summary>
		/// AnalyseAllFiles
		/// </summary>
		/// <param name="logIndexFileMap"></param>
		/// <param name="mapThreadNumAndFileName"></param>
		/// <returns></returns>
        private int AnalyseAllFiles(IDictionary<int, string> logIndexFileMap, 
            IDictionary<string, StreamWriter> mapThreadNumAndFileName)
        {
            int nFunRes = 0;
            List<int> arrayLogIndexSort = null;
            System.String strEchoFilePath = "";
            StreamWriter dstFileHandle = null;

            //sort file index
            arrayLogIndexSort = new List<int>(logIndexFileMap.Keys);
            arrayLogIndexSort.Sort();

            //analyse file one by one
            foreach (int nLogIndex in arrayLogIndexSort)
            {
                strEchoFilePath = logIndexFileMap[nLogIndex];
                AnalyseFile(strEchoFilePath, mapThreadNumAndFileName);
            }

            //close all file handle
            foreach (KeyValuePair<string, StreamWriter> item in mapThreadNumAndFileName)
            {
                dstFileHandle = item.Value;
                dstFileHandle.Flush();
                dstFileHandle.Close();
            }
            arrayLogIndexSort.Clear();
            mapThreadNumAndFileName.Clear();

            return nFunRes;
        }//AnalyseAllFiles



		/// <summary>
		/// AnalyseFile
		/// Analyse each File
		/// </summary>
		/// <param name="strFileName"></param>
		/// <param name="mapThreadNumAndFileName"></param>
		/// <returns></returns>
        private int AnalyseFile(System.String strFileName,
            IDictionary<string, StreamWriter> mapThreadNumAndFileName)
        {
            int nFunRes = 0;
            System.IO.StreamReader fileHander = null; 

            try
			{
				// Create an instance of StreamReader to read from a file.
				// The using statement also closes the StreamReader.
				fileHander = new System.IO.StreamReader(strFileName);

				String strGetLine;
				// Read and display lines from the file until the end of 
				// the file is reached.
				while ((strGetLine = fileHander.ReadLine()) != null)
				{
					AnalyseLogFileLine(strGetLine, mapThreadNumAndFileName);
				}
				
				fileHander.Close();
                
            }
            catch (Exception e)
            {
                // Let the user know what went wrong.
                //this.m_logHandle.WriteLine("The file could not be read:");
                //this.m_logHandle.WriteLine(e.Message);
                MessageBox.Show(e.Message);
                nFunRes = -1;
            }

            return nFunRes;
        }//AnalyseFile

        
        
        /// <summary>
		/// AnalyseLogFileLine
		/// Analyse one line in log file
        /// </summary>
        /// <param name="strLogFileLine"></param>
        /// <param name="mapThreadNumAndFileName"></param>
        /// <returns></returns>
        private int AnalyseLogFileLine(System.String strLogFileLine,
            IDictionary<string, StreamWriter> mapThreadNumAndFileName)
        {
            int nFunRes = 0;
            System.String strThrdNum = "";//[Thrd: 5476]
            System.String strDstFileName = "";//./DstLogPath/Thrd_5476.log
            StreamWriter dstFileHandle = null;

			//check line contain string "[Thrd:"
            if (!checkLogFileLine(strLogFileLine))
            {
                nFunRes = -1;
                return nFunRes;
            }

			//get string [Thrd: 3004]
            strThrdNum = getThrdNumFromLogFileLine(strLogFileLine);
            if (strThrdNum.Length <= 0)
            {
                nFunRes = -1;
                return nFunRes;
            }

			//get dst file name ./DstLogPath/Thrd_5476.log
			strDstFileName = getDstFileNameByThrdNum(strThrdNum);
			if (strDstFileName.Length <= 0)
			{
				nFunRes = -1;
				return nFunRes;
			}

			//get or new one StreamWriter
            if (mapThreadNumAndFileName.ContainsKey(strThrdNum))
            {
                dstFileHandle = mapThreadNumAndFileName[strThrdNum];
            }
            else
            {
                dstFileHandle = new StreamWriter(strDstFileName);
                mapThreadNumAndFileName.Add(strThrdNum, dstFileHandle);
            }

			//write to dst file
            if (null != dstFileHandle)
            {
                dstFileHandle.WriteLine(strLogFileLine);
            }

            return nFunRes;
        }//AnalyseFile
        
        

		/// <summary>
		/// checkLogFileLine
		/// check one line in log file contain string "[Thrd:"
		/// </summary>
		/// <param name="strLogFileLine"></param>
		/// <returns></returns>
        private Boolean checkLogFileLine(System.String strLogFileLine)
        {
            Boolean nFunRes = false;
            int nfindSunStr = -1;

            if (strLogFileLine.Length > 0)
            {
                nfindSunStr = -1;
                nfindSunStr = strLogFileLine.IndexOf("[Thrd:");
            }

            if (nfindSunStr >= 0)
            {
                nFunRes = true;
            }

            return nFunRes;
        }


		/// <summary>
		/// getThrdNumFromLogFileLine
		/// eg. get "[Thrd: 5476]" from one line in log file
		/// </summary>
		/// <param name="strLogFileLine"></param>
		/// <returns></returns>
        private System.String getThrdNumFromLogFileLine(System.String strLogFileLine)
        {
            System.String strLogFileLineSub = "";
            System.String strThrdNum = "";
            int nfindSunStr = -1;


            //	01/04/2013 17:09:18:265 [DEBUG] [Thrd: 5476] d:\stecode_pra\3001_tip_new\ta_base\transactive\app\dbsynchnewserver\maqlib\src\oracleconnection.cpp:92: [strDbConnectionStr=Oracle:TRA_OCC:IT271350_5:IT271350_5]
            if (strLogFileLine.Length > 0)
            {
                nfindSunStr = -1;
                nfindSunStr = strLogFileLine.IndexOf("[Thrd:");
            }
            if (nfindSunStr > 0)
            {
                //[Thrd: 5476] d:\stecode_pra\3001_tip_new\ta_base\transactive\app\dbsynchnewserver\maqlib\src\oracleconnection.cpp:92: [strDbConnectionStr=Oracle:TRA_OCC:IT271350_5:IT271350_5]
                strLogFileLineSub = strLogFileLine.Substring(nfindSunStr);
                nfindSunStr = -1;
            }


            if (strLogFileLineSub.Length > 0)
            {
                nfindSunStr = -1;
                nfindSunStr = strLogFileLineSub.IndexOf("]");
            }
            if (nfindSunStr > 0)
            {
                //[Thrd: 5476]
                strThrdNum = strLogFileLineSub.Substring(0, nfindSunStr + 1);

                nfindSunStr = -1;
            }

            return strThrdNum;
        }//AnalyseFile


		/// <summary>
		///	getDstFileNameByThrdNum   eg. is log contains: [Thrd: 5476] then dest file: ./DstLogPath/Thrd_5476.log
		/// </summary>
		/// <param name="strThrdNum"></param>
		/// <returns></returns>
        private System.String getDstFileNameByThrdNum(System.String strThrdNum)
        {
            System.String strDstFileName = "";
            System.String strThrdNumSubStr = "";

            int nfindSunStr = -1;

            //[Thrd: 5476]
            if (strThrdNum.Length > 0)
            {
                nfindSunStr = -1;
                nfindSunStr = strThrdNum.IndexOf(":");
            }
            if (nfindSunStr > 0)
            {
                strThrdNumSubStr = strThrdNum.Substring(nfindSunStr + 1);
                nfindSunStr = -1;
            }

            //remove "]"
            strThrdNumSubStr = strThrdNumSubStr.Replace("]", " ");

            //remove " "
            strThrdNumSubStr = strThrdNumSubStr.Trim(); 
            //./DstLogPath/Thrd_5476.log
            strDstFileName = m_strDstLogPath + "Thrd_" + strThrdNumSubStr + ".log";

            return strDstFileName;
        }//AnalyseFile



        /// <summary>
		/// delete all files and SubDirectory in this path
        /// </summary>
        /// <param name="targetDir"></param>
        /// <param name="delSubDir"></param> 		
        public void DeleteFiles(System.String targetDir, Boolean delSubDir)
        {
            foreach (System.String fileName in Directory.GetFiles(targetDir))
            {
                File.SetAttributes(fileName, FileAttributes.Normal);
                File.Delete(fileName);
            }
            
            if (delSubDir)
            {
                DirectoryInfo dir = new DirectoryInfo(targetDir);
                foreach (DirectoryInfo subDi in dir.GetDirectories())
                {
                    DeleteFiles(subDi.FullName, true);
                    subDi.Delete();
                }

            }
        }


		/// <summary>
		/// create Directory, if Directory is exists then delete all files and SubDirectory in this path
		/// </summary>
		/// <param name="targetDir"></param>
        public void CreateDirectory(string targetDir)
        {
            DirectoryInfo dir = new DirectoryInfo(targetDir);
            if (!dir.Exists)
            {
				//
                dir.Create();
            }
            else
            {
                DeleteFiles(targetDir, true);
            }
        }
            

    }// public partial class AnalyseLogFile : Window
}//namespace TestWPFApplication
