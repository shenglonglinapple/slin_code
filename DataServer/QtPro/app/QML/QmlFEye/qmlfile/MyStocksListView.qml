import QtQuick 2.0

Rectangle
{
    id: id_qml_MyStocksListView

    width:parent.width;
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    color: "white"


    //mvc data
    MyStocksListModel
    {
        id: m_id_MyStocksListModel;
        //no width height
    }

    //mvc 怎样显示这些数据
    MyStocksListDelegate
    {
        id: m_id_MyStocksListDelegate;
        //no width height
    }


    // Define a highlight with customized movement between items.
    Component
    {
        id: m_id_Component_highlight
        Rectangle
        {
            //y: listView.currentItem.y;
            width: parent.with;
            //height: 60
            color: "#eeeeee"

            /*
            Behavior on y
            {
                SpringAnimation
                {
                    spring: 2;
                    damping: 0.1
                }//SpringAnimation
            }//Behavior on y
            */
        }//Rectangle
    }//Component

    ListView
    {
        //0
        id: m_id_ListView_UserStock;
        //1
        width:parent.width;
        anchors.top: parent.top
        anchors.bottom: parent.bottom;
        //anchors.fill: parent

        clip: true// clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: m_id_MyStocksListModel; // 定义model
        delegate: m_id_MyStocksListDelegate;//显示Item

        // Set the highlight delegate. Note we must also set highlightFollowsCurrentItem
        // to false so the highlight delegate can control how the highlight is moved.
        highlight: m_id_Component_highlight
        //highlightFollowsCurrentItem: false

        currentIndex: 0;


        onCurrentIndexChanged:
        {// 当该ListView中的某个项目被选中

        }//onCurrentIndexChanged



    }//ListView



    //fun
    function fun_Update_RealTimeInfo_byindex(index)
    {
        var varReturnValue = false;
        var m_s_Symbol_Tmp = "";
        var varRealTimeInfo = "";
        var varRequest = "";

        m_s_Symbol_Tmp = m_id_ListView_UserStock.model.get(index).m_s_Symbol;


        //check
        if (m_s_Symbol_Tmp.length <= 0)
        {
            console.error("MyStocksListView.qml",
                          " ", "fun_Update_RealTimeInfo_byindex",
                          " ", "m_s_Symbol is empty!");

            varReturnValue = false;
            return varReturnValue;
        }

        varRequest = m_YahooRealTimeReqAck.fun_create_request_LatestQuotesCsv(m_s_Symbol_Tmp);
        if (varRequest.length <= 0)
        {
            varReturnValue = false;
            return varReturnValue;
        }
        console.log("MyStocksListView.qml",
                      " ", "fun_Update_RealTimeInfo_byindex",
                      " ", "XMLHttpRequest=",varRequest);

        //初始化请求参数，还未发送请求
        var xhr = new XMLHttpRequest();
        xhr.open("GET", varRequest, true);

        xhr.onreadystatechange = function()
        {
            console.log("MyStocksListView.qml",
                          " ", "fun_Update_RealTimeInfo_byindex",
                          " ", "xhr.readyState=",xhr.readyState);

            if (xhr.readyState === XMLHttpRequest.DONE)
            {
                /*
                console.log("DataRequest.qml",
                            " ","fun_Update_RealTimeInfo_byindex:",
                            " ","xhr.responseText:",
                            " ",xhr.responseText);
                */


                var varVariableLst = m_YahooRealTimeReqAck.fun_process_responseText_LatestQuotesCsv(xhr.responseText);

                /*
                console.log("StockListView.qml",
                            " ","fun_Update_RealTimeInfo_byindex:",
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
                    var varValueTmp = "";
                    varValueTmp = varVariableLst[0];
                    m_id_ListView_UserStock.model.setProperty(index, "m_x_Stock_Exchange",varValueTmp);
                    varValueTmp = varVariableLst[1];
                    console.log("MyStocksListView.qml"," ","varValueTmp==",varValueTmp);
                    m_id_ListView_UserStock.model.setProperty(index, "m_s_Symbol",varValueTmp);
                    varValueTmp = varVariableLst[2];
                    m_id_ListView_UserStock.model.setProperty(index, "m_c6_Change_Realtime",varValueTmp);
                    varValueTmp = varVariableLst[3];
                    m_id_ListView_UserStock.model.setProperty(index, "m_p2_Change_in_Percent",varValueTmp);
                    varValueTmp = varVariableLst[4];
                    m_id_ListView_UserStock.model.setProperty(index, "m_d1_Last_Trade_Date",varValueTmp);
                    varValueTmp = varVariableLst[5];
                    m_id_ListView_UserStock.model.setProperty(index, "m_ti_Last_Trade_Time",varValueTmp);
                    varValueTmp = varVariableLst[6];
                    m_id_ListView_UserStock.model.setProperty(index, "m_p_Previous_Close",varValueTmp);
                    varValueTmp = varVariableLst[7];
                    m_id_ListView_UserStock.model.setProperty(index, "m_o_Open",varValueTmp);
                    varValueTmp = varVariableLst[8];
                    m_id_ListView_UserStock.model.setProperty(index, "m_b_Bid",varValueTmp);
                    varValueTmp = varVariableLst[9];
                    m_id_ListView_UserStock.model.setProperty(index, "m_a_Ask",varValueTmp);
                    varValueTmp = varVariableLst[10];
                    m_id_ListView_UserStock.model.setProperty(index, "m_g_Day_Low",varValueTmp);
                    varValueTmp = varVariableLst[11];
                    m_id_ListView_UserStock.model.setProperty(index, "m_h_Day_High",varValueTmp);
                    varValueTmp = varVariableLst[12];
                    m_id_ListView_UserStock.model.setProperty(index, "m_m_Day_Range",varValueTmp);
                    varValueTmp = varVariableLst[13];
                    m_id_ListView_UserStock.model.setProperty(index, "m_l1_Last_Trade_Price_Only",varValueTmp);
                    varValueTmp = varVariableLst[14];
                    m_id_ListView_UserStock.model.setProperty(index, "m_t8_1year_Target_Price",varValueTmp);
                    varValueTmp = varVariableLst[15];
                    m_id_ListView_UserStock.model.setProperty(index, "m_v_Volume",varValueTmp);
                    varValueTmp = varVariableLst[16];
                    m_id_ListView_UserStock.model.setProperty(index, "m_a2_Average_Daily_Volume",varValueTmp);
                    varValueTmp = varVariableLst[17];
                    if (varValueTmp.length > 0)
                    {
                        console.log("MyStocksListView.qml"," ","varValueTmp==",varValueTmp);
                        m_id_ListView_UserStock.model.setProperty(index, "m_n_Name",varValueTmp);
                    }


                }
                else
                {
                    console.error("MyStocksListView.qml",
                                " ","fun_Update_RealTimeInfo_byindex:",
                                " ","varVariableLst.length:",
                                " ",varVariableLst.length,
                                " ","is not 18",
                                  " ","varVariableLst:", varVariableLst);

                }

            }//if (xhr.readyState === XMLHttpRequest.DONE)

            console.log("MyStocksListView.qml",
                        " ","RealTimeInfo xhr.onreadystatechange = function()  return");
        }//function


        //发送请求
        xhr.send();

        console.log("MyStocksListView.qml",
                    " ","fun_Update_RealTimeInfo_byindex()  return");
        varReturnValue = true;
        return varReturnValue;
    }//function fun_Update_RealTimeInfo_byindex(index)


    function  fun_add_usr_stock(m_n_Name, m_s_Symbol, m_s_Symbol_Extern)
    {
        console.log("MyStocksListView.qml",
                    " ","fun_add_usr_stock()",
                    " ","m_s_Symbol=",m_s_Symbol,
                    " ","m_n_Name=",m_n_Name);

        m_StockListModel.append( {
            "m_n_Name": m_n_Name,
            "m_s_Symbol": m_s_Symbol,
            "m_s_Symbol_Extern": m_s_Symbol_Extern,
            "m_l1_Last_Trade_Price_Only": "0.0",
            "m_c6_Change_Realtime": "0.0",
            "m_p2_Change_in_Percent": "0.0%"});
    }


    function  fun_remove_usr_stockList(m_n_Name, m_s_Symbol, m_s_Symbol_Extern)
    {
        console.log("MyStocksListView.qml",
                    " ","fun_remove_usr_stockList()",
                    " ","m_s_Symbol=",m_s_Symbol,
                    " ","m_n_Name=",m_n_Name);

        for (var nIndex = 0; nIndex < m_StockListModel.count; nIndex++)
        {
            if (m_s_Symbol === m_StockListModel.get(nIndex).m_s_Symbol)
            {
                m_StockListModel.remove(nIndex);
                return;
            }//if
        }//for

        return;
    }

    function  fun_check_in_usr_stockList(m_s_Symbol)
    {
        console.log("MyStocksListView.qml",
                    " ","fun_check_in_usr_stockList()",
                    " ","m_s_Symbol=",m_s_Symbol);

        var bCheck = false;

        for (var nIndex = 0; nIndex < m_StockListModel.count; nIndex++)
        {
            if (m_s_Symbol === m_StockListModel.get(nIndex).m_s_Symbol)
            {
                bCheck = true;
                return bCheck;
            }//if
        }//for

        return bCheck;
    }




}//Rectangle


