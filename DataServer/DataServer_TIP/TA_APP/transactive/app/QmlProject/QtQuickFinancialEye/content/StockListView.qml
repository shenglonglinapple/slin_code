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
}


