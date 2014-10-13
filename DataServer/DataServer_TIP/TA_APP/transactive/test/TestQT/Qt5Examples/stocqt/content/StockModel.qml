import QtQuick 2.0

ListModel {                                  // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    id: model
    property string stockId: ""              // 股票ID
    property string stockName: ""            // 股票名
    property string stockDataCycle: "d"      // 数据周期
    property bool ready: false               // 标志位
    property real stockPrice: 0.0           // 股票价格
    property real stockPriceChanged: 0.0    // 价格变化

    signal dataReady                      // 耗时的数据类通常需要定义这个信号

    function indexOf(date) {                               // 返回从特定date的数据在数据集中的位置
        var newest = new Date(model.get(0).date);               // 获取第一个数据对象的日期
        var oldest = new Date(model.get(model.count - 1).date); // 最后一个数据对象的日期
        if (newest <= date)
            return -1;                                // 在最新日期之后直接返回

        if (oldest >= date)
            return model.count - 1;                  // 在最先日期之前全部返回

        var currDiff = 0;
        var bestDiff = Math.abs(date.getTime() - newest.getTime());
        var retval = 0;                                            // 返回变量
        for (var i = 0; i < model.count; i++) {
            var d = new Date(model.get(i).date);
            currDiff = Math.abs(d.getTime() - date.getTime());    // 计算时间差值
            if (currDiff < bestDiff) {                         // 从最新时间向目标时间推进
                bestDiff = currDiff;
                retval = i;                                   // retval记录数据位置
            }
            if (currDiff > bestDiff)                       // 当达到目标时间后
                return retval;                             // 将数据位置返回
        }

        return -1;
    }

    function requestUrl() {                        // 创建请求数据的url字符串函数
        if (stockId === "")
            return;

        var startDate = new Date(2011, 4, 25);      // 指定一个开始时间

        var endDate = new Date();                   // 结束时间为当前时间

        if (stockDataCycle !== "d" && stockDataCycle !== "w" && stockDataCycle !== "m")
            stockDataCycle = "d";                  // 如果数据周期不是'天'、'周'、'月'，则定义为'天'

        /*                                          // 注释给出了向yahoo请求数据的格式
            Fetch stock data from yahoo finance:
             url: http://ichart.finance.yahoo.com/table.csv?s=NOK&a=5&b=11&c=2010&d=7&e=23&f=2010&g=d&ignore=.csv
                s:stock name/id, a:start day, b:start month, c:start year  default: 25 April 1995, oldest c= 1962
                d:end day, e:end month, f:end year, default:today  (data only available 3 days before today)
                g:data cycle(d daily,  w weekly, m monthly, v Dividend)
          */
        var request = "http://ichart.finance.yahoo.com/table.csv?";
        request += "s=" + stockId;
        request += "&a=" + startDate.getMonth();
        request += "&b=" + startDate.getDate();
        request += "&c=" + startDate.getFullYear();
        request += "&d=" + endDate.getMonth();
        request += "&e=" + endDate.getDate();
        request += "&f=" + endDate.getFullYear();
        request += "&g=" + stockDataCycle;
        request += "&ignore=.csv";
        return request;                             // 返回这一长串url
    }

    function createStockPrice(r) {               // 存储数据对象函数
        return {                                 // 用来接收下面分离的7位数据，以类似结构体的形式存储下来
                "date": r[0],                    // 这也是该model真正存储的数据类型格式
                "open":r[1],
                "high":r[2],
                "low":r[3],
                "close":r[4],
                "volume":r[5],
                "adjusted":r[6]
               };
    }

    function updateStock() {               // 数据更新
        var req = requestUrl();             // 得到请求数据的url字符串

        if (!req)
            return;

        var xhr = new XMLHttpRequest;      // 创建一个XMLHttp的请求对象

        xhr.open("GET", req, true);        // 初始化请求参数，还未发送请求

        model.ready = false;               // 标志位置false
        model.clear();                     // 数据清空
        var i = 1;                          // 输出一下调试信息可知，返回的数据第一行为描述符，因此将其跳过
        xhr.onreadystatechange = function() {  // readyState是XMLHttpRequest的一个属性，其值从0变化到4
            if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE) {
                var records = xhr.responseText.split('\n');        // LOADING为3，DONE为4，分别表示数据正在载入和载入完成
                                                                   // 以换行符分割数据
                for (;i < records.length; i++ ) {
                    var r = records[i].split(',');                 // 以逗号将数据分割
                    if (r.length === 7)                            // 数据校验
                        model.append(createStockPrice(r));         // 函数调用，向model中添加数据
                }

                if (xhr.readyState === XMLHttpRequest.DONE) {
                    if (model.count > 0) {
                        model.ready = true;
                        model.stockPrice = model.get(0).adjusted;  // 将最新的的调整收盘价赋予stockPrice
                        model.stockPriceChanged = model.count > 1 ? (Math.round((model.stockPrice - model.get(1).close) * 100) / 100) : 0;                                                                                   // 相比前一天的收盘价变化率
                        model.dataReady();                         //emit signal
                    }
                }
            }
        }
        xhr.send()                                         // 实际发出数据请求
    }
}


