import QtQuick 2.0
import QuoteTypeValue 1.0

Item
{
    //0
    id: id_qml_YahooHistoryReqAck

    //获取股票历史行情数据
    //var startDate = new Date(2011, 4, 25);//指定一个开始时间
    function fun_create_request_HistoricalQuotesCsv(strInstrument,  dateStart, dateEnd, strRangeType)
    {
        var varReturnValue = "";

        varReturnValue = "http://ichart.finance.yahoo.com/table.csv?";
        varReturnValue += "s=" + strInstrument;
        varReturnValue += "&a=" + dateStart.getMonth();
        varReturnValue += "&b=" + dateStart.getDate();
        varReturnValue += "&c=" + dateStart.getFullYear();
        varReturnValue += "&d=" + dateEnd.getMonth();
        varReturnValue += "&e=" + dateEnd.getDate();
        varReturnValue += "&f=" + dateEnd.getFullYear();
        varReturnValue += "&g=" + strRangeType;//stockDataCycle;//d w m v
        varReturnValue += "&ignore=.csv";

        return varReturnValue;
    }

    function fun_create_request_Sample()
    {// 创建请求数据的url字符串函数
        var strSymbol = "APPL";
        var startDate = new Date(2011, 4, 25);      // 指定一个开始时间
        var endDate = new Date();                   // 结束时间为当前时间
        var stockDataCycle = "v";

        if (stockDataCycle !== "d" && stockDataCycle !== "w" && stockDataCycle !== "m")
        {
            // 如果数据周期不是'天'、'周'、'月'，则定义为'天'
            stockDataCycle = "d";
        }

        id_qml_YahooHistoryReqAck.fun_create_request_HistoricalQuotesCsv(strSymbol, startDate, endDate, stockDataCycle);
    }

}//Rectangle


//doc--begin



/*
//注释给出了向yahoo请求数据的格式
Fetch stock data from yahoo finance:
url: http://ichart.finance.yahoo.com/table.csv?s=NOK&a=5&b=11&c=2010&d=7&e=23&f=2010&g=d&ignore=.csv
s:stock name/id,
a:start day, b:start month, c:start year  default: 25 April 1995, oldest c= 1962
d:end day, e:end month, f:end year, default:today  (data only available 3 days before today)
g:data cycle(d daily,  w weekly, m monthly, v Dividend)
*/
/*
Date,Open,High,Low,Close,Volume,Adj Close
2010-08-23,9.00,9.08,8.91,8.91,13309700,7.29
2010-08-20,9.07,9.16,9.04,9.09,15380200,7.44
*/

//doc--end






