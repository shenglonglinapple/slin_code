import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    //big first
    id:id_qml_CurrentUserStockData;


    //
    /*
    ListElement
    {
            "m_str_date": recordTmp[0],
            "m_str_open":recordTmp[1],
            "m_str_high":recordTmp[2],
            "m_str_low":recordTmp[3],
            "m_str_close":recordTmp[4],
            "m_str_volume":recordTmp[5],
            "m_str_adjusted":recordTmp[6]
    }
    */
    /*
    Date,Open,High,Low,Close,Volume,Adj Close
    2010-08-23,9.00,9.08,8.91,8.91,13309700,7.29  lastdate first
    2010-08-20,9.07,9.16,9.04,9.09,15380200,7.44
    */

    //
    property string m_n_Name_current:"";//股票名
    property string m_x_Stock_Exchange_current:"";//交易所
    property string m_s_Symbol_current: "";//股票ID
    property real   m_c6_Change_Realtime_current: 0.0;//
    property string m_p2_Change_in_Percent_current: "";//
    property string m_d1_Last_Trade_Date_current: "";//
    property string m_ti_Last_Trade_Time_current: "";//
    property string m_p_Previous_Close_current: "";//
    property string m_o_Open_current: "";//
    property string m_b_Bid_current: "";//
    property string m_a_Ask_current: "";//
    property string m_g_Day_Low_current: "";//
    property string m_h_Day_High_current: "";//
    property string m_m_Day_Range_current: "";//
    property string m_l1_Last_Trade_Price_Only_current: "";//
    property string m_t8_1year_Target_Price_current: "";//
    property string m_v_Volume_current: "";//
    property string m_a2_Average_Daily_Volume_current: "";//
    //
    property string m_str_HistoryDataCycle: "m";//数据周期  d m y
    property real m_n_HistoryDataTimeCount: 1;//总时间长度为30天， bar类型d
    property string m_str_HistoryDataTimeCount: "1m";//数据周期  d m y
    property bool m_bool_HistoryDataReady: false;//标志位
    //
    signal signalHistoryDataReady//耗时的数据类通常需要定义这个信号






    //fun
    function fun_Update_RealTimeInfo_Current()
    {
        var varReturnValue = false;
        var symbolTmp = "";
        var varRealTimeInfo = "";
        var varRequest = "";

        symbolTmp = m_s_Symbol_current;
        //check
        if (symbolTmp.length <= 0)
        {
            console.error('CurrentUserStockData.qml',
                        ' ','fun_Update_RealTimeInfo_Current',
                        ' ','m_s_Symbol_current is empty');
            varReturnValue = false;
            return varReturnValue;
        }

        varRequest = m_YahooRealTimeReqAck.fun_create_request_LatestQuotesCsv(symbolTmp);
        if (varRequest.length <= 0)
        {
            varReturnValue = false;
            return varReturnValue;
        }
        console.log("CurrentUserStockData.qml",
                    " ","fun_Update_RealTimeInfo_Current:",
                    " ","XMLHttpRequest:",
                    " ",varRequest);

        //初始化请求参数，还未发送请求
        var xhr = new XMLHttpRequest();
        xhr.open("GET", varRequest, true);

        xhr.onreadystatechange = function()
        {
            console.log("CurrentUserStockData.qml",
                        " ","fun_Update_RealTimeInfo_Current:",
                        " ","xhr.readyState:",
                        " ",xhr.readyState);

            if (xhr.readyState === XMLHttpRequest.DONE)
            {
                /*
                console.log("CurrentUserStockData.qml",
                            " ","fun_Update_RealTimeInfo_Current:",
                            " ","xhr.responseText:",
                            " ",xhr.responseText);
                */


                var varVariableLst = m_YahooRealTimeReqAck.fun_process_responseText_LatestQuotesCsv(xhr.responseText);

                /*
                console.log("CurrentUserStockData.qml",
                            " ","fun_Update_RealTimeInfo_Current:",
                            " ","varVariableLst.length:",
                            " ",varVariableLst.length,
                            " ","varVariableLst:", varVariableLst);
                */

                /*
            "m_x_Stock_Exchange": varVariableLst[0],
            "m_s_Symbol":varVariableLst[1],
            "m_c6_Change_Realtime":varVariableLst[2],
            "m_p2_Change_in_Percent":varVariableLst[3],
            "m_d1_Last_Trade_Date":varVariableLst[4],
            "m_ti_Last_Trade_Time":varVariableLst[5],
            "m_p_Previous_Close":varVariableLst[6],
            "m_o_Open":varVariableLst[7],
            "m_b_Bid":varVariableLst[8],
            "m_a_Ask":varVariableLst[9],
            "m_g_Day_Low":varVariableLst[10],
            "m_h_Day_High":varVariableLst[11],
            "m_m_Day_Range":varVariableLst[12],
            "m_l1_Last_Trade_Price_Only":varVariableLst[13],
            "m_t8_1year_Target_Price":varVariableLst[14],
            "m_v_Volume":varVariableLst[15],
            "m_a2_Average_Daily_Volume":varVariableLst[16]
            "m_n_Name":varVariableLst[17],
                */

                //check data
                if (varVariableLst.length >= 18)
                {
                    var nIndex = 0;
                    id_qml_CurrentUserStockData.m_x_Stock_Exchange_current = varVariableLst[nIndex];
                    nIndex++;
                    nIndex++;
                    id_qml_CurrentUserStockData.m_c6_Change_Realtime_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_p2_Change_in_Percent_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_d1_Last_Trade_Date_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_ti_Last_Trade_Time_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_p_Previous_Close_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_o_Open_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_b_Bid_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_a_Ask_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_g_Day_Low_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_h_Day_High_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_m_Day_Range_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_l1_Last_Trade_Price_Only_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_t8_1year_Target_Price_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_v_Volume_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_a2_Average_Daily_Volume_current = varVariableLst[nIndex];
                    nIndex++;
                    id_qml_CurrentUserStockData.m_n_Name_current = varVariableLst[nIndex];

                }
                else
                {
                    console.log("CurrentUserStockData.qml",
                                " ","fun_Update_RealTimeInfo_Current:",
                                " ","varVariableLst.length:",
                                " ",varVariableLst.length,
                                " ","is not 18",
                                  " ","varVariableLst:", varVariableLst);

                }

            }//if (xhr.readyState === XMLHttpRequest.DONE)

            console.log("CurrentUserStockData.qml",
                        " ","RealTimeInfo xhr.onreadystatechange = function()  return");
        }//function


        //发送请求
        xhr.send();

        console.log("CurrentUserStockData.qml",
                    " ","fun_Update_RealTimeInfo_Current()  return");
        varReturnValue = true;
        return varReturnValue;
    }//function fun_Update_RealTimeInfo_Current()


    function fun_createListElement(recordTmp)
    {// 存储数据对象函数
        // 用来接收下面分离的7位数据，以类似结构体的形式存储下来
        // 这也是该model真正存储的数据类型格式
        //Date,Open,High,Low,Close,Volume,Adj Close
        //2014-10-13,101.33,101.78,99.81,99.81,53485500,99.81
        return {
            "m_str_date": recordTmp[0],
            "m_str_open":recordTmp[1],
            "m_str_high":recordTmp[2],
            "m_str_low":recordTmp[3],
            "m_str_close":recordTmp[4],
            "m_str_volume":recordTmp[5],
            "m_str_adjusted":recordTmp[6]
        };
    }

    function fun_Update_HistoryInfo_Current()
    {
        var varReturnValue = false;
        var symbolTmp = "";
        var varRequest = "";

        //标志位置false
        id_qml_CurrentUserStockData.m_bool_HistoryDataReady = false;
        //数据清空
        id_qml_CurrentUserStockData.clear();


        symbolTmp = m_s_Symbol_current;
        //check
        if (symbolTmp.length <= 0)
        {
            console.error('CurrentUserStockData.qml',
                        ' ','fun_Update_HistoryInfo_Current',
                        ' ','m_s_Symbol_current is empty');
            varReturnValue = false;
            return varReturnValue;
        }


        if (m_str_HistoryDataCycle !== "d" && m_str_HistoryDataCycle !== "m" && m_str_HistoryDataCycle !== "y")
        {
            m_str_HistoryDataCycle = "d";// 如果数据周期不是'天'、'周'、'月'，则定义为'天'
        }
        if (m_str_HistoryDataCycle == "d")
        {
            varRequest = m_YahooHistoryReqAck.fun_create_request_x_day(symbolTmp, m_n_HistoryDataTimeCount);
        }
        if (m_str_HistoryDataCycle == "m")
        {
            varRequest = m_YahooHistoryReqAck.fun_create_request_x_month(symbolTmp, m_n_HistoryDataTimeCount);
        }
        if (m_str_HistoryDataCycle == "y")
        {
            varRequest = m_YahooHistoryReqAck.fun_create_request_x_year(symbolTmp, m_n_HistoryDataTimeCount);
        }
        //TODO....


        if (varRequest.length <= 0)
        {
            varReturnValue = false;
            return varReturnValue;
        }
        console.log("CurrentUserStockData.qml",
                    " ","fun_Update_HistoryInfo_Current:",
                    " ","XMLHttpRequest:",
                    " ",varRequest);

        //初始化请求参数，还未发送请求
        var xhr = new XMLHttpRequest();
        xhr.open("GET", varRequest, true);

        xhr.onreadystatechange = function()
        {
            console.log("CurrentUserStockData.qml",
                        " ","fun_Update_HistoryInfo_Current:",
                        " ","xhr.readyState:",
                        " ",xhr.readyState);

            if (xhr.readyState === XMLHttpRequest.DONE)
            //if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE)
            {

                console.log("CurrentUserStockData.qml",
                            " ","fun_Update_HistoryInfo_Current:",
                            " ","xhr.responseText:",
                            " ",xhr.responseText);


                var varVariableLst = m_YahooHistoryReqAck.fun_process_responseText_Historical_HeaderBody(xhr.responseText);

                /*
                console.log("CurrentUserStockData.qml",
                            " ","fun_Update_HistoryInfo_Current:",
                            " ","varVariableLst.length:",
                            " ",varVariableLst.length,
                            " ","varVariableLst:", varVariableLst);
                */

                //body begin with 1
                for (var nIndex = 1;nIndex < varVariableLst.length; nIndex++ )
                {
                    // 以逗号将数据分割
                    var varRecodeVariableLst = m_YahooHistoryReqAck.fun_process_responseText_Historical_BodyLine(
                                varVariableLst[nIndex]);
                    //var recodeTmp = records[nIndex].split(',');
                    // 数据校验
                    if (varRecodeVariableLst.length === 7)
                    {
                        // 函数调用，向model中添加数据
                        id_qml_CurrentUserStockData.append(
                                    id_qml_CurrentUserStockData.fun_createListElement(
                                        varRecodeVariableLst));
                    }
                    else
                    {
                        console.error("CurrentUserStockData.qml",
                                    " ","fun_Update_HistoryInfo_Current:",
                                    " ","nIndex:",nIndex,
                                    " ","varRecodeVariableLst.length:",varRecodeVariableLst.length,
                                    " ","is not 7",
                                    " ","varVariableLst[nIndex]:", varVariableLst[nIndex]);
                    }
                }

                if (xhr.readyState === XMLHttpRequest.DONE)
                {
                    id_qml_CurrentUserStockData.m_bool_HistoryDataReady = true;
                    console.log("CurrentUserStockData.qml",
                                " ","fun_Update_HistoryInfo_Current:",
                                " ","id_qml_CurrentUserStockData.count:",
                                " ",id_qml_CurrentUserStockData.count,
                                " ","emit signalHistoryDataReady");
                    //id_qml_CurrentUserStockData.count;
                    id_qml_CurrentUserStockData.signalHistoryDataReady();//emit signalHistoryDataReady

                }//if (xhr.readyState === XMLHttpRequest.DONE)


            }//if (xhr.readyState === XMLHttpRequest.LOADING || xhr.readyState === XMLHttpRequest.DONE)

            console.log("CurrentUserStockData.qml",
                        " ","HistoryInfo xhr.onreadystatechange = function()  return");
        }//function


        //发送请求
        xhr.send();

        console.log("CurrentUserStockData.qml",
                    " ","fun_Update_HistoryInfo_Current() return");

        varReturnValue = true;
        return varReturnValue;
    }//function fun_Update_HistoryInfo_Current()




}//ListModel


