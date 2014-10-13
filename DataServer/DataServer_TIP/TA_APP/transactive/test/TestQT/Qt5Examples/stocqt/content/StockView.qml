import QtQuick 2.0
import QtQuick.Window 2.1               // 下面的代码使用了Screen因此引入这个模块

Rectangle {
    id: root
    width: 320
    height: 480
    color: "transparent"

    property var stock: null
    property var stocklist: null
    signal settingsClicked

    function update() {                          // 用来更新图表显示
        chart.update()
    }

    Rectangle {
        id: mainRect
        color: "transparent"
        anchors.fill: parent

        StockInfo
        {                              // 提供左上方的股票信息
            id: stockInfo;
            anchors.left: parent.left;
            anchors.leftMargin: 10
            anchors.top: parent.top
            anchors.topMargin: 15
            height: 160
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left                                                                                                // 基于属性绑定的屏幕转向后布局方式的变化
            anchors.rightMargin: 20
            stock: root.stock
        }

        StockChart {                              // 右方的曲线绘制部分
            id: chart
            anchors.bottom: Screen.primaryOrientation === Qt.PortraitOrientation ? settingsPanel.top : parent.bottom
            anchors.bottomMargin: 20
            anchors.top : Screen.primaryOrientation === Qt.PortraitOrientation ? stockInfo.bottom : parent.top
            anchors.topMargin: 20
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.width - 40 : 0.6 * parent.width
            stockModel: root.stock
            settings: settingsPanel
        }

        StockSettingsPanel {                      //  左下方的显示设置面板
            id: settingsPanel
            anchors.left: parent.left
            anchors.leftMargin: 20
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : chart.left
            anchors.rightMargin: 20
            anchors.bottom: parent.bottom
            onDrawOpenPriceChanged: root.update()           // 更新
            onDrawClosePriceChanged: root.update();
            onDrawHighPriceChanged: root.update();
            onDrawLowPriceChanged: root.update();
        }
    }
}


