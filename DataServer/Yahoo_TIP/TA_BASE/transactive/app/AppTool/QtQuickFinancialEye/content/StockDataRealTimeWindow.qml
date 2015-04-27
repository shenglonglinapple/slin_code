import QtQuick 2.0

/*
//每个 item 都有 7 条不可见的锚线：左（left）、水平中心（horizontalCenter）、上（top）、下（bottom）、右（right）、垂直中心（verticalCenter）、基线（baseline）
//使用 anchors 布局时，除了对齐锚线，还可以在指定上（topMargin）、下（bottomMargin）、左（leftMargin）、右（rightMargin）
//anchors.horizontalCenter: id_qml_StockDataRealTimeWindow.horizontalCenter
*/



Rectangle
{// 将相关组件放在一个Item容器中
    id: id_qml_StockDataRealTimeWindow
    // 容器的尺寸由组件决定
    width: parent.width;
    height: parent.height*(28/100);
    anchors.top : parent.top
    anchors.left: parent.left
    //anchors.leftMargin: 10
    color:"PeachPuff";
    //color: "transparent"

    property real m_n_Rectangle_LastTradePriceOnyly_width: id_qml_StockDataRealTimeWindow.width/2;
    property real m_n_Rectangle_LastTradePriceOnyly_height: id_qml_StockDataRealTimeWindow.height*(4/12);
    property real m_n_Rectangle_ChangeRealTime_height: id_qml_StockDataRealTimeWindow.height*(2/12);

    Rectangle
    {
        id : m_Rectangle_LastTradePriceOnyly;

        width: m_n_Rectangle_LastTradePriceOnyly_width
        height: m_n_Rectangle_LastTradePriceOnyly_height
        anchors.top : parent.top
        anchors.left: parent.left

        color:"Peru"

        //"LastTradePrice"
        Text
        {// 价格
            id: m_Text_LastTradePriceOnly;

            anchors.left: m_Rectangle_LastTradePriceOnyly.left
            anchors.leftMargin: 10

            anchors.verticalCenter: m_Rectangle_LastTradePriceOnyly.verticalCenter


            font.family: "Abel";//"Open Sans"//"Abel"
            font.pointSize : parent.height/2;
            font.weight: Font.DemiBold
            color:m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            text: m_CurrentUserStockData.m_l1_Last_Trade_Price_Only_current;


        }//Text m_Text_LastTradePriceOnly
    }//m_Item_LastTradePriceOnyly


    //
    Rectangle
    {
        id : m_Rectangle_ChangeRealTime;

        width: m_Rectangle_LastTradePriceOnyly.width/2
        height: m_n_Rectangle_ChangeRealTime_height
        anchors.top : m_Rectangle_LastTradePriceOnyly.bottom
        anchors.topMargin: 1
        anchors.left: parent.left
        color:"Pink"
        //价格变化
        Text
        {// 价格变化
            id: m_Text_ChangeRealTime

            anchors.left: m_Rectangle_ChangeRealTime.left
            anchors.leftMargin: 10
            anchors.verticalCenter: m_Rectangle_ChangeRealTime.verticalCenter

            font.family: "Abel";
            font.pointSize: parent.height/2;
            font.weight: Font.DemiBold
            //horizontalAlignment: Text.AlignLeft
            color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            text: m_CurrentUserStockData.m_c6_Change_Realtime_current;
        }//Text m_Text_ChangeRealTime
    }//m_Item_ChangeRealTime


    Rectangle
    {
        id : m_Rectangle_ChangeInPercent;

        width: m_Rectangle_LastTradePriceOnyly.width/2
        height: m_n_Rectangle_ChangeRealTime_height
        anchors.top : m_Rectangle_LastTradePriceOnyly.bottom
        anchors.topMargin: 1
        anchors.left: m_Rectangle_ChangeRealTime.right
        color:"Plum"
        //价格变化

        Text
        {//价格变化百分比
            id: m_Text_ChangeInPercent
            anchors.verticalCenter: m_Rectangle_ChangeInPercent.verticalCenter

            font.family: "Abel";//Abel//Helvetica//font.family: "Open Sans"
            font.pointSize: parent.height/2
            font.weight: Font.DemiBold
            //horizontalAlignment: Text.AlignRight
            color: m_CurrentUserStockData.m_c6_Change_Realtime_current < 0 ? "red" : "green"
            //text: Math.abs(Math.round(m_CurrentUserStockData.m_real_stockPriceChanged/(m_CurrentUserStockData.m_real_stockPrice - m_CurrentUserStockData.m_real_stockPriceChanged) * 100))/100  + "%";
            text:m_CurrentUserStockData.m_p2_Change_in_Percent_current;
        }//Text m_Text_ChangeInPercent

    }//m_Text_ChangeInPercent




}//Item id_qml_StockDataRealTimeWindow








