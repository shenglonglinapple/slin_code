import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with StockListDelegate.qml StockListModel.qml
Rectangle
{
    id: id_qml_TotalStockListView

    width:parent.width;
    //anchors.top: parent.top
    //anchors.bottom: parent.bottom

    color: "white"

    property string m_str_SeachStock : "002024";


    TextInput
    {
        id: m_TextInput_SeachStock

    }

    //mvc data
    TotalStockListModel
    {
        id: m_TotalStockListModel;
        //no width height
    }

    //mvc 怎样显示这些数据
    TotalStockListDelegate
    {
        id: m_TotalStockListDelegate
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
            height: 30;//m_Rectangle_StockListDelegate.height;//60
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        //0
        id: m_TotalStockListView
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
        model: m_TotalStockListModel; // 定义model
        delegate: m_TotalStockListDelegate;//显示Item
        highlight: m_Component_highlight;
        currentIndex: 0;


        onCurrentIndexChanged:
        {// 当该ListView中的某个项目被选中

        }//onCurrentIndexChanged



    }//ListView



}//Rectangle


