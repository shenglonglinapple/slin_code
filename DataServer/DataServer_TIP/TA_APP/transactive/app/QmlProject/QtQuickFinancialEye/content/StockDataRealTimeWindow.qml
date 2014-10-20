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

    Text
    {// Symbol
        id: m_Text_Symbol

        width: 128
        height: 32

        anchors.top: parent.top
        anchors.topMargin: 1
        anchors.left: parent.left
        anchors.leftMargin: 15


        //color: "#000000"
        color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize:20
        font.weight: Font.DemiBold

        // 类似的，对显示文本赋值
        text: m_CurrentUserStockData.m_s_Symbol_current;
    }//Text

    Text
    {// Name

        id: m_Text_Name

        anchors.top: parent.top
        anchors.topMargin: 2
        anchors.left: m_Text_Symbol.right
        anchors.leftMargin: 5
        anchors.right: parent.right
        //elide: Text.ElideMiddle

        //color: "#000000"
        color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 15


        text: "(" + m_CurrentUserStockData.m_n_Name_current + ")";
    }//Text
/*

    Text
    {// 价格
        id: m_Text_LastTradePriceOnly;

        anchors.top: m_Text_Symbol.bottom
        //anchors.topMargin: 1
        anchors.left: parent.left
        //anchors.leftMargin: 1
        anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
        anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter

        horizontalAlignment: Text.AlignRight
        //color: "#000000"
        color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 64
        font.weight: Font.DemiBold

        text: m_CurrentUserStockData.m_l1_Last_Trade_Price_Only_current;
    }//Text

    Text
    {// 价格变化
        id: m_Text_ChangeRealTime
        anchors.top: m_Text_LastTradePriceOnly.bottom
        //anchors.topMargin: 5
        anchors.left: parent.left
        //anchors.leftMargin: 5
        anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
        anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter


        horizontalAlignment: Text.AlignRight

        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 10
        font.weight: Font.Bold

        text: m_CurrentUserStockData.m_c6_Change_Realtime_current;
    }//Text

    Text
    {//价格变化百分比
        id: m_Text_ChangeInPercent

        anchors.top: m_Text_LastTradePriceOnly.bottom
        //anchors.topMargin: 5
        anchors.left: m_Text_ChangeRealTime.right
        //anchors.leftMargin: 20
        anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
        anchors.verticalCenter: id_qml_StockDataRealTimeWindow.verticalCenter


        horizontalAlignment: Text.AlignRight

        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 10
        font.weight: Font.Bold

        //text: Math.abs(Math.round(m_CurrentUserStockData.m_real_stockPriceChanged/(m_CurrentUserStockData.m_real_stockPrice - m_CurrentUserStockData.m_real_stockPriceChanged) * 100))/100  + "%";
        text:m_CurrentUserStockData.m_p2_Change_in_Percent_current;
    }//Text
*/

}//Rectangle



