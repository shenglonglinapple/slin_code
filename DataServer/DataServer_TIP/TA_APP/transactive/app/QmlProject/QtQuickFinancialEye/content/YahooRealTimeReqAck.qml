






import QtQuick 2.0
import QuoteTypeValue 1.0

Item
{
    //0
    id: id_qml_YahooRealTimeReqAck

    property int m_n_QuoteTypeValue: QuoteType.ask;


    //获取股票最新行情数据
    /*
    http://finance.yahoo.com/d/quotes.csv?s=AAPL&f=xnsc6p2d1t1pobaghml1t8va2
    */
    /*
responseText:   <HTML>
<HEAD>
<TITLE>Error</TITLE>
</HEAD>

<BODY BGCOLOR="white" FGCOLOR="black">
<!-- status code : 301 -->
<!-- Error: GET -->
<!-- host machine: yts12.global.media.sg3.yahoo.com -->
<!-- timestamp: 1413689649.000 -->
<!-- url: http://finance.yahoo.com/d/quotes.csv?s=AAPL&f=xnsc6p2d1t1pobaghml1t8va2-->
<H1>Error</H1>
<HR>

<FONT FACE="Helvetica,Arial"><B>
Description: Could not process this "GET" request.
</B></FONT>
<HR>
</BODY>
"NasdaqNM""AAPL","+1.41","+1.46%","10/17/2014","4:00pm",96.26,97.50,98.12,98.14,96.81,99.00,"96.81 - 99.00",97.67,112.64,68179688,57839400,,"Apple Inc."
    */
    /*
      error: "Analog Devices, I",  have , so 公司名称放在最后
    */
    function fun_create_request_LatestQuotesCsv(strSymbol, strSymbolExtern)
    {
        var varReturnValue = "";

        varReturnValue = "http://finance.yahoo.com/d/quotes.csv?";
        varReturnValue += "s=" + strSymbol;
        varReturnValue += "&f=xsc6p2d1t1pobaghml1t8va2n";
        // 返回这一长串url

        return varReturnValue;
    }

    /////////////////////////////////////////////////////////////////////////////
    function fun_Process_StringReplace(strSrc, strReplaceSrc, strReplaceWith)
    {
        var varReturnValue = "";
        varReturnValue = strSrc;

        while (-1 != varReturnValue.indexOf(strReplaceSrc))
        {
           varReturnValue = varReturnValue.replace(strReplaceSrc, strReplaceWith);
        }

        return varReturnValue;
    }



    function fun_process_responseText_LatestQuotesCsv(strResponseText)
    {
        var varStrBody = "";
        var strResponseTextTmp = "";

        strResponseTextTmp = strResponseText;

        /*
        console.log("YahooRealTimeReqAck.qml",
                    " ","fun_process_responseText_LatestQuotesCsv:",
                    " ","strResponseTextTmp:",
                    " ",strResponseTextTmp);
        */

        var varHeaderAndBodyLst = strResponseTextTmp.split('</BODY>');
        if (varHeaderAndBodyLst.length >= 2)
        {
            varStrBody = varHeaderAndBodyLst[1];
        }
        else
        {
            console.error("YahooRealTimeReqAck.qml",
                        " ","fun_process_responseText_LatestQuotesCsv error:",
                        " ","strResponseTextTmp:",
                        " ",strResponseTextTmp);
            varStrBody = "";
        }


        //"NasdaqNM","AAPL","+1.41","+1.46%","10/17/2014","4:00pm",96.26,97.50,98.12,98.14,96.81,99.00,"96.81 - 99.00",97.67,112.64,68179688,57839400,"Apple ,Inc."
        var varVariableLst = varStrBody.split(',');


        console.log("YahooRealTimeReqAck.qml",
                      " ", "fun_process_responseText_LatestQuotesCsv",
                      " ", "varVariableLst.length=",varVariableLst.length,
                      " ", "varVariableLst=",varStrBody);

        if (varVariableLst.length < 18)
        {
            console.error("YahooRealTimeReqAck.qml",
                          " ", "fun_process_responseText_LatestQuotesCsv",
                          " ", "varVariableLst.length=",varVariableLst.length,
                          " ", "is < 18");

            varVariableLst = "";
            return varVariableLst;
        }

        if (varVariableLst.length > 18)
        {
            //"Apple ,Inc." have ,
            //""Apple "
            //Inc."

            //varVariableLst[17] = varVariableLst[17] +","+ varVariableLst[18];
            varVariableLst[17] = varVariableLst[17] +". Inc";
        }

        for (var nIndex = 0; nIndex < varVariableLst.length; nIndex++)
        {
            varVariableLst[nIndex] = id_qml_YahooRealTimeReqAck.fun_Process_StringReplace(varVariableLst[nIndex], '"', '');
            varVariableLst[nIndex] = varVariableLst[nIndex].trim();
        }//for

        return varVariableLst;
    }//fun_process_responseText_LatestQuotesCsv


}//Rectangle


