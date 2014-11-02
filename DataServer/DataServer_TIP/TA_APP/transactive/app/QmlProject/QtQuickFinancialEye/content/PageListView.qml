import QtQuick 2.0
import QtQuick.Window 2.1
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

    currentIndex: 0;

    /*
      StockListDelegate.qml
      MouseArea onClicked
      emit signalUpdateStockInfo;


    */
    //信号 向服务器发请求 获取当前股票信息realtime history
    signal signalUpdateCurrentUserStockData;

    onCurrentIndexChanged:
    {
        console.log('PageListView.qml',
                    ' ', 'onCurrentIndexChanged:',
                    ' ','id_qml_MainPage.currentIndex:',id_qml_PageListView.currentIndex,
                    ' ','id_qml_MainPage.count:',id_qml_PageListView.count);

        if (1 == id_qml_PageListView.currentIndex)
        {
            m_CurrentUserStockData.fun_Update_RealTimeInfo_Current();
            //m_CurrentUserStockData.fun_Update_HistoryInfo_Current();
        }

    }


    function fun_update()
    {
        console.log('PageListView.qml',
                    ' ', 'fun_update()',
                    ' ','id_qml_MainPage.currentIndex:',id_qml_PageListView.currentIndex);

        if (id_qml_PageListView.currentIndex == m_PageListData.m_n_MainpageListView_Index_StockDetailView)
        {
            console.log('PageListView.qml',
                        ' ', 'fun_update()',
                        ' ','id_qml_MainPage.currentIndex:',id_qml_PageListView.currentIndex,
                        ' ','m_page_StockDetailView.fun_update()');
           m_page_StockDetailView.fun_update();
        }

        if (id_qml_PageListView.currentIndex == m_PageListData.m_n_MainpageListView_Index_StockDetailBigView)
        {
            console.log('PageListView.qml',
                        ' ', 'fun_update()',
                        ' ','id_qml_MainPage.currentIndex:',id_qml_PageListView.currentIndex,
                        ' ','m_page_StockDetailBigView.fun_update()');
           m_page_StockDetailBigView.fun_update();
        }

    }

    model: ObjectModel
    {
        // ObjectModel源自上面import的Qt.QML.Model 2.1，它使得ListView可以使用一组对象作为模型
        //index=0
        StockListView
        {//列表页面
            id: m_page_StockListView
            width: id_qml_PageListView.width
            height: id_qml_PageListView.height;
            //m_Mainpage_ListView_ref:id_qml_MainPage;
        }

        //index=1
        StockDetailView
        {//曲线页面
            id: m_page_StockDetailView;
            width: id_qml_PageListView.width
            height: id_qml_PageListView.height
        }

        //index=2
        StockDetailBigView
        {
            id: m_page_StockDetailBigView;
            //width: id_qml_PageListView.width
            //height: id_qml_PageListView.height
            width: id_qml_PageListView.height
            height: id_qml_PageListView.width
        }

        //index=3
        TotalStockListView
        {
            id: m_page_TotalStockListView
            width: id_qml_PageListView.width
            height: id_qml_PageListView.height
        }


        //index=4
        PageView
        {//曲线页面
            id: m_page_PageView_2;
            width: id_qml_PageListView.width
            height: id_qml_PageListView.height
        }
    }//model: ObjectModel


}//ListView


