import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    //big first
    id: id_qml_StockModel

    /* 
    ListElement
    {
        date:"2014-10-14 20:00:00";
        open:"20.00";
        high:"20.00";
        low:"20.00";
        close:"20.00";
        volume:"50";
        adjusted:"20.00";
    }
    ListElement
    {
        date:"2013-10-14 20:00:00";
        open:"20.00";
        high:"20.00";
        low:"20.00";
        close:"20.00";
        volume:"50";
        adjusted:"20.00";
    }
    //adjusted 最新的的调整收盘价
    */


    //
    property string stockId: ""              // 股票ID
    property string stockName: ""            // 股票名
    property string stockDataCycle: "d"      // 数据周期
    property bool ready: false               // 标志位
    property real stockPrice: 0.0           // 股票价格
    property real stockPriceChanged: 0.0    // 价格变化
    //
    signal signalDataReady                      // 耗时的数据类通常需要定义这个信号

    function indexOf(startdateTmp)
    {// 返回从特定date的数据在数据集中的位置

        //获取第一个数据对象的日期
        var newest = new Date(id_qml_StockModel.get(0).date);//2014-10-15
        //最后一个数据对象的日期
        var oldest = new Date(id_qml_StockModel.get(id_qml_StockModel.count - 1).date);//2013-10-15
        /*qml: StockModel.qml   indexOf(startdateTmp)   startdateTmp: Tue Oct 15 2013   newest: Tue Oct 14 2014   oldest: Wed May 25 2011   id_qml_StockModel.count: 1706*/
        console.log('StockModel.qml',' ','indexOf(startdateTmp)',
                    ' ','startdateTmp:',startdateTmp.toDateString(),
                    ' ','newest:',newest.toDateString(),
                    ' ','oldest:',oldest.toDateString(),
                    ' ','id_qml_StockModel.count:',id_qml_StockModel.count);

        if (newest <= startdateTmp)
        {
            //在最新日期之后直接返回
            return -1;
        }

        if (oldest >= startdateTmp)
        {
            //在最先日期之前全部返回
            return id_qml_StockModel.count - 1;
        }

        var currDiff = 0;
        var bestDiff = Math.abs(startdateTmp.getTime() - newest.getTime());
        // 返回变量
        var retval = 0;

        for (var i = 0; i < id_qml_StockModel.count; i++)
        {
            var d = new Date(id_qml_StockModel.get(i).date);
            currDiff = Math.abs(d.getTime() - startdateTmp.getTime());    // 计算时间差值
            if (currDiff < bestDiff)
            {// 从最新时间向目标时间推进
                bestDiff = currDiff;
                retval = i;// retval记录数据位置
            }
            if (currDiff > bestDiff)// 当达到目标时间后
            {
                return retval;// 将数据位置返回
            }
        }

        return -1;
    }

    function requestUrl()
    {// 创建请求数据的url字符串函数
        if (stockId === "")
        {
            return;
        }

        var startDate = new Date(2011, 4, 25);      // 指定一个开始时间

        var endDate = new Date();                   // 结束时间为当前时间

        if (stockDataCycle !== "d" && stockDataCycle !== "w" && stockDataCycle !== "m")
        {

            stockDataCycle = "d";                  // 如果数据周期不是'天'、'周'、'月'，则定义为'天'
        }

        // 注释给出了向yahoo请求数据的格式
        /*
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

    function createStockPrice(recordTmp)
    {// 存储数据对象函数
        // 用来接收下面分离的7位数据，以类似结构体的形式存储下来
        // 这也是该model真正存储的数据类型格式
        //Date,Open,High,Low,Close,Volume,Adj Close
        //2014-10-13,101.33,101.78,99.81,99.81,53485500,99.81
        return {
            "date": recordTmp[0],
            "open":recordTmp[1],
            "high":recordTmp[2],
            "low":recordTmp[3],
            "close":recordTmp[4],
            "volume":recordTmp[5],
            "adjusted":recordTmp[6]
        };
    }

    function updateStock()
    {//when stockId changed 数据更新

        // 得到请求数据的url字符串
        var req = requestUrl();
        //http://ichart.finance.yahoo.com/table.csv?s=AAPL&a=4&b=25&c=2011&d=9&e=14&f=2014&g=d&ignore=.csv

        if (!req)
        {
            return;
        }

        console.log('StockModel.qml updateStock XMLHttpRequest');
        // 创建一个XMLHttp的请求对象
        var xhr = new XMLHttpRequest();

         // 初始化请求参数，还未发送请求
        xhr.open("GET", req, true);

        //标志位置false
        id_qml_StockModel.ready = false;
        // 数据清空
        id_qml_StockModel.clear();

        // 输出一下调试信息可知，返回的数据第一行为描述符，因此将其跳过
        var nIndex = 1;
        xhr.onreadystatechange = function()
        {  // readyState是XMLHttpRequest的一个属性，其值从0变化到4
            if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE)
            {
                // LOADING为3，DONE为4，分别表示数据正在载入和载入完成
                var records = xhr.responseText.split('\n');
                //0:Date,Open,High,Low,Close,Volume,Adj Close
                //1:2014-10-13,101.33,101.78,99.81,99.81,53485500,99.81
                //...
                //n:2011-05-25,333.43,338.56,332.85,336.78,73556000,45.76

                // 以换行符分割数据
                for (nIndex = 1;nIndex < records.length; nIndex++ )
                {
                    // 以逗号将数据分割
                    var recodeTmp = records[nIndex].split(',');
                    // 数据校验
                    if (recodeTmp.length === 7)
                    {
                        // 函数调用，向model中添加数据
                        id_qml_StockModel.append(createStockPrice(recodeTmp));
                    }
                }

                if (xhr.readyState === XMLHttpRequest.DONE)
                {
                    var stockPriceChangedTmp = 0.0;

                    if (id_qml_StockModel.count > 0)
                    {
                        id_qml_StockModel.ready = true;
                        id_qml_StockModel.stockPrice = id_qml_StockModel.get(0).adjusted;  // 将最新的的调整收盘价赋予stockPrice

                        stockPriceChangedTmp = 0.0;
                        stockPriceChangedTmp = id_qml_StockModel.count > 1 ? (Math.round((id_qml_StockModel.stockPrice - id_qml_StockModel.get(1).close) * 100) / 100) : 0;
                        // 相比前一天的收盘价变化率
                        id_qml_StockModel.stockPriceChanged = stockPriceChangedTmp;
                        //id_qml_StockModel.stockPriceChanged = id_qml_StockModel.count > 1 ? (Math.round((id_qml_StockModel.stockPrice - id_qml_StockModel.get(1).close) * 100) / 100) : 0;

                        console.log('StockListModel.qml',
                                    ' ','emit signalDataReady()');
                        id_qml_StockModel.signalDataReady();//emit signal
                    }//if
                }//if
            }//if
        }//function
        xhr.send();// 实际发出数据请求
    }
}//ListModel


