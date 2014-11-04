import QtQuick 2.0
import QtQml.Models 2.1

ListModel
{
    id:id_qml_UsrSearchStockListModel


    /*
    ListElement
    {
        C_INDEX:"0";
        m_n_Name:"R003";
        m_s_Symbol:"600203.SS";
        m_s_Symbol_Extern:".SS"
    }

    ListElement
    {
        C_INDEX:"0";
        m_n_Name:"福日电子";
        m_s_Symbol:"201000.SS";
        m_s_Symbol_Extern:".SS"
    }

    ListElement
    {
        C_INDEX:"0";
        m_n_Name:"苏宁云商";
        m_s_Symbol:"002024.SZ";
        m_s_Symbol_Extern:".SZ"
    }

    */

    function fun_createListElement(myItem)
    {// 存储数据对象函数

        //C_INDEX, m_s_Symbol, m_s_Symbol_Extern, m_n_Name
        id_qml_UsrSearchStockListModel.append(
                    {"C_INDEX": myItem.C_INDEX,
                        "m_s_Symbol":myItem.m_s_Symbol,
                        "m_s_Symbol_Extern":myItem.m_s_Symbol_Extern,
                        "m_n_Name":myItem.m_n_Name});
        return;
    }

    function fun_db_select_from_TableTotalStock(strSeachStock)
    {
        console.log('UsrSearchStockListModel.qml',
                    ' ','begin fun_db_select_from_TableTotalStock()');
        var strSQL = "";

        var db =  m_SqliteDbStorage.fun_db_CheckAndCreateDB();
        db.transaction
        (
            function(tx)
            {
                console.log('UsrSearchStockListModel.qml',
                            ' ','begin db.transaction(callback(tx))');
                //property string m_str_sql_select_TABLE_TOTALSTOCK_003 : "SELECT C_INDEX, m_s_Symbol, m_s_Symbol_Extern, m_n_Name FROM TABLE_TOTALSTOCK where m_s_Symbol LIKE '%?%'";

                strSQL = m_SqliteDbStorage.m_str_sql_select_TABLE_TOTALSTOCK_003.replace("?", strSeachStock);
                console.log("UsrSearchStockListModel.qml",
                            " ","fun_db_select_from_TableTotalStock()",
                            " ","strSQL:", strSQL);
                var rs = tx.executeSql(strSQL);

                var nRowIndex = 0;
                if (rs.rows.length > 0)
                {
                    nRowIndex = 0;
                    while (nRowIndex < rs.rows.length)
                    {
                        var myItem = rs.rows.item(nRowIndex);

                        console.log("UsrSearchStockListModel.qml",
                                    " ","fun_db_select_from_TableTotalStock()",
                                    " ","nRowIndex=", nRowIndex,
                                    " ","C_INDEX=",myItem.C_INDEX,
                                    " ","m_s_Symbol=",myItem.m_s_Symbol,
                                    " ","m_s_Symbol_Extern=",myItem.m_s_Symbol_Extern,
                                    " ","m_n_Name=",myItem.m_n_Name);

                        fun_createListElement(myItem);

                        nRowIndex++;
                    }
                }


                console.log('UsrSearchStockListModel.qml',
                            ' ','end db.transaction(callback(tx))');
            }//function(tx)
        )//db.transaction


        console.log('UsrSearchStockListModel.qml',
                    ' ','end fun_db_select_from_TableTotalStock()');
    }//function fun_db_getCount_from_TableTotalStock()



}//ListModel



