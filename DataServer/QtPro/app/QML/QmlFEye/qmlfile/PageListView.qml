import QtQuick 2.0
import QtQml.Models 2.1

ListView
{
    //标题栏下方则是ListView的内容，它为列表页面与曲线页面提供了滑动切换的能力
    id: id_qml_PageListView;

    //notice:大小位置必须制定清楚才能看到滑动效果
    width: parent.width;
    //height:100  no use height
    anchors.top: parent.top;
    //anchors.bottom: parent.bottom;

    //设置该属性使View停止在一个完整的页面上
    snapMode: ListView.SnapOneItem
    highlightRangeMode: ListView.StrictlyEnforceRange
    // 这里设置了一个无形的高亮，它不显示，但提供了0.25秒的切换动画
    highlightMoveDuration: 250
    focus: false

    //水平方向上放了多个页面
    orientation: ListView.Horizontal
    //滑动时停在边界，默认可以拉拽更远并在弹回时带有超调效果
    boundsBehavior: Flickable.StopAtBounds


    preferredHighlightBegin: 0;
    preferredHighlightEnd: 0;
    flickDeceleration: 2000
    cacheBuffer: 200

    currentIndex: 0;

    //信号 向服务器发请求 获取当前股票信息realtime history
    signal signalUpdateCurrentUserStockData;

    //
    PageListModel
    {
       id: m_PageListModel
    }

    model: m_PageListModel


    //
    onCurrentIndexChanged:
    {
        console.log("PageListView.qml",
                    " ", "onCurrentIndexChanged",
                    " ", "id_qml_PageListView.currentIndex=", id_qml_PageListView.currentIndex,
                    " ", "id_qml_PageListView.count=", id_qml_PageListView.count);
    }//onCurrentIndexChanged

}//ListView




