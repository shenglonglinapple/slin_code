/*
      http://blog.csdn.net/ablo_zhou/article/details/4283320
      http://www.lidaren.com/archives/741
从网上搜索到的Yahoo财经API接口，基本可以取到世界各个市场的股票，指数，外汇等数据
但是测试下来好像日本国内数据没有，不过调查之后发现可以使用其他方式获取，获取的方法会在随后的博文再附上。

1.获取实时数据
http://finance.yahoo.com/d/quotes.csv?s=股票名称&f=数据列选项
s — 表示股票名称，多个股票之间使用英文加号分隔，如“XOM+BBDb.TO+JNJ+MSFT”，罗列了四个公司的股票：XOM, BBDb.TO, JNJ, MSFT。
f — 表示返回数据列，如“snd1l1yr”。


2.历史数据请求
http://ichart.yahoo.com/table.csv?s=string&a=int&b=int&c=int&d=int&e=int&f=int&g=d&ignore=.csv
s — 股票名称
a — 起始时间，月
b — 起始时间，日
c — 起始时间，年
d — 结束时间，月
e — 结束时间，日
f — 结束时间，年
g — 时间周期。
参数g的取值范围：d->‘日’(day), w->‘周’(week)，m->‘月’(mouth)，v->‘dividends only’
月份是从0开始的，如9月数据，则写为08。

参考网址：
http://blog.sina.com.cn/s/blog_71302a17010100on.html
http://www.gummy-stuff.org/Yahoo-data.htm

http://hi.baidu.com/arjsyy/blog/item/3057167ab50157d50ad1878a.html
*/
/*
利用雅虎查中国股票
http://quote.yahoo.com/d/quotes.csv?s=MSFT&f=slc1wop
返回微软的股票价格
"MSFT","Oct 16 - <b>42.74</b>",-0.48,"33.57 - 47.57",42.59,43.22

http://quote.yahoo.com/d/quotes.csv?s=000969.SZ&f=slc1wop
这个返回安泰科技的，一般有半个小时的延迟。
但是s=000969.sz 这个后面的sz是深圳的意思, 沪市是SS后缀
*/


import QtQuick 2.0

Item
{
    //0
    id: id_qml_DataRequest
    //1
    property string m_str_Instruments: ""// 股票ID
    property string m_str_QuoteTypes: ""// 股票数据类型





    //获取股票最新行情数据
    function fun_create_quest_for_LatestQuotesCsv()
    {
        var varReturnValue = "";

        //check
        if (m_str_Instruments.length <= 0)
        {
            console.error('DataRequest.qml',
                        ' ','fun_create_quest_for_LatestQuotesCsv',
                        ' ','m_str_Instruments is empty');
             return varReturnValue;
        }

        if (m_str_QuoteTypes.length <= 0)
        {
            console.error('DataRequest.qml',
                        ' ','fun_create_quest_for_LatestQuotesCsv',
                        ' ','m_str_QuoteTypes is empty');
             return varReturnValue;
        }

        varReturnValue = "http://finance.yahoo.com/d/quotes.csv?";
        varReturnValue += "s=" + id_qml_DataRequest.m_str_Instruments;
        varReturnValue += "&f=" + id_qml_DataRequest.m_str_QuoteTypes;
        // 返回这一长串url

        return varReturnValue;
    }


    function fun_getLatestQuotesCsv()
    {
        var varReturnValue = "";

        var varRequest = "";
        varRequest = fun_create_quest_for_LatestQuotesCsv();
        if (!varRequest)
        {
            return;
        }

        return varReturnValue;
    }
}//Rectangle
