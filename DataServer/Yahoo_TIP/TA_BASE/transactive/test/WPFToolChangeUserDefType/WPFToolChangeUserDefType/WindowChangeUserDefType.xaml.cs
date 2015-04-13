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


namespace WPFToolChangeUserDefType
{
    /// <summary>
    /// Interaction logic for WindowChangeUserDefType.xaml
    /// </summary>
    public partial class WindowChangeUserDefType : Window
    {
        /// <summary>
        /// 
        /// </summary>
        private System.String m_strDirectoryFrom_UserInput = System.String.Empty;
        private System.String m_strDirectoryTo_UserInput = System.String.Empty;
        private System.String m_strFindWhat_UserInput = System.String.Empty;
        private System.String m_strReplaceWith_UserInput = System.String.Empty;
        private System.String m_strFileExtenion_UserInput = System.String.Empty;
        public System.Boolean m_bProcessSubDir_UserInput = true;

        private DataChangeUserDefType m_pDataChangeUserDefType;

        
        private System.ComponentModel.BackgroundWorker m_pBackgroundWorker;
        private DirectoryOper m_pDirectoryOper;
        private FileOperChangeUserDefType m_pFileOperChangeUserDefType;

        public WindowChangeUserDefType()
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
            this.m_strDirectoryFrom_UserInput = "./DataSrc";
            this.m_strDirectoryTo_UserInput = "./DataDest";
            this.m_strFindWhat_UserInput = "10.2.0";
            this.m_strReplaceWith_UserInput = "11.2.0";
            this.m_strFileExtenion_UserInput = "";
            this.m_bProcessSubDir_UserInput = true;

            m_pDataChangeUserDefType = new DataChangeUserDefType();
            m_pDataChangeUserDefType.resetDirectoryValue(
                this.m_strDirectoryFrom_UserInput,
                this.m_strDirectoryTo_UserInput,
                this.m_strFindWhat_UserInput,
                this.m_strReplaceWith_UserInput,
                this.m_strFileExtenion_UserInput,
                this.m_bProcessSubDir_UserInput);
            this.m_pBackgroundWorker = new System.ComponentModel.BackgroundWorker();

            m_pDirectoryOper = new DirectoryOper();
            m_pFileOperChangeUserDefType = new FileOperChangeUserDefType();

        }//InitializeData

        /// <summary>
        /// 
        /// </summary>
        private void _InitializeEvent()
        {
            //create one thread to do work
            //register event  DoWork  RunWorkerCompleted

            this.m_pBackgroundWorker.DoWork +=
                new System.ComponentModel.DoWorkEventHandler(this.functon_BackgroundWorker_DoWork);

            this.m_pBackgroundWorker.RunWorkerCompleted +=
                new System.ComponentModel.RunWorkerCompletedEventHandler(this.functon_BackgroundWorker_DoWorkCompleted);

        }//InitializeEvent




        /// <summary>
        /// 
        /// </summary>
        /// <param name="sender"></param>
        /// <param name="e"></param>
        private void CheckBox_SubDirectory_Checked(object sender, RoutedEventArgs e)
        {
            this.m_bProcessSubDir_UserInput = true;
        }

        private void CheckBox_SubDirectory_Unchecked(object sender, RoutedEventArgs e)
        {
            this.m_bProcessSubDir_UserInput = false;
        }

        private void button_ChangeUserDef_DoWork_Click(object sender, RoutedEventArgs e)
        {
            this.buttonChangeUserDef_DoWork.IsEnabled = false;

            this.m_strDirectoryFrom_UserInput = this.textBox_DirectoryFrom.Text;
            this.m_strDirectoryTo_UserInput = this.textBox_DirectoryTo.Text;
            this.m_strFindWhat_UserInput = this.textBox_FindWhat.Text;//"10.2.0";
            this.m_strReplaceWith_UserInput = this.textBox_ReplaceWith.Text;//"11.2.0";
            this.m_strFileExtenion_UserInput = this.textBox_FileExten.Text;
            //this.m_bProcessSubDir_UserInput
            
            /*
            //TODO lsl -- test
            this.m_strDirectoryFrom_UserInput = "C:\\work_changelongtype\\WPFToolChangeUserDefType\\pathsrc";
            this.m_strDirectoryTo_UserInput = "C:\\work_changelongtype\\WPFToolChangeUserDefType\\pathdest";
            this.m_strFindWhat_UserInput = "1.1.0";
            this.m_strReplaceWith_UserInput = "1.1.5";
            this.m_strFileExtenion_UserInput = ".vcproj";
            //this.m_strFileExtenion_UserInput = "";
            this.m_bProcessSubDir_UserInput = true;
            //this.m_bProcessSubDir_UserInput = false;
            */
            
            
            //check params
            if (this.m_strDirectoryFrom_UserInput.Length <= 0)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataSrcPath error!"));
                //MessageBox.Show("DataSrcPath error!");
                this.buttonChangeUserDef_DoWork.IsEnabled = true;
                return;
            }

