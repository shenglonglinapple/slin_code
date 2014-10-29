import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1
import QtQuick.LocalStorage 2.0//sqlite db

ListModel
{
    id: id_qml_StockListModel
    Component.onCompleted:
    {
        console.log('StockListModel.qml',
                    ' ','Component.onCompleted');
        fun_db_LoadUserStockData();

    }
    Component.onDestruction:
    {
        console.log('StockListModel.qml',
                    ' ','Component.onDestruction');
        fun_db_SaveUserStockData();
    }


    function fun_db_LoadUserStockData()
    {
        console.log('StockListModel.qml',
                    ' ','fun_db_LoadUserStockData()');
        //object openDatabaseSync(string name, string version, string description, int estimated_size, jsobject callback(db))
        var db =  LocalStorage.openDatabaseSync("DB_QtQuickFinancialEye", "1.0", "My model SQL", 50000);
        db.transaction
        (
            function(tx)
            {
                tx.executeSql('DROP TABLE TABLE_USERSTOCK');
                // Create the database if it doesn't already exist
                //
                tx.executeSql('CREATE TABLE IF NOT EXISTS TABLE_USERSTOCK(ID INTEGER primary key, m_n_Name TEXT)');
                // tx.executeSql( 'delete from Images  where id == 1 ');

                var rs = tx.executeSql('SELECT ID, m_n_Name FROM TABLE_USERSTOCK');
                var index = 0;
                if (rs.rows.length > 0)
                {
                    index = 0;
                    while (index < rs.rows.length)
                    {
                        var myItem = rs.rows.item(index);
                        id_qml_StockListModel.append( {
                            "m_n_Name": myItem.m_n_Name,
                            "m_s_Symbol": myItem.m_n_Name,
                            "m_l1_Last_Trade_Price_Only": "0.0",
                            "m_c6_Change_Realtime": "0.0",
                            "m_p2_Change_in_Percent": "0.0%"});

                        index++;
                    }
                }
                else
                {
                    id_qml_StockListModel.append( {
                        "m_n_Name": "Apple Inc.",
                        "m_s_Symbol": "AAPL",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});


                    id_qml_StockListModel.append( {
                        "m_n_Name": "Adobe Systems Inc.",
                        "m_s_Symbol": "ADBE",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});

                    /*
                    id_qml_StockListModel.append( {
                        "m_n_Name": "Analog Devices, Inc.",
                        "m_s_Symbol": "ADI",
                        "m_l1_Last_Trade_Price_Only": "0.0",
                        "m_c6_Change_Realtime": "0.0",
                        "m_p2_Change_in_Percent": "0.0%"});
                    */

                }
            }//function(tx)
        )//db.transaction
    }//function loadImageData()


    function fun_db_SaveUserStockData()
    {
        console.log('StockListModel.qml',
                    ' ','fun_db_SaveUserStockData()');
        var db =  LocalStorage.openDatabaseSync("DB_QtQuickFinancialEye", "1.0", "My model SQL", 50000);
        db.transaction
        (
            function(tx)
            {
                tx.executeSql('DROP TABLE TABLE_USERSTOCK');
                tx.executeSql('CREATE TABLE IF NOT EXISTS TABLE_USERSTOCK(ID INTEGER primary key, m_n_Name TEXT)');
                var index = 0;
                while (index < id_qml_StockListModel.count)
                {
                    var myItem = id_qml_StockListModel.get(index);
                    tx.executeSql('INSERT INTO TABLE_USERSTOCK(ID, m_n_Name) VALUES(?,?)', [index, myItem.m_n_Name]);
                    index++;
                }
            }//function(tx)
        )//db.transaction
    }//function saveImageData()

}//ListModel



/*
ListModel
{
    id:id_qml_StockListModel;
    //
    ListElement
    {
        m_n_Name: "Apple Inc.";
        m_s_Symbol: "AAPL";
        m_l1_Last_Trade_Price_Only: "0.0";
        m_c6_Change_Realtime: "0.0";
        m_p2_Change_in_Percent: "0%"

    }
    //
    ListElement
    {
        m_n_Name: "Adobe Systems Inc.";
        m_s_Symbol: "ADBE";
        m_l1_Last_Trade_Price_Only: "0.0";
        m_c6_Change_Realtime: "0.0";
        m_p2_Change_in_Percent: "0%"
    }
    //
    ListElement
    {
        m_n_Name: "Analog Devices, Inc.";
        m_s_Symbol: "ADI";
        m_l1_Last_Trade_Price_Only: "0.0";
        m_c6_Change_Realtime: "0.0";
        m_p2_Change_in_Percent: "0%"
    }

}//ListModel

*/



