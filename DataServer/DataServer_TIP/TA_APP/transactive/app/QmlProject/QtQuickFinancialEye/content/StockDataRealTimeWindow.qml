import QtQuick 2.0

Rectangle
{// 根项目是一个透明的Rectangle。为什么不用Item，我想可能是因为当时布局的时候把color设置出来可能更方便一些
    id: id_qml_StockDataRealTimeWindow

    width:parent.width;
    height: 256;
    anchors.top: parent.top
    anchors.left: parent.left;

    color: "transparent"

/*
//每个 item 都有 7 条不可见的锚线：左（left）、水平中心（horizontalCenter）、上（top）、下（bottom）、右（right）、垂直中心（verticalCenter）、基线（baseline）
//使用 anchors 布局时，除了对齐锚线，还可以在指定上（topMargin）、下（bottomMargin）、左（leftMargin）、右（rightMargin）
//anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
*/

    //"Symbol"
    //"Name"
    Item
    {// 将相关组件放在一个Item容器中
        id: m_Item_Text_Symbol
        // 容器的尺寸由组件决定
        width: m_Text_Symbol.width + m_Text_Name.width + 10
        height: m_Text_Symbol.height
        anchors.top : id_qml_StockDataRealTimeWindow.top
        anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
        //anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter

        Text
        {// Stocqt
            id: m_Text_Symbol

            anchors.verticalCenter: m_Item_Text_Symbol.verticalCenter

            color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            font.family: "Abel";//font.family: "Open Sans"//font.family: "Abel"
            font.pointSize:20
            font.weight: Font.DemiBold
            text: m_CurrentUserStockData.m_s_Symbol_current;
        }//m_Text_Symbol

        Text
        {// Name

            id: m_Text_Name

            anchors.verticalCenter: m_Item_Text_Symbol.verticalCenter
            anchors.left: m_Text_Symbol.right
            anchors.leftMargin: 2

            //color: "#000000"
            color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            font.family: "Abel";//font.family: "Open Sans"
            font.pointSize: 15

            text: "(" + m_CurrentUserStockData.m_n_Name_current + ")";
        }//Text m_Text_Name
    }//Item m_Item_Text_Symbol


    //"LastTradePrice"
    //""
    Item
    {// 将相关组件放在一个Item容器中
        id: m_Item_Text_LastTradePrice
        // 容器的尺寸由组件决定
        width: m_Text_LastTradePriceOnly.width
        height: m_Text_LastTradePriceOnly.height + m_Text_ChangeRealTime.height + 10
        anchors.top : m_Item_Text_Symbol.bottom
        anchors.left: parent.left
        anchors.leftMargin: 10

        Text
        {// 价格
            id: m_Text_LastTradePriceOnly;

            anchors.verticalCenter: m_Item_Text_LastTradePrice.verticalCenter

            //horizontalAlignment: Text.AlignRight
            //color: "#000000"

            color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            font.family: "Abel";//font.family: "Open Sans"//font.family: "Abel"
            font.pointSize:64
            font.weight: Font.DemiBold
            text: m_CurrentUserStockData.m_l1_Last_Trade_Price_Only_current;
        }//Text m_Text_LastTradePriceOnly


        Text
        {// 价格变化
            id: m_Text_ChangeRealTime
            anchors.top: m_Text_LastTradePriceOnly.bottom
            anchors.topMargin: 5
            anchors.left: m_Item_Text_LastTradePrice.left
            anchors.leftMargin: 10
            //anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
            //anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter
            //horizontalAlignment: Text.AlignLeft
            //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
            color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 16
            font.weight: Font.DemiBold
            text: m_CurrentUserStockData.m_c6_Change_Realtime_current;
        }//Text m_Text_ChangeRealTime


        Text
        {//价格变化百分比
            id: m_Text_ChangeInPercent

            anchors.top: m_Text_LastTradePriceOnly.bottom
            anchors.topMargin: 5
            anchors.left: m_Text_ChangeRealTime.right
            anchors.leftMargin: 5
            anchors.right: m_Item_Text_LastTradePrice.right
            anchors.rightMargin: 5
            //anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
            //anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter
            horizontalAlignment: Text.AlignRight
            //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
            color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 16
            font.weight: Font.DemiBold
            //text: Math.abs(Math.round(m_CurrentUserStockData.m_real_stockPriceChanged/(m_CurrentUserStockData.m_real_stockPrice - m_CurrentUserStockData.m_real_stockPriceChanged) * 100))/100  + "%";
            text:m_CurrentUserStockData.m_p2_Change_in_Percent_current;
        }//Text m_Text_ChangeInPercent

    }//Item m_Item_Text_LastTradePrice




}//Rectangle



