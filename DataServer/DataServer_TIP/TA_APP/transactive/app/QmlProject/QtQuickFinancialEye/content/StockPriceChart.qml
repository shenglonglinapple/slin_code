import QtQuick 2.0

Rectangle
{
    id: id_qml_StockPriceChart
    width: 320
    height: 200

    // new Date()初始化得到的是当前时间
    property var startDate: new Date();
    property var endDate: new Date();


    //UI
    StockDetailInfoType
    {
        //0
        id:m_StockDetailInfoType;
        //1
        width: id_qml_StockPriceChart.width
        //height: 200
        //
        anchors.left: id_qml_StockPriceChart.left
        anchors.right: id_qml_StockPriceChart.right
        anchors.top: id_qml_StockPriceChart.top
        anchors.topMargin: 4
    }

    /*
    StockPriceChartCanvas
    {
        //0
        id:m_StockPriceChartPrice;
        //1
        width: id_qml_StockPriceChart.width
        //height: 200

        anchors.top: m_StockDetailInfoType.bottom
        anchors.left: id_qml_StockPriceChart.left
        anchors.right: id_qml_StockPriceChart.right
        anchors.bottom: m_Text_fromDate.top
    }

    */

    ////////////////////////////////////////////////////////////////////////
    //UI
    Text
    {// 下方的起始日期显示
        id: m_Text_fromDate

        //anchors.top: m_StockPriceChartPrice.bottom
        anchors.left: parent.left
        anchors.bottom: parent.bottom

        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 8

        text: startDate.toDateString()
    }

    Text
    {// 结束日期显示
        id: m_Text_toDate

        //anchors.top: m_StockPriceChartPrice.bottom
        anchors.right: parent.right
        anchors.rightMargin: 32;
        anchors.bottom: parent.bottom

        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 8

        text: endDate.toDateString()
    }//Text


}//Rectangle


