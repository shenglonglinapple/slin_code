import QtQuick 2.0

Rectangle {                      // 根项目是一个透明的Rectangle。为什么不用Item，我想可能是因为当时布局的时候把color设置出来可能更方便一些
    id: root
    width: 440
    height: 160
    color: "transparent"

    property var stock: null          // var类型的stock属性，它接受的是stocqt.qml中定义的StockModel

    Text {                               // id
        id: stockIdText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 38
        font.weight: Font.DemiBold
        text: root.stock.stockId        // 类似的，对显示文本赋值
    }

    Text {                            // name
        id: stockNameText
        anchors.left: parent.left
        anchors.leftMargin: 5
        anchors.bottom: priceChangePercentage.bottom
        anchors.right: priceChangePercentage.left
        anchors.rightMargin: 15
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 16
        elide: Text.ElideRight
        text: root.stock.stockName
    }

    Text {                                 // 价格
        id: price
        anchors.right: parent.right
        anchors.rightMargin: 5
        anchors.top: parent.top
        anchors.topMargin: 15
        horizontalAlignment: Text.AlignRight
        color: "#000000"
        font.family: "Open Sans"
        font.pointSize: 30
        font.weight: Font.DemiBold
        text: root.stock.stockPrice
    }

    Text {                            // 价格变化
        id: priceChange
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: price.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        color: root.stock.stockPriceChanged < 0 ? "#d40000" : "#328930"
        font.family: "Open Sans"
        font.pointSize: 20
        font.weight: Font.Bold
        text: root.stock.stockPriceChanged
    }

    Text {                                 // 价格变化百分比
        id: priceChangePercentage
        anchors.right: parent.right
        anchors.rightMargin: 20
        anchors.top: priceChange.bottom
        anchors.topMargin: 5
        horizontalAlignment: Text.AlignRight
        color: root.stock.stockPriceChanged < 0 ? "#d40000" : "#328930"
        font.family: "Open Sans"
        font.pointSize: 18
        font.weight: Font.Bold
        text: Math.abs(Math.round(root.stock.stockPriceChanged/(root.stock.stockPrice - root.stock.stockPriceChanged) * 100))/100  +"%"
    }
}
