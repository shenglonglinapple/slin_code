import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with StockListDelegate.qml StockListModel.qml
Rectangle
{
    id: id_qml_StockListView

    width:parent.width;
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    color: "white"


    //mvc data
    StockListModel
    {
        id: m_StockListModel;
        //no width height
    }

    //mvc 怎样显示这些数据
    StockListDelegate
    {
        id: m_StockListDelegate;
        //no width height
    }

    //Component for ListView
    Component
    {
        id: m_Component_highlight
        //no width height

        Rectangle
        {
            id:m_Rectangle_highlight;
            //width: id_qml_StockListView.width
            //height: 60;//m_Rectangle_StockListDelegate.height;//60
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        //0
        id: m_ListView_UserStock;
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
        model: m_StockListModel; // 定义model
        delegate: m_StockListDelegate;//显示Item
        highlight: m_Component_highlight;
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
        var m_s_Symbol_Extern_Tmp = "";
        var varRealTimeInfo = "";
        var varRequest = "";

        m_s_Symbol_Tmp = m_ListView_UserStock.model.get(index).m_s_Symbol;
        m_s_Symbol_Extern_Tmp = m_ListView_UserStock.model.get(index).m_s_Symbol_Extern;
        //check
        if (m_s_Symbol_Tmp.length <= 0)
        {
            console.error('StockListView.qml',
                        ' ','fun_Update_RealTimeInfo_byindex',
                        ' ','m_s_Symbol is empty');
            varReturnValue = false;
            return varReturnValue;
        }

        varRequest = m_YahooRealTimeReqAck.fun_create_request_LatestQuotesCsv(m_s_Symbol_Tmp, m_s_Symbol_Extern_Tmp);
        if (varRequest.length <= 0)
        {
            varReturnValue = false;
            return varReturnValue;
        }
        console.log("StockListView.qml",
                    " ","fun_Update_RealTimeInfo_byindex:",
                    " ","XMLHttpRequest:",
                    " ",varRequest);

        //初始化请求参数，还未发送请求
        var xhr = new XMLHttpRequest();
        xhr.open("GET", varRequest, true);

        xhr.onreadystatechange = function()
        {
            console.log("DataRequest.qml",
                        " ","fun_Update_RealTimeInfo_byindex:",
                        " ","xhr.readyState:",
                        " ",xhr.readyState);

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
                    varValueTmp = varVariableLst[1];
                    console.log("StockListView.qml"," ","varValueTmp==",varValueTmp);
                    m_ListView_UserStock.model.setProperty(index, "m_s_Symbol",varValueTmp);
                    varValueTmp = varVariableLst[2];
                    m_ListView_UserStock.model.setProperty(index, "m_c6_Change_Realtime",varValueTmp);
                    varValueTmp = varVariableLst[3];
                    m_ListView_UserStock.model.setProperty(index, "m_p2_Change_in_Percent",varValueTmp);
                    varValueTmp = varVariableLst[13];
                    m_ListView_UserStock.model.setProperty(index, "m_l1_Last_Trade_Price_Only",varValueTmp);
                    varValueTmp = varVariableLst[17];
                    if (varValueTmp.length > 0)
                    {
                        console.log("StockListView.qml"," ","varValueTmp==",varValueTmp);
                        m_ListView_UserStock.model.setProperty(index, "m_n_Name",varValueTmp);
                    }


                }
                else
                {
                    console.error("StockListView.qml",
                                " ","fun_Update_RealTimeInfo_byindex:",
                                " ","varVariableLst.length:",
                                " ",varVariableLst.length,
                                " ","is not 18",
                                  " ","varVariableLst:", varVariableLst);

                }

            }//if (xhr.readyState === XMLHttpRequest.DONE)

            console.log("StockListView.qml",
                        " ","RealTimeInfo xhr.onreadystatechange = function()  return");
        }//function


        //发送请求
        xhr.send();

        console.log("StockListView.qml",
                    " ","fun_Update_RealTimeInfo_byindex()  return");
        varReturnValue = true;
        return varReturnValue;
    }//function fun_Update_RealTimeInfo_byindex(index)


    function  fun_add_usr_stock(m_n_Name, m_s_Symbol, m_s_Symbol_Extern)
    {
        console.log('StockListView.qml',
                    ' ','fun_add_usr_stock',
                    ' ','m_s_Symbol=', m_s_Symbol,
                    ' ','m_n_Name=', m_n_Name);

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
        console.log("StockListView.qml",
                    " ","fun_remove_usr_stockList",
                    " ","m_s_Symbol=", m_s_Symbol,
                    " ","m_n_Name=", m_n_Name);

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
        console.log('StockListView.qml',
                    ' ','fun_check_in_usr_stockList',
                    ' ','m_s_Symbol=', m_s_Symbol);
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


