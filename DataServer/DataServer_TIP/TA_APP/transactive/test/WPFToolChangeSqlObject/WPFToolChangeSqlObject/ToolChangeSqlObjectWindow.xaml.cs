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

namespace WPFToolChangeSqlObject
{
    /// <summary>
    /// Interaction logic for Window1.xaml
    /// </summary>
    public partial class ToolChangeSqlObjectWindow : Window
    {
        private System.String m_strDataSrcPath = System.String.Empty;
        private System.String m_strDataDestPath = System.String.Empty;
        private System.ComponentModel.BackgroundWorker m_backgroundWorkerAnalystFile;
        private processFileCopy m_processFileCopy;
        private ProcessFileSQLObject m_ProcessFileSQLObject;
        

        public ToolChangeSqlObjectWindow()
        {
            InitializeComponent();


            InitializeData();
            InitializeEvent();
        }



        private void InitializeData()
        {
            this.m_strDataSrcPath = "./DataSrc";
            this.m_strDataDestPath = "./DataDest";
            this.m_backgroundWorkerAnalystFile = new System.ComponentModel.BackgroundWorker();
            m_processFileCopy = new processFileCopy();
            m_ProcessFileSQLObject = new ProcessFileSQLObject();

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
            

            if (this.m_strDataSrcPath.Length <= 0)
            {
                MessageBox.Show("DataSrcPath error!");
                this.button_DoWork.IsEnabled = true;
                return;
            }

            if (this.m_strDataDestPath.Length <= 0)
            {
                MessageBox.Show("DataDestPath use default value ./DataDest");
                this.m_strDataDestPath = "./DataDest";
            }

            this.m_backgroundWorkerAnalystFile.RunWorkerAsync();

        }//button_DoWork_Click




        private void BackgroundWorkerAnalystFile_DoWork(object sender, System.ComponentModel.DoWorkEventArgs e)
        {
            Boolean bProcessSubDir = true;

            MessageBox.Show("Run begin");

            //CreateDirectory DstLogPath
            CreateDirectory(this.m_strDataDestPath);
            //this.m_strDataSrcPath = this.textBox_Path.Text;
            processFilesInPath(this.m_strDataSrcPath, this.m_strDataDestPath, bProcessSubDir);

            MessageBox.Show("end work!");
        }//BackgroundWorkerAnalystFile_DoWork

        private void BackgroundWorkerAnalystFile_RunWorkerCompleted(object sender, System.ComponentModel.RunWorkerCompletedEventArgs e)
        {
            this.button_DoWork.IsEnabled = true;

        }//BackgroundWorkerAnalystFile_RunWorkerCompleted




        //===============================================================
        public void processFilesInPath(System.String strDataSrcPath, System.String strDataDestPath, Boolean bProcessSubDir)
        {
            System.IO.DirectoryInfo dirInfoSrcPath;
            FileInfo[] filelist = null;

            dirInfoSrcPath = new System.IO.DirectoryInfo(strDataSrcPath);
            //bDataSrcPathExists = System.IO.Directory.Exists(strDataSrcPath);
            if (false == dirInfoSrcPath.Exists)
            {
                MessageBox.Show("error! processFilesInPath  DataSrcPath not Exists");
                //System.String strLog = String.Format("Error: That path not exists  strPath ={0}", strPath);
                return;
            }


            CreateDirectory(strDataDestPath);

            filelist = dirInfoSrcPath.GetFiles("*.*");//"*.log"

            foreach (FileInfo item in filelist)
            {
                System.String strSrcFullName = item.FullName;
                System.String strSrcFileName = item.Name;
                System.String strDestFileName = System.String.Empty;
                strDestFileName = System.IO.Path.Combine(strDataDestPath, strSrcFileName);

                processFile(strSrcFullName, strDestFileName);


            }
                       

            if (bProcessSubDir)
            {
                foreach (DirectoryInfo subDi in dirInfoSrcPath.GetDirectories())
                {
                    System.String strDataSrcSubPath = System.String.Empty;
                    System.String strDataDestSubPath = System.String.Empty;

                    strDataSrcSubPath = subDi.FullName;
                    strDataDestSubPath = System.IO.Path.Combine(strDataDestPath, subDi.Name);
                    
                    processFilesInPath(strDataSrcSubPath, strDataDestSubPath, bProcessSubDir);
                }

            }
        }//processFilesInPath

        public void processFile(System.String strDataSrcFile, System.String strDataDestFile)
        {
            //m_processFileCopy.processFile(strDataSrcFile, strDataDestFile);
            m_ProcessFileSQLObject.processFile(strDataSrcFile, strDataDestFile);

        }//processFile

        //===============================================================

        public void CreateDirectory(string targetDir)
        {
            DirectoryInfo dir = new DirectoryInfo(targetDir);
            if (!dir.Exists)
            {
                //System.IO.Directory.CreateDirectory(targetPath);
                dir.Create();
            }
            else
            {
                DeleteFiles(targetDir, true);
            }
        }//CreateDirectory

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
                    //System.IO.Directory.Delete(@"C:\Users\Public\DeleteTest");
                }

            }
        }//DeleteFiles






    }//class ToolChangeSqlObjectWindow

}//namespace WPFToolChangeSqlObject
