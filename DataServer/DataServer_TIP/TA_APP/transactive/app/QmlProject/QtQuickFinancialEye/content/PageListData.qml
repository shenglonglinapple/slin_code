import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    //big first
    id: id_qml_PageListData

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
    property string m_str_stockId: ""              // 股票ID
    property string m_str_stockName: ""            // 股票名

    property real m_real_stockPrice: 0.0           // 股票价格
    property real m_real_stockPriceChanged: 0.0    // 价格变化
    property real m_real_stockPriceYesterday: 0.0  //昨天的股票价格
    property string m_str_stockPriceChanged_Percentage: "10%"    //价格变化百分比

    property string m_str_stockDataCycle: "d"      // 数据周期
    property bool m_bool_ready: false               // 标志位
    //
    signal signalDataReady                      // 耗时的数据类通常需要定义这个信号


    ///
    function fun_setDefaultValue()
    {
        id_qml_PageListData.m_real_stockPrice = 1.0;//当前的股票价格
        id_qml_PageListData.m_real_stockPriceChanged = 0.2;//比昨天的股票价格涨了0.2
        id_qml_PageListData.m_str_stockDataCycle = "d";
        id_qml_PageListData.m_bool_ready = false;

        id_qml_PageListData.m_real_stockPriceYesterday =id_qml_PageListData.m_real_stockPrice - id_qml_PageListData.m_real_stockPriceChanged;
        id_qml_PageListData.m_str_stockPriceChanged_Percentage = Math.abs(Math.round(m_real_stockPriceChanged/(id_qml_PageListData.m_real_stockPriceYesterday) * 100))/100  + "%";
    }


    function fun_UpdateStockInfo()
    {
        id_qml_PageListData.fun_setDefaultValue();


    }

}//ListModel


