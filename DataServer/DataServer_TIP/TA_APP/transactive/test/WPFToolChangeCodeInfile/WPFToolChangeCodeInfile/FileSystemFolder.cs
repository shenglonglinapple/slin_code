using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

///
using System.IO;

namespace WPFToolChangeCodeInfile
{
    public class FileSystemFolder
    {
        public FileSystemFolder()
        {
            
        }

        ~FileSystemFolder()
        {

        }


        public void createDirectory(string targetDir)
        {
            System.IO.DirectoryInfo dir = new System.IO.DirectoryInfo(targetDir);
            if (!dir.Exists)
            {
                //System.IO.Directory.CreateDirectory(targetPath);
                dir.Create();
            }
            else
            {
                deleteFiles(targetDir, true);
            }
        }//CreateDirectory

        public void deleteFiles(System.String targetDir, Boolean delSubDir)
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
                    deleteFiles(subDi.FullName, true);
                    subDi.Delete();
                    //System.IO.Directory.Delete(@"C:\Users\Public\DeleteTest");
                }

            }
        }//DeleteFiles


    }
}
