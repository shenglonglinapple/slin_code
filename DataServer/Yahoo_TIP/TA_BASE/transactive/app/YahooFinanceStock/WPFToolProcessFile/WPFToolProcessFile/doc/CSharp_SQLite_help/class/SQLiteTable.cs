using System;
using System.Collections.Generic;
using System.Text;
using System.Data.SQLite;

namespace WPFToolProcessFile
{
    public class SQLiteTable
    {
        public string TableName = "";
        public SQLiteColumnList Columns = new SQLiteColumnList();

        public SQLiteTable()
        { }

        public SQLiteTable(string name)
        {
            TableName = name;
        }
    }//public class SQLiteTable
}//WPFToolChangeLongType