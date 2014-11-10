import QtQuick 2.0
import QuoteTypeValue 1.0

Item
{
    //0
    id: id_qml_YahooHistoryReqAck

    //获取股票历史行情数据
    //var startDate = new Date(2011, 4, 25);//指定一个开始时间
    function fun_create_request_HistoricalQuotesCsv(strSymbol, strSymbolExtern,  dateStart, dateEnd, strRangeType)
    {
        var varReturnValue = "";

        varReturnValue = "http://ichart.finance.yahoo.com/table.csv?";
        varReturnValue += "s=" + strSymbol;
        varReturnValue += "&a=" + dateStart.getMonth();
        varReturnValue += "&b=" + dateStart.getDate();
        varReturnValue += "&c=" + dateStart.getFullYear();
        varReturnValue += "&d=" + dateEnd.getMonth();
        varReturnValue += "&e=" + dateEnd.getDate();
        varReturnValue += "&f=" + dateEnd.getFullYear();
        varReturnValue += "&g=" + strRangeType;//stockDataCycle;//d w m v
        varReturnValue += "&ignore=.csv";

        return varReturnValue;
    }//fun_create_request_HistoricalQuotesCsv


    function fun_create_request_Sample()
    {// 创建请求数据的url字符串函数
        var varReturnValue = "";
        var strSymbol = "APPL";
        var m_s_Symbol_Extern_Tmp = "";
        var startDate = new Date(2011, 4, 25);      // 指定一个开始时间
        var endDate = new Date();// today   // 结束时间为当前时间
        var stockDataCycle = "v";

        if (stockDataCycle !== "d" && stockDataCycle !== "w" && stockDataCycle !== "m")
        {
            // 如果数据周期不是'天'、'周'、'月'，则定义为'天'
            stockDataCycle = "d";
        }

        varReturnValue = id_qml_YahooHistoryReqAck.fun_create_request_HistoricalQuotesCsv(strSymbol, m_s_Symbol_Extern_Tmp, startDate, endDate, stockDataCycle);
        return varReturnValue;
    }//fun_create_request_Sample




    //1d 5d
    function fun_create_request_x_day(strSymbol,strSymbolExtern, nDays, stockDataCycle)
    {// 创建请求数据的url字符串函数
        var varReturnValue = "";
        var endDate = new Date();// today
        var startDate = new Date(); //结束时间为当前时间
        //var stockDataCycle = "d";
        var nDiff = nDays;

        startDate.setDate(startDate.getDate() - nDiff);// 最近5天

        varReturnValue = id_qml_YahooHistoryReqAck.fun_create_request_HistoricalQuotesCsv(
                    strSymbol,strSymbolExtern, startDate, endDate, stockDataCycle);

        return varReturnValue;
    }//fun_create_request_x_day



    //1m 3m 6m
    function fun_create_request_x_month(strSymbol,strSymbolExtern, nMonths, stockDataCycle)
    {// 创建请求数据的url字符串函数
        var varReturnValue = "";
        var endDate = new Date();// today
        var startDate = new Date();// today //结束时间为当前时间
        //var stockDataCycle = "m";
        var nDiff = nMonths;

        startDate.setMonth(startDate.getMonth() - nMonths);

        varReturnValue = id_qml_YahooHistoryReqAck.fun_create_request_HistoricalQuotesCsv(strSymbol,strSymbolExtern, startDate, endDate, stockDataCycle);
        return varReturnValue;
    }//fun_create_request_x_month




    //1y 2y  3y
    function fun_create_request_x_year(strSymbol,strSymbolExtern, nYears,stockDataCycle)
    {// 创建请求数据的url字符串函数
        var varReturnValue = "";
        var endDate = new Date();// today
        var startDate = new Date();// today //结束时间为当前时间
        //var stockDataCycle = "y";
        var nDiff = nYears;

        startDate.setFullYear(startDate.getFullYear() - nDiff);

        varReturnValue = id_qml_YahooHistoryReqAck.fun_create_request_HistoricalQuotesCsv(strSymbol,strSymbolExtern, startDate, endDate, stockDataCycle);
        return varReturnValue;
    }//fun_create_request_x_year





    function fun_process_responseText_Historical_HeaderBody(strResponseText)
    {
        /*
        Date,Open,High,Low,Close,Volume,Adj Close
        2010-08-23,9.00,9.08,8.91,8.91,13309700,7.29
        2010-08-20,9.07,9.16,9.04,9.09,15380200,7.44
        */

        var varHeaderAndBodyLst = strResponseText.split('\n');

        /*
        console.log("YahooHistoryReqAck.qml",
                      " ", "fun_process_responseText_Historical_HeaderBody",
                      " ", "varHeaderAndBodyLst.length=",varHeaderAndBodyLst.length,
                      " ", "varHeaderAndBodyLst=",varHeaderAndBodyLst);
        */

        return varHeaderAndBodyLst;
    }//fun_process_responseText_LatestQuotesCsv



    function fun_process_responseText_Historical_BodyLine(strResponseLine)
    {
        /*
        Date,Open,High,Low,Close,Volume,Adj Close
        2010-08-23,9.00,9.08,8.91,8.91,13309700,7.29
        2010-08-20,9.07,9.16,9.04,9.09,15380200,7.44
        */

        var varHeaderAndBodyLst = strResponseLine.split(',');

        /*
        console.log("YahooHistoryReqAck.qml",
                      " ", "fun_process_responseText_Historical_BodyLine",
                      " ", "varHeaderAndBodyLst.length=",varHeaderAndBodyLst.length,
                      " ", "varHeaderAndBodyLst=",varHeaderAndBodyLst);
        */

        return varHeaderAndBodyLst;
    }//fun_process_responseText_LatestQuotesCsv

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
/*
var today = parseFloat(r[4]);// parseFloat()将字符串转化成浮点数，变量声明为var而不是real
change.toFixed(2));  // 同样对model赋值大于零则带+号，保留两位小数
*/

//doc--end






