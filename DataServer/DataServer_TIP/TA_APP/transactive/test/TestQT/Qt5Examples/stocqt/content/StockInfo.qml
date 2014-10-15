import QtQuick 2.0

Rectangle
{// 根项目是一个透明的Rectangle。为什么不用Item，我想可能是因为当时布局的时候把color设置出来可能更方便一些
    id: id_qml_StockInfo
    width: 440
    height: 160
    color: "transparent"

    // var类型的stock属性，它接受的是stocqt.qml中定义的StockModel
    property var m_data_stock_ref: null


    Text
    {// stockId
        id: stockIdText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 38
        font.weight: Font.DemiBold
        text: id_qml_StockInfo.m_data_stock_ref.stockId        // 类似的，对显示文本赋值
    }

    Text
    {// stockName
        id: stockNameText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: priceChangePercentage.bottom
        anchors.right: priceChangePercentage.left
        anchors.rightMargin: 15
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 16
        elide: Text.ElideRight
        text: id_qml_StockInfo.m_data_stock_ref.stockName
    }

    Text
    {// 价格
        id: price
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        horizontalAlignment: Text.AlignRight
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 30
        font.weight: Font.DemiBold
        //adjusted;  // 将最新的的调整收盘价赋予stockPrice
        text: id_qml_StockInfo.m_data_stock_ref.stockPrice
    }

    Text
    {// 价格变化
        id: priceChange
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: price.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        text: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged
    }

    Text
    {// 价格变化百分比
        id: priceChangePercentage
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: priceChange.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        //color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "#d40000" : "#328930"
        color: id_qml_StockInfo.m_data_stock_ref.stockPriceChanged < 0 ? "red" : "green"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 18
        font.weight: Font.Bold
        text: Math.abs(Math.round(id_qml_StockInfo.m_data_stock_ref.stockPriceChanged/(id_qml_StockInfo.m_data_stock_ref.stockPrice - id_qml_StockInfo.m_data_stock_ref.stockPriceChanged) * 100))/100  +"%"
    }
}//Rectangle



