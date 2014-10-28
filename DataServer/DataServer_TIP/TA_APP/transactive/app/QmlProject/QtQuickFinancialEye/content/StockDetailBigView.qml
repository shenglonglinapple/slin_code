import QtQuick 2.0
import QtQuick.Window 2.1               // 下面的代码使用了Screen因此引入这个模块

Rectangle
{
    id: id_qml_StockDetailBigView;
    //
    width: parent.width;
    height: parent.height;

    //color: "transparent"
    color: "blue"

    //矩形旋转，再平移
    //矩形绕着Item.Center旋转90度，再平移x（height/2-width/2） y(width/2-height/2)，以适合屏幕
    transformOrigin: Item.Center
    rotation: 90;//
    transform: Translate
    {
        x: id_qml_StockDetailBigView.height/2 - id_qml_StockDetailBigView.width/2
        y: id_qml_StockDetailBigView.width/2 - id_qml_StockDetailBigView.height/2
    }


    function fun_update()
    {
        m_HistoryDataBigGraphWindow.fun_update();
    }

    //曲线绘制部分
    HistoryDataBigGraphWindow
    {
        id : m_HistoryDataBigGraphWindow

        anchors.top: id_qml_StockDetailBigView.top
        anchors.left: id_qml_StockDetailBigView.left;
        anchors.right: id_qml_StockDetailBigView.right
        //anchors.rightMargin: 1
        anchors.bottom: id_qml_StockDetailBigView.bottom
    }




}//Rectangle



