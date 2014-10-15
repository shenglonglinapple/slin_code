import QtQuick 2.0

Rectangle
{
    id: id_qml_StockListView
    width: 320
    height: 410
    anchors.top: parent.top
    anchors.bottom: parent.bottom
    color: "white"

    property string currentStockId: ""
    property string currentStockName: ""




    //mvc
    StockListModel
    {
        id: m_listModel;
    }

    StockListDelegate
    {
        id: m_listDelegate;
    }

    //Component for ListView
    Component
    {
        id: m_highlight
        Rectangle
        {
            width: parent.width
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        id: m_listViewStock
        anchors.fill: parent
        width: parent.width
        clip: true                            // clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: m_listModel;                 // 定义model
        delegate: m_listDelegate;
        highlight: m_highlight


        onCurrentIndexChanged:
        {                       // 当该ListView中的某个项目被选中
            id_qml_stocqt.listViewActive = 0;                         // 切换主ListView的页面
            id_qml_StockListView.currentStockId = model.get(currentIndex).stockId;       // 获取 Id 与 name
            id_qml_StockListView.currentStockName = model.get(currentIndex).name;
        }



        function requestUrl(stockId)
        {
            // 最近5天的url创建函数，与StockModel不同的是，由于未定义stockId属性，它带有这样一个参数
            var endDate = new Date("");            // today
            var startDate = new Date()
            startDate.setDate(startDate.getDate() - 5);// 最近5天

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

        function getCloseValue(index)
        {
            var req = requestUrl(model.get(index).stockId);   // 得到对应的股票Id

            if (!req)
                return;

            var xhr = new XMLHttpRequest;

            xhr.open("GET", req, true);

            xhr.onreadystatechange = function()
            {
                if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE)
                {
                    var records = xhr.responseText.split('\n');
                    if (records.length > 0)
                    {
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


    }//ListView
}


