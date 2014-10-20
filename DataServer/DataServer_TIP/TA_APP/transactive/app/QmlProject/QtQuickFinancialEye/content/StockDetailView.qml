import QtQuick 2.0
import QtQuick.Window 2.1               // 下面的代码使用了Screen因此引入这个模块

Rectangle
{
    id: id_qml_StockDetailView;

    width: 320
    height: 480

    color: "transparent"


    property var m_page_listView_ref: null

    Rectangle
    {
        id: m_Rectangle_StockDetailView
        color: "transparent"
        anchors.fill: parent

        StockDataRealTimeWindow
        {//提供左上方的股票信息
            id: m_StockDataRealTimeWindow;

            height: 160;

            anchors.left: parent.left;
            anchors.leftMargin: 1
            anchors.top: parent.top
            anchors.topMargin: 1
            //基于属性绑定的屏幕转向后布局方式的变化
            anchors.right: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.right : m_StockPriceChart.left
            anchors.rightMargin: 1
        }//StockDetailInfo

        StockPriceChart
        {//右方的曲线绘制部分
            id: m_StockPriceChart

            //基于属性绑定的屏幕转向后布局方式的变化
            width: Screen.primaryOrientation === Qt.PortraitOrientation ? parent.width - 40 : 0.6 * parent.width

            anchors.bottom: Screen.primaryOrientation === Qt.PortraitOrientation ? settingsPanel.top : parent.bottom
            anchors.bottomMargin: 1
            anchors.top : Screen.primaryOrientation === Qt.PortraitOrientation ? m_StockDataRealTimeWindow.bottom : parent.top
            anchors.topMargin: 1
            anchors.right: parent.right
            anchors.rightMargin: 1

        }//StockPriceChart

    }//Rectangle


}//Rectangle


