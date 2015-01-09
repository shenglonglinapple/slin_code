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
	class UnitFun
	{


		public UnitFun()
		{
			
		}


		/// <summary>
		/// get all file names in Path
		/// </summary>
		/// <param name="strPath"></param>	eg./logfile/
		/// <param name="strFileType"></param>   eg. *.log
		/// <returns></returns>
		public System.IO.FileInfo[] getFiles(string strPath, string strFileType)
		{
			System.IO.DirectoryInfo dirInfo;
			System.IO.FileInfo[] filelist = null;

			// Specify the directories you want to manipulate.
			dirInfo = new System.IO.DirectoryInfo(strPath);

			try
			{
				// Determine whether the directory exists.
				if (!dirInfo.Exists)
				{
					// Indicate that the directory already exists.

					System.String strLog = System.String.Format("Error: That path not exists  strPath ={0}", strPath);
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
		
		
		
		
		
		
		
		
		
		
		
	}
}
