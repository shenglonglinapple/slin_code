import QtQuick 2.0

//work with StockListDelegate.qml StockListModel.qml
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
        {// 当该ListView中的某个项目被选中

            console.log('StockListView.qml', ' ', 'onCurrentIndexChanged',
                        ' ','currentIndex:',m_listViewStock.currentIndex);

            // 切换主ListView的页面
            //使用了属性绑定，当listViewActive set value 0时，使currentIndex置1，从而跳转到曲线页面
            console.log('StockListView.qml', ' ', 'onCurrentIndexChanged',
                        ' ','update',' ',
                        ' ','id_qml_stocqt.listViewActive:',id_qml_stocqt.listViewActive);
            id_qml_stocqt.listViewActive = 0;//使用了属性绑定

            // 获取 Id 与 name
            //set value and emit
            id_qml_StockListView.currentStockId = model.get(m_listViewStock.currentIndex).stockId;
            console.log('StockListView.qml', ' ', 'onCurrentIndexChanged',
                        ' ','update',' ','currentStockId',
                        ' ','currentStockId:',id_qml_StockListView.currentStockId,
                        ' ','currentStockName:',id_qml_StockListView.currentStockName);

            id_qml_StockListView.currentStockName = model.get(m_listViewStock.currentIndex).name;
            console.log('StockListView.qml', ' ', 'onCurrentIndexChanged',
                        ' ','update',' ','currentStockName',
                        ' ','currentStockId:',id_qml_StockListView.currentStockId,
                        ' ','currentStockName:',id_qml_StockListView.currentStockName);
        }//onCurrentIndexChanged



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
            {
                return;
            }
            console.log('StockListView.qml getCloseValue() XMLHttpRequest',
                        ' ','index:',index,
                        ' ','stockId:',model.get(index).stockId);
            var xhr = new XMLHttpRequest();

            xhr.open("GET", req, true);

            xhr.onreadystatechange = function()
            {
                if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE)
                {
                    //console.log('xhr.responseText:',xhr.responseText);
                    /*
qml: xhr.responseText: Date,Open,High,Low,Close,Volume,Adj Close
2014-10-14,43.93,44.66,43.38,43.46,4012100,43.46
2014-10-13,43.43,44.38,42.86,43.10,4187800,43.10
2014-10-10,44.30,44.47,42.57,43.45,10052700,43.45
                    */


                    var records = xhr.responseText.split('\n');
                    //console.log('records:',records);
                    //console.log('records.length:',records.length);
                    /*
qml: records: [Date,Open,High,Low,Close,Volume,Adj Close,2014-10-14,43.93,44.66,43.38,43.46,4012100,43.46,2014-10-13,43.43,44.38,42.86,43.10,4187800,43.10,2014-10-10,44.30,44.47,42.57,43.45,10052700,43.45,]
records.length: 5
                    */



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
            }//function
            xhr.send()              // 发送请求
        }//function getCloseValue


    }//ListView
}