//doc--begin
//fun_create_request_LatestQuotesCsv
/*
http://finance.yahoo.com/d/quotes.csv?s=AAPL&f=xnsc6p2d1t1pobaghml1t8va2
"NasdaqNM","Apple Inc.","AAPL","+1.41","+1.46%","10/17/2014","4:00pm",96.26,97.50,98.12,98.14,96.81,99.00,"96.81 - 99.00",97.67,112.64,68179688,57839400
Symbol Info
x: Stock Exchange
n: Name
s: Symbol
xns


Date
c6: Change (Realtime)
p2: Change in Percent
d1: Last Trade Date
t1: Last Trade Time
c6p2d1t1



Pricing
p: Previous Close  96.26,
o: Open            97.50,
b: Bid             98.12 x 100,
a: Ask             98.14 x 3000
poba



Averages
g: Day’s Low
h: Day’s High
m: Day’s Range
l1: Last Trade (Price Only)
t8: 1 yr Target Price
ghml1t8

Volume
v: Volume
a2: Average Daily Volume
va2
*/
//fun_create_request_LatestQuotesCsv

//total
/*
 http://www.jarloo.com/yahoo_finance/
quoteTypes:

Pricing
a: Ask
b: Bid
b2: Ask (Realtime)
b3: Bid (Realtime)
p: Previous Close
o: Open

Date
c1: Change
c: Change & Percent Change
c6: Change (Realtime)
k2: Change Percent (Realtime)
p2: Change in Percent
d1: Last Trade Date
d2: Trade Date
t1: Last Trade Time


Dividends
y: Dividend Yield
d: Dividend per Share
r1: Dividend Pay Date
q: Ex-Dividend Date

Dividends
d1: Last Trade Date
d2: Trade Date
t1: Last Trade Time


Averages
c8: After Hours Change (Realtime)
c3: Commission
g: Day’s Low
h: Day’s High
k1: Last Trade (Realtime) With Time
l: Last Trade (With Time)
l1: Last Trade (Price Only)
t8: 1 yr Target Price
m5: Change From 200 Day Moving Average
m6: Percent Change From 200 Day Moving Average
m7: Change From 50 Day Moving Average
m8: Percent Change From 50 Day Moving Average
m3: 50 Day Moving Average
m4: 200 Day Moving Average



Misc
w1: Day’s Value Change
w4: Day’s Value Change (Realtime)
p1: Price Paid
m:  Day’s Range
m2: Day’s Range (Realtime)
g1: Holdings Gain Percent
g3: Annualized Gain
g4: Holdings Gain
g5: Holdings Gain Percent (Realtime)
g6: Holdings Gain (Realtime)



52 Week Pricing
k: 52 Week High
j: 52 week Low
j5: Change From 52 Week Low
k4: Change From 52 week High
j6: Percent Change From 52 week Low
k5: Percent Change From 52 week High
w: 52 week Range

Symbol Info
v: More Info
j1: Market Capitalization
j3: Market Cap (Realtime)
f6: Float Shares
n: Name
n4: Notes
s: Symbol
s1: Shares Owned
x: Stock Exchange
j2: Shares Outstanding

Volume
v: Volume
a5: Ask Size
b6: Bid Size
k3: Last Trade Size
a2: Average Daily Volume


Misc
t7: Ticker Trend
t6: Trade Links
i5: Order Book (Realtime)
l2: High Limit
l3: Low Limit
v1: Holdings Value
v7: Holdings Value (Realtime)
s6 Revenue

Ratios
e: Earnings per Share
e7: EPS Estimate Current Year
e8: EPS Estimate Next Year
e9: EPS Estimate Next Quarter
b4: Book Value
j4: EBITDA
p5: Price / Sales
p6: Price / Book
r: P/E Ratio
r2: P/E Ratio (Realtime)
r5: PEG Ratio
r6: Price / EPS Estimate Current Year
r7: Price / EPS Estimate Next Year
s7: Short Ratio
*/
//total


//doc--end






