import QtQuick 2.0
import QtQml.Models 2.1
import QtQuick.LocalStorage 2.0//sqlite db

ListModel
{
    id: id_qml_MyStocksListModel;

    Component.onCompleted:
    {
        console.log("MyStocksListModel.qml",
                    " ", "Component.onCompleted");

        //for Test. TODO.
        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        m_SqliteDbStorage.fun_db_drop_table_TRABLE_USERSTOCK();
        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        fun_db_LoadData_from_TableUserStock();

    }
    Component.onDestruction:
    {
        console.log("MyStocksListModel.qml",
                    " ", "Component.onDestruction");

        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        m_SqliteDbStorage.fun_db_drop_table_TRABLE_USERSTOCK();
        m_SqliteDbStorage.fun_db_CheckAndCreateTable_TABLE_USERSTOCK();
        fun_db_SaveData_to_TableUserStock();
    }

    function fun_db_LoadData_from_TableUserStock()
    {
        console.log("MyStocksListModel.qml",
                    " ", "fun_db_LoadData_from_TableUserStock");

        var db =  m_SqliteDbStorage.fun_db_CheckAndCreateDB();
        db.transaction
        (
            function(tx)
            {
                //property string m_str_sql_select_TABLE_USERSTOCK_001 : "SELECT C_INDEX,m_s_Symbol,m_s_Symbol_Extern FROM TABLE_USERSTOCK";
                console.log("MyStocksListModel.qml",
                            " ", "fun_db_LoadData_from_TableUserStock",
                            " ", "executeSql=",m_SqliteDbStorage.m_str_sql_select_TABLE_USERSTOCK_001);

                var rs = tx.executeSql(m_SqliteDbStorage.m_str_sql_select_TABLE_USERSTOCK_001);
                var nRowIndex = 0;
                if (rs.rows.length > 0)
                {
                    nRowIndex = 0;
                    while (nRowIndex < rs.rows.length)
                    {
                        var myItem = rs.rows.item(nRowIndex);                       
                        id_qml_MyStocksListModel.append(
                                    {
                                        "m_x_Stock_Exchange": "shengzhen",
                                        "m_s_Symbol":myItem.m_s_Symbol,
                                        "m_c6_Change_Realtime":"3.00",
                                        "m_p2_Change_in_Percent":"1.00%",
                                        "m_d1_Last_Trade_Date":"3.00",
                                        "m_ti_Last_Trade_Time":"2014/10/20 10:01:02",
                                        "m_p_Previous_Close":"3.00",
                                        "m_o_Open":"3.00",
                                        "m_b_Bid":"10000",
                                        "m_a_Ask":"10",
                                        "m_g_Day_Low":"3.00",
                                        "m_h_Day_High":"3.00",
                                        "m_m_Day_Range":"3.00-3.00",
                                        "m_l1_Last_Trade_Price_Only":"3.00",
                                        "m_t8_1year_Target_Price":"3.00",
                                        "m_v_Volume":"300000",
                                        "m_a2_Average_Daily_Volume":"100",
                                        "m_n_Name":myItem.m_n_Name
                                    });

                        console.log("MyStocksListModel.qml",
                                    " ", "fun_db_LoadData_from_TableUserStock",
                                    " ", "nRowIndex=",nRowIndex,
                                    " ", "m_n_Name=",myItem.m_n_Name,
                                    " ", "m_s_Symbol=",myItem.m_s_Symbol);

                        nRowIndex++;
                    }
                }
                else
                {
                    id_qml_MyStocksListModel.append(
                                {
                                    "m_x_Stock_Exchange": "shengzhen",
                                    "m_s_Symbol":"600667.SS",
                                    "m_c6_Change_Realtime":"3.00",
                                    "m_p2_Change_in_Percent":"1.00%",
                                    "m_d1_Last_Trade_Date":"3.00",
                                    "m_ti_Last_Trade_Time":"2014/10/20 10:01:02",
                                    "m_p_Previous_Close":"3.00",
                                    "m_o_Open":"3.00",
                                    "m_b_Bid":"10000",
                                    "m_a_Ask":"10",
                                    "m_g_Day_Low":"3.00",
                                    "m_h_Day_High":"3.00",
                                    "m_m_Day_Range":"3.00-3.00",
                                    "m_l1_Last_Trade_Price_Only":"3.00",
                                    "m_t8_1year_Target_Price":"3.00",
                                    "m_v_Volume":"300000",
                                    "m_a2_Average_Daily_Volume":"100",
                                    "m_n_Name":"三全食品"
                                });

                    id_qml_MyStocksListModel.append(
                                {
                                    "m_x_Stock_Exchange": "shengzhen",
                                    "m_s_Symbol":"002216.SZ",
                                    "m_c6_Change_Realtime":"3.00",
                                    "m_p2_Change_in_Percent":"1.00%",
                                    "m_d1_Last_Trade_Date":"3.00",
                                    "m_ti_Last_Trade_Time":"2014/10/20 10:01:02",
                                    "m_p_Previous_Close":"3.00",
                                    "m_o_Open":"3.00",
                                    "m_b_Bid":"10000",
                                    "m_a_Ask":"10",
                                    "m_g_Day_Low":"3.00",
                                    "m_h_Day_High":"3.00",
                                    "m_m_Day_Range":"3.00-3.00",
                                    "m_l1_Last_Trade_Price_Only":"3.00",
                                    "m_t8_1year_Target_Price":"3.00",
                                    "m_v_Volume":"300000",
                                    "m_a2_Average_Daily_Volume":"100",
                                    "m_n_Name":"太极实业"
                                });



                    /*
                "m_x_Stock_Exchange": varVariableLst[0],
                "m_s_Symbol":varVariableLst[1],
                "m_c6_Change_Realtime":varVariableLst[2],
                "m_p2_Change_in_Percent":varVariableLst[3],
                "m_d1_Last_Trade_Date":varVariableLst[4],
                "m_ti_Last_Trade_Time":varVariableLst[5],
                "m_p_Previous_Close":varVariableLst[6],
                "m_o_Open":varVariableLst[7],
                "m_b_Bid":varVariableLst[8],
                "m_a_Ask":varVariableLst[9],
                "m_g_Day_Low":varVariableLst[10],
                "m_h_Day_High":varVariableLst[11],
                "m_m_Day_Range":varVariableLst[12],
                "m_l1_Last_Trade_Price_Only":varVariableLst[13],
                "m_t8_1year_Target_Price":varVariableLst[14],
                "m_v_Volume":varVariableLst[15],
                "m_a2_Average_Daily_Volume":varVariableLst[16]
                "m_n_Name":varVariableLst[17],
                    */


                    //do nothing
                }//else
            }//function(tx)
        )//db.transaction
    }//function loadImageData()


    function fun_db_SaveData_to_TableUserStock()
    {
        console.log("MyStocksListModel.qml",
                    " ", "fun_db_SaveData_to_TableUserStock");

        var db =  m_SqliteDbStorage.fun_db_CheckAndCreateDB();

        db.transaction
        (
            function(tx)
            {
                var nRowIndex = 0;
                while (nRowIndex < id_qml_MyStocksListModel.count)//id_qml_MyStocksListModel
                {
                    var myItem = id_qml_MyStocksListModel.get(nRowIndex);
                    console.log("MyStocksListModel.qml",
                                " ", "fun_db_SaveData_to_TableUserStock",
                                " ", "executeSql=",m_SqliteDbStorage.m_str_sql_insert_TABLE_USERSTOCK_001,
                                " ", "nRowIndex=",nRowIndex,
                                " ", "m_s_Symbol=",myItem.m_s_Symbol,
                                " ", "m_n_Name=",myItem.m_n_Name);

                    tx.executeSql(m_SqliteDbStorage.m_str_sql_insert_TABLE_USERSTOCK_001, [nRowIndex, myItem.m_s_Symbol, myItem.m_n_Name]);

                    nRowIndex++;
                }
            }//function(tx)
        )//db.transaction
    }//function saveImageData()

}//ListModel


