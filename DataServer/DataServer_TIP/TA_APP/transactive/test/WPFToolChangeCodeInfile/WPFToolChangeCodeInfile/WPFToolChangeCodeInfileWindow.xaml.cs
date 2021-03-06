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

using System.Diagnostics;

namespace WPFToolChangeCodeInfile
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class WPFToolChangeCodeInfileWindow : Window
    {
        /// <summary>
        /// 
        /// </summary>
        private System.String m_strStringSrc = System.String.Empty;
        private System.String m_strStringDest = System.String.Empty;
        private System.String m_strDataSrcPath = System.String.Empty;
        private System.String m_strDataDestPath = System.String.Empty;
        private System.ComponentModel.BackgroundWorker m_backgroundWorkerAnalystFile;
        private FileSystemFolder m_FileSYstemFolder;
        private ProcessFileChangeCodeInfile m_ProcessFileChangCodeInfile;

        /// <summary>
        /// 
        /// </summary>
        public WPFToolChangeCodeInfileWindow()
        {
            InitializeComponent();

            ////////////////////////////////////////
            _InitializeData();
            _InitializeEvent();

            _LogTest();
        }


        /// <summary>
        /// 
        /// </summary>
        private void _InitializeData()
        {
            this.m_strDataSrcPath = "./DataSrc";
            this.m_strDataDestPath = "./DataDest";
            this.m_backgroundWorkerAnalystFile = new System.ComponentModel.BackgroundWorker();

            m_FileSYstemFolder = new FileSystemFolder();
            m_ProcessFileChangCodeInfile = new ProcessFileChangeCodeInfile();

        }//InitializeData

        /// <summary>
        /// 
        /// </summary>
        private void _InitializeEvent()
        {
            //create one thread to do work
            //register event  DoWork  RunWorkerCompleted

            this.m_backgroundWorkerAnalystFile.DoWork +=
                new System.ComponentModel.DoWorkEventHandler(this.BackgroundWorkerAnalystFile_DoWork);

            this.m_backgroundWorkerAnalystFile.RunWorkerCompleted +=
                new System.ComponentModel.RunWorkerCompletedEventHandler(this.BackgroundWorkerAnalystFile_RunWorkerCompleted);

        }//InitializeEvent

        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void button_DoWork_Click(object sender, RoutedEventArgs e)
        {
            this.button_DoWork.IsEnabled = false;

            this.m_strDataSrcPath = this.textBox_DataSrcPath.Text;
            this.m_strDataDestPath = this.textBox_DataDestPath.Text;
            this.m_strStringSrc = this.textBox_StringSrc.Text;
            this.m_strStringDest = this.textBox_StringDest.Text;
            
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("m_strStringSrc={0}", this.m_strDataSrcPath));
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("m_strStringDest={0}", this.m_strStringDest));
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("m_strDataSrcPath={0}", this.m_strDataSrcPath));
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("m_strDataDestPath={0}", this.m_strDataDestPath));
            
            if (this.m_strDataSrcPath.Length <= 0)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataSrcPath error!"));
                //MessageBox.Show("DataSrcPath error!");
                this.button_DoWork.IsEnabled = true;
                return;
            }

            if (this.m_strDataDestPath.Length <= 0)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataDestPath use default value ./DataDest"));
                //MessageBox.Show("DataDestPath use default value ./DataDest");
                this.m_strDataDestPath = "./DataDest"; ;
            }
            this.m_backgroundWorkerAnalystFile.RunWorkerAsync();

        }//button_DoWork_Click




        private void BackgroundWorkerAnalystFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            Boolean bProcessSubDir = true;

            MessageBox.Show("begin work");

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("begin work"));


            DataProcessParam pDataProcessParam = null;
            pDataProcessParam = new DataProcessParam();
            pDataProcessParam.m_strStringSrc = this.m_strStringSrc;
            pDataProcessParam.m_strStringDest = this.m_strStringDest;
            pDataProcessParam.m_strDataSrcPath = this.m_strDataSrcPath;
            pDataProcessParam.m_strDataDestPath = this.m_strDataDestPath;

            //CreateDirectory DstLogPath
            m_FileSYstemFolder.createDirectory(this.m_strDataDestPath);
            //this.m_strDataSrcPath = this.textBox_Path.Text;
            processFilesInPath(this.m_strDataSrcPath, this.m_strDataDestPath, bProcessSubDir, pDataProcessParam);

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("end work!"));

            MessageBox.Show("end work!");


        }//BackgroundWorkerAnalystFile_DoWork

        private void BackgroundWorkerAnalystFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            this.button_DoWork.IsEnabled = true;

        }//BackgroundWorkerAnalystFile_RunWorkerCompleted




        //===============================================================
        public void processFilesInPath(System.String strDataSrcPath, System.String strDataDestPath, Boolean bProcessSubDir, DataProcessParam pDataProcessParam)
        {
            System.IO.DirectoryInfo dirInfoSrcPath;
            FileInfo[] filelist = null;

            dirInfoSrcPath = new System.IO.DirectoryInfo(strDataSrcPath);
            //bDataSrcPathExists = System.IO.Directory.Exists(strDataSrcPath);
            if (false == dirInfoSrcPath.Exists)
            {
                log4net.LogManager.GetLogger("ExeLogger").Error(System.String.Format("error! processFilesInPath  DataSrcPath not Exists"));
                //MessageBox.Show("error! processFilesInPath  DataSrcPath not Exists");
                //System.String strLog = String.Format("Error: That path not exists  strPath ={0}", strPath);
                return;
            }


            m_FileSYstemFolder.createDirectory(strDataDestPath);

            filelist = dirInfoSrcPath.GetFiles("*.*");//"*.log"

            foreach (FileInfo item in filelist)
            {
                System.String strSrcFullName = item.FullName;
                System.String strSrcFileName = item.Name;
                System.String strDestFileName = System.String.Empty;
                strDestFileName = System.IO.Path.Combine(strDataDestPath, strSrcFileName);

                processFile(strSrcFullName, strDestFileName, pDataProcessParam);
            }


            if (bProcessSubDir)
            {
                foreach (DirectoryInfo subDi in dirInfoSrcPath.GetDirectories())
                {
                    System.String strDataSrcSubPath = System.String.Empty;
                    System.String strDataDestSubPath = System.String.Empty;

                    strDataSrcSubPath = subDi.FullName;
                    strDataDestSubPath = System.IO.Path.Combine(strDataDestPath, subDi.Name);

                    processFilesInPath(strDataSrcSubPath, strDataDestSubPath, bProcessSubDir, pDataProcessParam);
                }

            }
        }//processFilesInPath

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile, DataProcessParam pDataProcessParam)
        {
            //m_processFileCopy.processFile(strDataSrcFile, strDataDestFile);
            m_ProcessFileChangCodeInfile.processFile(strDataSrcFile, strDataDestFile, pDataProcessParam);

        }//processFile

        //===============================================================







        private void _LogTest()
        {
            //Trace|Debug|Info|Warn|Error|Fatal
            {
                System.Diagnostics.StackTrace StackTraceTmp = new System.Diagnostics.StackTrace(true);
                System.Diagnostics.StackFrame StackFrameTmp = null;
                int count = StackTraceTmp.FrameCount;
                for (int i = 0; i < count; i++)
                {
                    StackFrameTmp = StackTraceTmp.GetFrame(i);
                    //Console.WriteLine(StackFrameTmp.ToString() + StackFrameTmp.GetFileLineNumber() + StackFrameTmp.GetFileName());

                    //NLog.LogManager.GetCurrentClassLogger().Trace("StackFrameTmp.ToString={0}  StackFrameTmp.GetFileName={1}  StackFrameTmp.GetFileLineNumber={2}", 
                     //   StackFrameTmp.ToString(), StackFrameTmp.GetFileName(), StackFrameTmp.GetFileLineNumber());
                }
            }
            // <!--None,Fatal,ERROR,WARN,DEBUG,INFO,ALL-->
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("Info"));
            log4net.LogManager.GetLogger("ExeLogger").Debug(System.String.Format("Debug"));
            log4net.LogManager.GetLogger("ExeLogger").Warn(System.String.Format("Warn"));
            log4net.LogManager.GetLogger("ExeLogger").Error(System.String.Format("Error"));
            //log4net.LogManager.GetLogger("Fatal").Fatal(System.String.Format("Fatal"));


        }


    }//class ToolChangeSqlObjectWindow

}//namespace WPFToolChangeLongType