            if (this.m_strDirectoryTo_UserInput.Length <= 0)
            {
                log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("DataDestPath use default value ./DataDest"));
                //MessageBox.Show("DataDestPath use default value ./DataDest");
                this.m_strDirectoryTo_UserInput = "./DataDest"; ;
            }
            System.String strLogFormat = System.String.Format("m_strDataSrcPath={0} m_strDataDestPath={1} m_strSrc={2} m_strDest={3}",
                              this.m_strDirectoryFrom_UserInput,
                              this.m_strDirectoryTo_UserInput,
                              this.m_strFindWhat_UserInput,
                              this.m_strReplaceWith_UserInput);
            log4net.LogManager.GetLogger("ExeLogger").Info(strLogFormat);

            m_pDataChangeUserDefType.resetDirectoryValue(
                this.m_strDirectoryFrom_UserInput,
                this.m_strDirectoryTo_UserInput,
                this.m_strFindWhat_UserInput,
                this.m_strReplaceWith_UserInput,
                this.m_strFileExtenion_UserInput,
                this.m_bProcessSubDir_UserInput);

            this.m_pBackgroundWorker.RunWorkerAsync();//functon_BackgroundWorker_DoWork

            //_DoWork_BackgroundWorker_DoWork();

        }//button_DoWork_Click




        private void functon_BackgroundWorker_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            _DoWork_BackgroundWorker_DoWork();

        }//BackgroundWorkerAnalystFile_DoWork

        private void _DoWork_BackgroundWorker_DoWork()
        {

            MessageBox.Show("begin work");

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("begin work"));

            //CreateDirectory DstLogPath
            m_pDirectoryOper.createDirectory(m_pDataChangeUserDefType.m_strDirectoryTo);
            //this.m_strDataSrcPath = this.textBox_Path.Text;

            System.String strDirectoryFrom = m_pDataChangeUserDefType.m_strDirectoryFrom;
            System.String strDirectoryTo = m_pDataChangeUserDefType.m_strDirectoryTo;
            Boolean bProcessSubDir = m_pDataChangeUserDefType.m_bProcessSubDir;

            processDirectory(strDirectoryFrom, strDirectoryTo, bProcessSubDir);

            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format("end work!"));

            MessageBox.Show("end work!");


        }//BackgroundWorkerAnalystFile_DoWork

        private void functon_BackgroundWorker_DoWorkCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            this.buttonChangeUserDef_DoWork.IsEnabled = true;

        }//BackgroundWorkerAnalystFile_RunWorkerCompleted

        
        //===============================================================
        public void processDirectory(System.String strDirectoryFrom, System.String strDirectoryTo, Boolean bProcessSubDir)
        {
            log4net.LogManager.GetLogger("ExeLogger").Info(
                System.String.Format("processDirectory strDirectoryFrom={0} strDirectoryTo={1} bProcessSubDir={2}",
                strDirectoryFrom, strDirectoryTo, bProcessSubDir));

            System.IO.DirectoryInfo dirInfoSrcPath;
            FileInfo[] filelist = null;

            dirInfoSrcPath = new System.IO.DirectoryInfo(strDirectoryFrom);
            //bDataSrcPathExists = System.IO.Directory.Exists(strDataSrcPath);
            if (false == dirInfoSrcPath.Exists)
            {
                log4net.LogManager.GetLogger("ExeLogger").Error(
                    System.String.Format("error! processDirectory  not Exists strDirectoryFrom={0}", strDirectoryFrom));
                MessageBox.Show(System.String.Format("error! processDirectory  not Exists strDirectoryFrom={0}", strDirectoryFrom));
                //System.String strLog = String.Format("Error: That path not exists  strPath ={0}", strPath);
                return;
            }


            m_pDirectoryOper.createDirectory(strDirectoryTo);

            filelist = dirInfoSrcPath.GetFiles("*.*");//"*.log"

            foreach (FileInfo item in filelist)
            {
                System.String strFileFrom = item.FullName;
                System.String strFileNameFrom = item.Name;
                System.String strFileTo = System.String.Empty;
                //将两个字符串组合成一个路径。
                strFileTo = System.IO.Path.Combine(strDirectoryTo, strFileNameFrom);

                processFile(strFileFrom, strFileTo);
            }


            if (bProcessSubDir)
            {
                foreach (DirectoryInfo subDi in dirInfoSrcPath.GetDirectories())
                {
                    System.String strSubDirectoryFrom = System.String.Empty;
                    System.String strSubDirectoryTo = System.String.Empty;

                    strSubDirectoryFrom = subDi.FullName;
                    strSubDirectoryTo = System.IO.Path.Combine(strDirectoryTo, subDi.Name);

                    processDirectory(strSubDirectoryFrom, strSubDirectoryTo, bProcessSubDir);
                }

            }
        }//processFilesInPath

        public void processFile(System.String strFileFrom, System.String strFileTo)
        {
            log4net.LogManager.GetLogger("ExeLogger").Info(System.String.Format(
                "processFile strFileFrom={0} strFileTo={1}",
                strFileFrom, strFileTo));
            DataChangeUserDefType pDataChangeUserDefTypeTmp = new DataChangeUserDefType();
            pDataChangeUserDefTypeTmp = m_pDataChangeUserDefType;
            pDataChangeUserDefTypeTmp.resetCurrentFileValue(
                strFileFrom,
                strFileTo,
                m_pDataChangeUserDefType.m_strFindWhat,
                m_pDataChangeUserDefType.m_strReplaceWith);
            m_pFileOperChangeUserDefType.processFile(pDataChangeUserDefTypeTmp);
            //m_processFileCopy.processFile(strDataSrcFile, strDataDestFile);
            //m_pFileOperChangeUserDefType.processFile(strFileFrom, strFileTo, m_strFindWhat_UserInput, m_strReplaceWith_UserInput);

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






    }//WindowChangeUserDefType
}//public partial class WindowChangeUserDefType : Window
