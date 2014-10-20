import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    //big first
    id:id_qml_CurrentUserStockData;

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
    property string m_str_stockDataCycle: "d";//数据周期
    property bool m_bool_HistoryDataReady: false;//标志位
    //
    signal signalHistoryDataReady//耗时的数据类通常需要定义这个信号


    ///
    function fun_setDefaultValue()
    {

    }




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




}//ListModel


