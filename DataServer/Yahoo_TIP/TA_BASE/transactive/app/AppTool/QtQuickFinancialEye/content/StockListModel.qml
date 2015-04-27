import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1
import QtQuick.LocalStorage 2.0//sqlite db

ListModel
{
    id: id_qml_StockListModel;


    /*
    id_qml_StockListModel.append( {
        "m_n_Name": "Analog Devices, Inc.",
        "m_s_Symbol": "ADI",
        "m_s_Symbol_Extern": "null/.SS/.SZ",
        "m_l1_Last_Trade_Price_Only": "0.0",
        "m_c6_Change_Realtime": "0.0",
        "m_p2_Change_in_Percent": "0.0%"});
    */


    Component.onCompleted:
    {
        console.log('StockListModel.qml',
                    ' ','Component.onCompleted');

        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        fun_db_LoadData_from_TableUserStock();

    }
    Component.onDestruction:
    {
        console.log('StockListModel.qml',
                    ' ','Component.onDestruction');

        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        m_SqliteDbStorage.fun_db_clear_table_TABLE_USERSTOCK();
        fun_db_SaveData_to_TableUserStock();
    }

    function fun_db_LoadData_from_TableUserStock()
    {
        console.log('StockListModel.qml',
                    ' ','fun_db_LoadData_from_TableUserStock()');

        var db =  m_SqliteDbStorage.fun_db_CheckAndCreateDB();
        db.transaction
        (
            function(tx)
            {
                //property string m_str_sql_select_TABLE_USERSTOCK_001 : "SELECT C_INDEX,m_s_Symbol,m_s_Symbol_Extern FROM TABLE_USERSTOCK";
                console.log('StockListModel.qml',
                            ' ','fun_db_LoadData_from_TableUserStock()',
                            ' ','executeSql m_SqliteDbStorage.m_str_sql_select_TABLE_USERSTOCK_001:', m_SqliteDbStorage.m_str_sql_select_TABLE_USERSTOCK_001);
                var rs = tx.executeSql(m_SqliteDbStorage.m_str_sql_select_TABLE_USERSTOCK_001);
                var nRowIndex = 0;
                if (rs.rows.length > 0)
                {
                    nRowIndex = 0;
                    while (nRowIndex < rs.rows.length)
                    {
                        var myItem = rs.rows.item(nRowIndex);
                        id_qml_StockListModel.append( {
                            "m_n_Name": myItem.m_n_Name,
                            "m_s_Symbol": myItem.m_s_Symbol,
                            "m_s_Symbol_Extern": myItem.m_s_Symbol_Extern,
                            "m_l1_Last_Trade_Price_Only": "0.0",
                            "m_c6_Change_Realtime": "0.0",
                            "m_p2_Change_in_Percent": "0.0%"});


                        console.log('StockListModel.qml',
                                    ' ','fun_db_LoadData_from_TableUserStock()',
                                    ' ','nRowIndex=',nRowIndex,
                                    ' ','m_n_Name=',myItem.m_n_Name,
                                    ' ','m_s_Symbol=',myItem.m_s_Symbol,
                                    ' ','m_s_Symbol_Extern=',myItem.m_s_Symbol_Extern);

                        nRowIndex++;
                    }
                }
                else
                {
                    /*

                    id_qml_StockListModel.append( {
                        "m_n_Name": "福日电子",
                        "m_s_Symbol": "600203.SS",
                        "m_s_Symbol_Extern": ".SS",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});

                    id_qml_StockListModel.append( {
                        "m_n_Name": "苏宁云商",
                        "m_s_Symbol": "002024.SZ",
                        "m_s_Symbol_Extern": ".SZ",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});
                    //"m_s_Symbol_Extern": "null/.SS/.SZ",
                    id_qml_StockListModel.append( {
                        "m_n_Name": "Apple Inc.",
                        "m_s_Symbol": "AAPL",
                        "m_s_Symbol_Extern": "",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});

                    id_qml_StockListModel.append( {
                        "m_n_Name": "Adobe Systems Inc.",
                        "m_s_Symbol": "ADBE",
                        "m_s_Symbol_Extern": "",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});


                        */

                }//else
            }//function(tx)
        )//db.transaction
    }//function loadImageData()


    function fun_db_SaveData_to_TableUserStock()
    {
        console.log('StockListModel.qml',
                    ' ','fun_db_SaveData_to_TableUserStock()');

        var db =  m_SqliteDbStorage.fun_db_CheckAndCreateDB();

        db.transaction
        (
            function(tx)
            {
                var nRowIndex = 0;
                while (nRowIndex < id_qml_StockListModel.count)
                {
                    var myItem = id_qml_StockListModel.get(nRowIndex);

                    console.log('StockListModel.qml',
                                ' ','fun_db_SaveData_to_TableUserStock()',
                                ' ','executeSql insert_TABLE_USERSTOCK_001:',m_SqliteDbStorage.m_str_sql_insert_TABLE_USERSTOCK_001,
                                ' ','nRowIndex:',nRowIndex,
                                ' ','m_s_Symbol:',myItem.m_s_Symbol,
                                ' ','m_s_Symbol_Extern:',myItem.m_s_Symbol_Extern);

                    tx.executeSql(m_SqliteDbStorage.m_str_sql_insert_TABLE_USERSTOCK_001, [nRowIndex, myItem.m_s_Symbol, myItem.m_s_Symbol_Extern, myItem.m_n_Name]);

                    nRowIndex++;
                }
            }//function(tx)
        )//db.transaction
    }//function saveImageData()

}//ListModel


