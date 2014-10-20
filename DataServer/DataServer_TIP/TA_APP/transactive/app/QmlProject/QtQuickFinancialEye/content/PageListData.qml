import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    //big first
    id: id_qml_PageListData

    //
    property string m_s_Symbol_current: ""              // 股票ID
    property string m_n_Name_current: ""            // 股票名

    property string m_str_stockDataCycle: "d"      // 数据周期
    property bool m_bool_ready: false               // 标志位
    //
    signal signalDataReady                      // 耗时的数据类通常需要定义这个信号


    ///
    function fun_setDefaultValue()
    {

    }


}//ListModel


