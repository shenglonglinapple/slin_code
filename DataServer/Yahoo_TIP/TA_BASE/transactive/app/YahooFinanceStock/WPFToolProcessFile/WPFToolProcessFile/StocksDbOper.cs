using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

using System.Data.SQLite;


namespace WPFToolProcessFile
{
    public class StocksDbOper
    {
        //数据库连接
        public System.String m_connectionString;
        public System.Data.SQLite.SQLiteConnection m_dbConnection;

        public List<System.String> m_lstSQL;

        public StocksDbOper()
        {
            m_lstSQL = new List<System.String>();
            m_lstSQL.Clear();

        }
        public void createNewDatabase()
        {
            //System.IO.File.Delete("STOCKSSQLITE_DB.db");
            SQLiteConnection.CreateFile("STOCKSSQLITE_DB.db");
        }
        public void connectToDatabase()
        {
            m_dbConnection = new SQLiteConnection("Data Source=STOCKSSQLITE_DB.db;Version=3;");
            m_dbConnection.Open();
        }
        public void disConnectToDatabase()
        {
            m_dbConnection.Close();
        }

        public void BeginTransaction()
        {
            System.Int32 nFunRes = 0;
            SQLiteCommand command = new SQLiteCommand("begin transaction", m_dbConnection);
            command.CommandText = "begin transaction";
            nFunRes = command.ExecuteNonQuery();
        }

        public void Commit()
        {
            System.Int32 nFunRes = 0;
            SQLiteCommand command = new SQLiteCommand("commit", m_dbConnection);
            command.CommandText = "commit;";
            nFunRes = command.ExecuteNonQuery();
        }

        public void Rollback()
        {
            System.Int32 nFunRes = 0;
            SQLiteCommand command = new SQLiteCommand("rollback", m_dbConnection);
            command.CommandText = "rollback";
            nFunRes = command.ExecuteNonQuery();
        }

        public void createTable()
        {
            //"CREATE TABLE IF NOT EXISTS TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE TEXT, COLUMN_NAMEPINYINFIRST TEXT, COLUMN_NAMEPINYINFULL0 TEXT,COLUMN_NAMEPINYINFULL4 TEXT, COLUMN_NAMEUTF8 nvarchar(256))"
            string sql = "CREATE TABLE IF NOT EXISTS TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE TEXT, COLUMN_NAMEPINYINFIRST TEXT, COLUMN_NAMEPINYINFULL0 TEXT,COLUMN_NAMEPINYINFULL4 TEXT, COLUMN_NAMEUTF8 nvarchar(256))";
            SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
            command.ExecuteNonQuery();
        }

        public void AddToSQLArray(System.String str_symboluse,
            System.String str_namePinYinFirst,
            System.String str_namePinYinFull_0,
            System.String str_namePinYinFull_4,
            System.String str_name_utf8)
        {
            
            //INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES (?, ?, ?, ?, ?)
            //System.String sql = "INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES (?, ?, ?, ?, ?)";
            System.String sql =
                System.String.Format("INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}')",
                str_symboluse, str_namePinYinFirst, str_namePinYinFull_0, str_namePinYinFull_4, str_name_utf8);

            m_lstSQL.Add(sql);
            //SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
            //command.ExecuteNonQuery();
        }

        public void insertAllDataToDB()
        {
            //INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES (?, ?, ?, ?, ?)
            //System.String sql = "INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES (?, ?, ?, ?, ?)";
            //System.String sql =  System.String.Format("INSERT INTO TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE, COLUMN_NAMEPINYINFIRST, COLUMN_NAMEPINYINFULL0, COLUMN_NAMEPINYINFULL4, COLUMN_NAMEUTF8) VALUES ('{0}', '{1}', '{2}', '{3}', '{4}')",
            //    str_symboluse, str_namePinYinFirst, str_namePinYinFull_0, str_namePinYinFull_4, str_name_utf8);
            
            System.Int32 nFunRes = 0;
            BeginTransaction();
            SQLiteCommand command = new SQLiteCommand(m_dbConnection);
            
            foreach (System.String strSQL in m_lstSQL)
            {
                command.CommandText = strSQL;
                nFunRes = command.ExecuteNonQuery();
            }
            Commit();

        }


/*
         public StocksDbOper()
        {
            createNewDatabase();
            connectToDatabase();
            createTable();
            fillTable();
            printHighscores();
        }

        void createNewDatabase()
        {
            SQLiteConnection.CreateFile("STOCKSSQLITE_DB.db");
        }

        void connectToDatabase()
        {
            m_dbConnection = new SQLiteConnection("Data Source=STOCKSSQLITE_DB.db;Version=3;");
            m_dbConnection.Open();
        }

        void createTable()
        {
            //"CREATE TABLE IF NOT EXISTS TABLE_STOCKSSQLITE (COLUMN_SYMBOLUSE TEXT, COLUMN_NAMEPINYINFIRST TEXT, COLUMN_NAMEPINYINFULL0 TEXT,COLUMN_NAMEPINYINFULL4 TEXT, COLUMN_NAMEUTF8 nvarchar(256))"
            string sql = "create table highscores (name varchar(20), score int)";
            SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
            command.ExecuteNonQuery();
        }

        void fillTable()
        {
            string sql = "insert into highscores (name, score) values ('Me', 3000)";
            SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
            command.ExecuteNonQuery();

            sql = "insert into highscores (name, score) values ('Myself', 6000)";
            command = new SQLiteCommand(sql, m_dbConnection);
            command.ExecuteNonQuery();

            sql = "insert into highscores (name, score) values ('And I', 9001)";
            command = new SQLiteCommand(sql, m_dbConnection);
            command.ExecuteNonQuery();
        }

        void printHighscores()
        {
            string sql = "select * from highscores order by score desc";
            SQLiteCommand command = new SQLiteCommand(sql, m_dbConnection);
            SQLiteDataReader reader = command.ExecuteReader();
            while (reader.Read())
                Console.WriteLine("Name: " + reader["name"] + "\tScore: " + reader["score"]);
            Console.ReadLine();
        }
*/
       

    }//class StocksDbOper
}//namespace WPFToolChangeLongType
