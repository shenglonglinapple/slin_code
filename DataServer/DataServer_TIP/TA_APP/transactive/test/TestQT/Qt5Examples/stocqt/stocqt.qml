import QtQuick 2.0
import QtQml.Models 2.1
import "./content"                   // 添加其他qml文件路径

Rectangle {
    id: mainRect
    width: 1000
    height: 700

    property int listViewActive: 0      // 该页面实际是一个ListView的一部分，这个属性用来表明前面的列表页面是否被激活

    Rectangle {                         // 导航栏
        id: banner
        height: 80
        anchors.top: parent.top
        width: parent.width
        color: "#000000"

        Image {
            id: arrow
            source: "./content/images/icon-left-arrow.png"
            anchors.left: banner.left
            anchors.leftMargin: 20
            anchors.verticalCenter: banner.verticalCenter
            visible: root.currentIndex == 1 ? true : false  // 曲线页面是ListView的第二个页面，currentIndex的值也就是1

            MouseArea {
                anchors.fill: parent
                onClicked: listViewActive = 1;
            }
        }

        Item {                                    // 将相关组件放在一个Item容器中
            id: textItem
            width: stocText.width + qtText.width           // 容器的尺寸由组件决定
            height: stocText.height + qtText.height
            anchors.horizontalCenter: banner.horizontalCenter
            anchors.verticalCenter: banner.verticalCenter

            Text {                                  // Stoc
                id: stocText
                anchors.verticalCenter: textItem.verticalCenter
                color: "#ffffff"
                font.family: "Abel"
                font.pointSize: 40
                text: "Stoc"
            }
            Text {                                   // Qt
                id: qtText
                anchors.verticalCenter: textItem.verticalCenter
                anchors.left: stocText.right
                color: "#5caa15"
                font.family: "Abel"
                font.pointSize: 40
                text: "Qt"
            }
        }
    }

    ListView {                        // 标题栏下方则是ListView的内容，它为列表页面与曲线页面提供了滑动切换的能力
        id: root
        width: parent.width
        anchors.top: banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem        // 设置该属性使View停止在一个完整的页面上
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250                  // 这里设置了一个无形的高亮，它不显示，但提供了0.25秒的切换动画
        focus: false
        orientation: ListView.Horizontal
        boundsBehavior: Flickable.StopAtBounds     // 滑动时停在边界，默认可以拉拽更远并在弹回时带有超调效果
        currentIndex: listViewActive == 0 ? 1 : 0  // 使用属性绑定，当listViewActive被激活时，使currentIndex置0，从而跳转到列表页面
        onCurrentIndexChanged: {
            if (currentIndex == 1)
                listViewActive = 0;
        }

        StockModel {                            // 初始化数据模型
            id: stock
            stockId: listView.currentStockId     // 注意这个listView不是其父ListView，而是下面那个，即列表页面
            stockName: listView.currentStockName  // 列表页面将当前所选的股票ID及名字赋给StockModel，使其取得相应的数据
            onStockIdChanged: stock.updateStock(); // 当ID改变时数据更新
            onDataReady: {
                //console.log(listView.currentStockId, listView.currentStockName)
                root.positionViewAtIndex(1, ListView.SnapPosition)    // 上面的高亮即为这里的ListView.SnapPosition做准备，数据变更后切换到曲线页面，带有0.25秒的过渡动画
                stockView.update()                                    // 页面更新
            }
        }

        model: ObjectModel
        {       // ObjectModel源自上面import的Qt.QML.Model 2.1，它使得ListView可以使用一组对象作为模型
            StockListView
            {           // 列表页面
                id: listView
                width: root.width
                height: root.height;
            }

            StockView
            {               // 曲线页面
                id: stockView;
                width: root.width
                height: root.height
                stocklist: listView
                stock: stock
            }
        }
    }
}


