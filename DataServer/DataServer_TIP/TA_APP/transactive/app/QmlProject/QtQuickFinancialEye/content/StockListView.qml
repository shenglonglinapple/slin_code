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

    property string currentStockId: ""
    property string currentStockName: ""




    //mvc data
    StockListModel
    {
        id: m_listModel;
    }

    //mvc 怎样显示这些数据
    StockListDelegate
    {
        id: m_listDelegate;
    }

    //Component for ListView
    Component
    {
        id: m_highlight
        Rectangle
        {
            width: parent.width
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        id: m_listViewStock;
        anchors.fill: parent
        width: parent.width
        clip: true                            // clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: m_listModel;                 // 定义model
        delegate: m_listDelegate;
        highlight: m_highlight;


        onCurrentIndexChanged:
        {// 当该ListView中的某个项目被选中

            console.log('StockListView.qml',
                        ' ','onCurrentIndexChanged',
                        ' ','m_listViewStock.currentIndex:',m_listViewStock.currentIndex);

            //切换主ListView的页面
            //id_qml_stocqt.listViewActive = 0;//使用了属性绑定
            //TODO.

            // 获取 Id 与 name
            //set value and emit
            id_qml_StockListView.currentStockId = model.get(m_listViewStock.currentIndex).stockId;
            id_qml_StockListView.currentStockName = model.get(m_listViewStock.currentIndex).name;
            console.log('StockListView.qml', ' ', 'onCurrentIndexChanged',
                        ' ','update',' ','currentStockName',
                        ' ','id_qml_StockListView.currentStockId:',id_qml_StockListView.currentStockId,
                        ' ','id_qml_StockListView.currentStockName:',id_qml_StockListView.currentStockName);
        }//onCurrentIndexChanged

    }//ListView
}


