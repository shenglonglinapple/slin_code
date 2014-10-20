import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with StockListDelegate.qml StockListModel.qml
Rectangle
{
    id: id_qml_StockListView
    width: 320
    height: 410
    anchors.top: parent.top
    anchors.bottom: parent.bottom

    color: "white"

    //mvc data
    StockListModel
    {
        id: m_listModel;
        //no width height
    }

    //mvc 怎样显示这些数据
    StockListDelegate
    {
        id: m_listDelegate;
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
            width: parent.width
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        //0
        id: m_listViewStock;
        //1
        width: parent.width

        anchors.fill: parent

        clip: true                            // clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: m_listModel;                 // 定义model
        delegate: m_listDelegate;
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
        var symbolTmp = "";
        var varRealTimeInfo = "";
        var varRequest = "";

        symbolTmp = m_listViewStock.model.get(index).m_s_Symbol;
        //check
        if (symbolTmp.length <= 0)
        {
            console.error('StockListView.qml',
                        ' ','fun_Update_RealTimeInfo_byindex',
                        ' ','m_s_Symbol is empty');
            varReturnValue = false;
            return varReturnValue;
        }

        varRequest = m_YahooRealTimeReqAck.fun_create_request_LatestQuotesCsv(symbolTmp);
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
                    m_listViewStock.model.setProperty(index, "m_s_Symbol",varValueTmp);
                    varValueTmp = varVariableLst[2];
                    m_listViewStock.model.setProperty(index, "m_c6_Change_Realtime",varValueTmp);
                    varValueTmp = varVariableLst[3];
                    m_listViewStock.model.setProperty(index, "m_p2_Change_in_Percent",varValueTmp);
                    varValueTmp = varVariableLst[14];
                    m_listViewStock.model.setProperty(index, "m_l1_Last_Trade_Price_Only",varValueTmp);
                    varValueTmp = varVariableLst[17];
                    console.log("StockListView.qml"," ","varValueTmp==",varValueTmp);
                    m_listViewStock.model.setProperty(index, "m_n_Name",varValueTmp);
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



}//Rectangle


