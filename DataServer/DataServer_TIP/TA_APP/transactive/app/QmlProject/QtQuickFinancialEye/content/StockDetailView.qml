import QtQuick 2.0
import QtQuick.Window 2.1               // 下面的代码使用了Screen因此引入这个模块

Rectangle
{
    id: id_qml_StockDetailView;
    //
    width: parent.width;
    height: parent.height;

    color: "transparent"

    function fun_update()
    {
        m_HistoryDataGraphWindow.fun_update();
    }

    StockDataRealTimeWindow
    {//提供左上方的股票信息
        id: m_StockDataRealTimeWindow;
        //
        width:id_qml_StockDetailView.width;
        height: 200;
        anchors.top: id_qml_StockDetailView.top
        anchors.left: id_qml_StockDetailView.left;

        //基于属性绑定的屏幕转向后布局方式的变化
        //anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : m_StockPriceChart.left
        //anchors.rightMargin: 1
    }//StockDetailInfo


    ChooseHistoryDataTypeWindow
    {
        id : m_ChooseHistoryDataTypeWindow
        //
        width:id_qml_StockDetailView.width;
        height: 64;
        anchors.top: m_StockDataRealTimeWindow.bottom
        anchors.left: id_qml_StockDetailView.left;
    }



    //曲线绘制部分
    HistoryDataGraphWindow
    {
        id : m_HistoryDataGraphWindow

        anchors.top: m_ChooseHistoryDataTypeWindow.bottom
        anchors.left: id_qml_StockDetailView.left;
        anchors.right: id_qml_StockDetailView.right
        //anchors.rightMargin: 1
        anchors.bottom: id_qml_StockDetailView.bottom
    }




}//Rectangle


