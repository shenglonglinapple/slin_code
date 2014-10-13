import QtQuick 2.0

Rectangle {
    id: root
    width: 320
    height: 410
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "white"

    property string currentStockId: ""
    property string currentStockName: ""

    ListView {
        id: view
        anchors.fill: parent
        width: parent.width
        clip: true                            // clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: StockListModel{}                 // 定义model

        function requestUrl(stockId) {            // 最近5天的url创建函数，与StockModel不同的是，由于未定义stockId属性，它带有这样一个参数
            var endDate = new Date("");            // today
            var startDate = new Date()
            startDate.setDate(startDate.getDate() - 5);

            var request = "http://ichart.finance.yahoo.com/table.csv?";
            request += "s=" + stockId;
            request += "&g=d";
            request += "&a=" + startDate.getMonth();
            request += "&b=" + startDate.getDate();
            request += "&c=" + startDate.getFullYear();
            request += "&d=" + endDate.getMonth();
            request += "&e=" + endDate.getDate();
            request += "&f=" + endDate.getFullYear();
            request += "&g=d";
            request += "&ignore=.csv";
            return request;
        }

        function getCloseValue(index) {
            var req = requestUrl(model.get(index).stockId);   // 得到对应的股票Id

            if (!req)
                return;

            var xhr = new XMLHttpRequest;

            xhr.open("GET", req, true);

            xhr.onreadystatechange = function() {
                if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE) {
                    var records = xhr.responseText.split('\n');
                    if (records.length > 0) {
                        var r = records[1].split(',');               // 第一条数据，即最新一天的数据
                        model.setProperty(index, "value", r[4]);     // 与StockModel类似，第五个数据为'Close'，即收盘价
                                                                     // 这里将model中index位置数据的"value"值设置为该收盘价                                                                                                    // 注意这个model是StockListModel而不是StockModel
                        var today = parseFloat(r[4]);            // parseFloat()将字符串转化成浮点数，变量声明为var而不是real
                        r = records[2].split(',');                  // 再取前一天数据
                        var yesterday = parseFloat(r[4]);
                        var change = today - yesterday;             // 计算变化值
                        if (change >= 0.0)
                            model.setProperty(index, "change", "+" + change.toFixed(2));  // 同样对model赋值大于零则带+号，保留两位小数
                        else
                            model.setProperty(index, "change", change.toFixed(2));

                        var changePercentage = (change / yesterday) * 100.0;         // 变化率百分比
                        if (changePercentage >= 0.0)
                            model.setProperty(index, "changePercentage", "+" + changePercentage.toFixed(2) + "%");
                        else
                            model.setProperty(index, "changePercentage", changePercentage.toFixed(2) + "%");
                    }
                }
            }
            xhr.send()              // 发送请求
        }

        onCurrentIndexChanged: {                       // 当该ListView中的某个项目被选中
            mainRect.listViewActive = 0;                         // 切换主ListView的页面
            root.currentStockId = model.get(currentIndex).stockId;       // 获取 Id 与 name
            root.currentStockName = model.get(currentIndex).name;
        }

        delegate: Rectangle {                    // 委托组件，基本都是布局，不多说了
            height: 102
            width: parent.width
            color: "transparent"
            MouseArea {
                anchors.fill: parent;
                onClicked: {
                    view.currentIndex = index;
                }
            }

            Text {
                id: stockIdText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.left: parent.left
                anchors.leftMargin: 15
                width: 125
                height: 40
                color: "#000000"
                font.family: "Open Sans"                // 我的机器貌似不支持这种字体
                font.pointSize: 20
                font.weight: Font.Bold
                verticalAlignment: Text.AlignVCenter
                text: stockId
            }

            Text {
                id: stockValueText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 0.31 * parent.width
                width: 190
                height: 40
                color: "#000000"
                font.family: "Open Sans"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: value
                Component.onCompleted: view.getCloseValue(index);
            }

            Text {
                id: stockValueChangeText
                anchors.top: parent.top
                anchors.topMargin: 15
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 135
                height: 40
                color: "#328930"
                font.family: "Open Sans"
                font.pointSize: 20
                font.bold: true
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: change
                onTextChanged: {
                    if (parseFloat(text) >= 0.0)           // 正为绿色，负为红色
                        color = "#328930";
                    else
                        color = "#d40000";
                }
            }

            Text {
                id: stockNameText
                anchors.top: stockIdText.bottom
                anchors.left: parent.left
                anchors.leftMargin: 15
                width: 330
                height: 30
                color: "#000000"
                font.family: "Open Sans"
                font.pointSize: 16
                font.bold: false
                elide: Text.ElideRight
                maximumLineCount: 1
                verticalAlignment: Text.AlignVCenter
                text: name
            }

            Text {
                id: stockValueChangePercentageText
                anchors.top: stockIdText.bottom
                anchors.right: parent.right
                anchors.rightMargin: 20
                width: 120
                height: 30
                color: "#328930"
                font.family: "Open Sans"
                font.pointSize: 18
                font.bold: false
                horizontalAlignment: Text.AlignRight
                verticalAlignment: Text.AlignVCenter
                text: changePercentage
                onTextChanged: {
                    if (parseFloat(text) >= 0.0)
                        color = "#328930";
                    else
                        color = "#d40000";
                }
            }

            Rectangle {
                id: endingLine
                anchors.bottom: parent.bottom
                anchors.left: parent.left
                height: 1
                width: parent.width
                color: "#d7d7d7"
            }
        }

        highlight: Rectangle {
            width: parent.width
            color: "#eeeeee"
        }
    }
}


