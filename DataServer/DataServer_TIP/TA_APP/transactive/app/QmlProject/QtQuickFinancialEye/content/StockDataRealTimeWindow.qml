import QtQuick 2.0

Rectangle
{// 根项目是一个透明的Rectangle。为什么不用Item，我想可能是因为当时布局的时候把color设置出来可能更方便一些
    id: id_qml_StockDataRealTimeWindow

    width: 440
    height: 160

    color: "transparent"

    // var类型的stock属性，它接受的是stocqt.qml中定义的StockModel
   // property var m_data_stock_ref: null


    Text
    {// stockId
        id: m_Text_stockId
        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.top: parent.top
        anchors.topMargin: 1

        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 38
        font.weight: Font.DemiBold

        // 类似的，对显示文本赋值
        text: m_CurrentUserStockData.m_s_Symbol_current;
    }//Text

    Text
    {// stockName

        id: m_Text_Name

        anchors.left: parent.left
        anchors.leftMargin: 1
        anchors.bottom: m_Text_ChangeInPercent.bottom
        anchors.right: m_Text_ChangeInPercent.left
        anchors.rightMargin: 1

        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 16
        elide: Text.ElideRight

        text: m_CurrentUserStockData.m_n_Name_current;
    }//Text

    Text
    {// 价格
        id: m_Text_LastTradePriceOnly;

        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15

        horizontalAlignment: Text.AlignRight
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 30
        font.weight: Font.DemiBold

        text: m_CurrentUserStockData.m_l1_Last_Trade_Price_Only_current;
    }//Text

    Text
    {// 价格变化
        id: m_Text_ChangeRealTime
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: m_Text_LastTradePriceOnly.bottom
        anchors.topMargin: 5

        horizontalAlignment: Text.AlignRight

        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold

        text: m_CurrentUserStockData.m_c6_Change_Realtime_current;
    }//Text

    Text
    {//价格变化百分比
        id: m_Text_ChangeInPercent

        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: m_Text_ChangeRealTime.bottom
        anchors.topMargin: 5

        horizontalAlignment: Text.AlignRight

        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 18
        font.weight: Font.Bold

        //text: Math.abs(Math.round(m_CurrentUserStockData.m_real_stockPriceChanged/(m_CurrentUserStockData.m_real_stockPrice - m_CurrentUserStockData.m_real_stockPriceChanged) * 100))/100  + "%";
        text:m_CurrentUserStockData.m_p2_Change_in_Percent_current;
    }//Text

}//Rectangle