/*
//work with StockListDelegate.qml StockListView.qml
ListModel
{
    id: id_qml_StockListModel
    // Data from : http://en.wikipedia.org/wiki/NASDAQ-100// 这里告诉了我们数据来源
    ListElement
    {
        name: "Apple Inc.";
        stockId: "AAPL";
        value: "0.0";
        change: "0.0";
        changePercentage: "0.0"
    }
    ListElement {name: "Adobe Systems Inc."; stockId: "ADBE"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Analog Devices, Inc."; stockId: "ADI"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Automatic Data Processing, Inc."; stockId: "ADP"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Autodesk, Inc."; stockId: "ADSK"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Akamai Technologies, Inc."; stockId: "AKAM"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Altera Corp."; stockId: "ALTR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Alexion Pharmaceuticals, Inc."; stockId: "ALXN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Applied Materials, Inc."; stockId: "AMAT"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Amgen Inc."; stockId: "AMGN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Amazon.com Inc."; stockId: "AMZN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Activision Blizzard, Inc."; stockId: "ATVI"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Avago Technologies Limited"; stockId: "AVGO"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Bed Bath & Beyond Inc."; stockId: "BBBY"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Baidu, Inc."; stockId: "BIDU"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Biogen Idec Inc."; stockId: "BIIB"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Broadcom Corp."; stockId: "BRCM"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "CA Technologies"; stockId: "CA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Celgene Corporation"; stockId: "CELG"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Cerner Corporation"; stockId: "CERN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Check Point Software Technologies Ltd."; stockId: "CHKP"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "CH Robinson Worldwide Inc."; stockId: "CHRW"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Charter Communications, Inc."; stockId: "CHTR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Comcast Corporation"; stockId: "CMCSA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Costco Wholesale Corporation"; stockId: "COST"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Cisco Systems, Inc."; stockId: "CSCO"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Catamaran Corporation"; stockId: "CTRX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Cognizant Technology Solutions Corporation"; stockId: "CTSH"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Citrix Systems, Inc."; stockId: "CTXS"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Discovery Communications, Inc."; stockId: "DISCA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Dish Network Corp."; stockId: "DISH"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Dollar Tree, Inc."; stockId: "DLTR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "DIRECTV"; stockId: "DTV"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "eBay Inc."; stockId: "EBAY"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Equinix, Inc."; stockId: "EQIX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Express Scripts Holding Company"; stockId: "ESRX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Expeditors International of Washington Inc."; stockId: "EXPD"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Expedia Inc."; stockId: "EXPE"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Fastenal Company"; stockId: "FAST"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Facebook, Inc."; stockId: "FB"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "F5 Networks, Inc."; stockId: "FFIV"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Fiserv, Inc."; stockId: "FISV"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Twenty-First Century Fox, Inc."; stockId: "FOXA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Gilead Sciences Inc."; stockId: "GILD"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Keurig Green Mountain, Inc."; stockId: "GMCR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Google Inc."; stockId: "GOOG"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Google Inc."; stockId: "GOOGL"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Garmin Ltd."; stockId: "GRMN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Henry Schein, Inc."; stockId: "HSIC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Illumina Inc."; stockId: "ILMN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Intel Corporation"; stockId: "INTC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Intuit Inc."; stockId: "INTU"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Intuitive Surgical, Inc."; stockId: "ISRG"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "KLA-Tencor Corporation"; stockId: "KLAC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Kraft Foods Group, Inc."; stockId: "KRFT"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Liberty Global plc"; stockId: "LBTYA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Liberty Interactive Corporation"; stockId: "LINTA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Linear Technology Corporation"; stockId: "LLTC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Liberty Media Corporation"; stockId: "LMCA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Marriott International, Inc."; stockId: "MAR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Mattel, Inc"; stockId: "MAT"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Mondelez International, Inc."; stockId: "MDLZ"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Monster Beverage Corporation"; stockId: "MNST"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Microsoft Corporation"; stockId: "MSFT"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Micron Technology Inc."; stockId: "MU"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Maxim Integrated Products, Inc."; stockId: "MXIM"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Mylan, Inc."; stockId: "MYL"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Netflix, Inc."; stockId: "NFLX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "NetApp, Inc."; stockId: "NTAP"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "NVIDIA Corporation"; stockId: "NVDA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "NXP Semiconductors NV"; stockId: "NXPI"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "O'Reilly Automotive Inc."; stockId: "ORLY"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Paychex, Inc."; stockId: "PAYX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "PACCAR Inc."; stockId: "PCAR"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "The Priceline Group Inc."; stockId: "PCLN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "QUALCOMM Incorporated"; stockId: "QCOM"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Regeneron Pharmaceuticals, Inc."; stockId: "REGN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Ross Stores Inc."; stockId: "ROST"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "SBA Communications Corp."; stockId: "SBAC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Starbucks Corporation"; stockId: "SBUX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Sigma-Aldrich Corporation"; stockId: "SIAL"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Sirius XM Holdings Inc."; stockId: "SIRI"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "SanDisk Corp."; stockId: "SNDK"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Staples, Inc."; stockId: "SPLS"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Stericycle, Inc."; stockId: "SRCL"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Seagate Technology Public Limited Company"; stockId: "STX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Symantec Corporation"; stockId: "SYMC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "TripAdvisor Inc."; stockId: "TRIP"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Tractor Supply Company"; stockId: "TSCO"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Tesla Motors, Inc."; stockId: "TSLA"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Texas Instruments Inc."; stockId: "TXN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Viacom, Inc."; stockId: "VIAB"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "VimpelCom Ltd."; stockId: "VIP"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Vodafone Group Public Limited Company"; stockId: "VOD"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Verisk Analytics, Inc."; stockId: "VRSK"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Vertex Pharmaceuticals Incorporated"; stockId: "VRTX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Western Digital Corporation"; stockId: "WDC"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Whole Foods Market, Inc."; stockId: "WFM"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Wynn Resorts Ltd."; stockId: "WYNN"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
    ListElement {name: "Xilinx Inc."; stockId: "XLNX"; value: "0.0"; change: "0.0"; changePercentage: "0.0"}
}


*/
