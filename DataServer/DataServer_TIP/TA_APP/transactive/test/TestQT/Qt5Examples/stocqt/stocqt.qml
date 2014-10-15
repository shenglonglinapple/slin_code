import QtQuick 2.0
import QtQml.Models 2.1
import "./content"                   // 添加其他qml文件路径

Rectangle
{
    id: id_qml_stocqt;
    width: 1000;
    height: 700;

    property int listViewActive: 0      // 该页面实际是一个ListView的一部分，这个属性用来表明前面的列表页面是否被激活

    //////////////////////////////////////////
    Rectangle
    { // 导航栏
        id: m_Rectangle_banner
        height: 80
        anchors.top: parent.top
        width: parent.width
        color: "#000000"

        Image
        {
            id: m_Image_arrow
            source: "./content/images/icon-left-arrow.png"
            anchors.left: m_Rectangle_banner.left
            anchors.leftMargin: 20
            anchors.verticalCenter: m_Rectangle_banner.verticalCenter
            visible: m_ListView_Main.currentIndex == 1 ? true : false  // 曲线页面是ListView的第二个页面，currentIndex的值也就是1

            MouseArea
            {
                anchors.fill: parent
                onClicked:
                {
                    //使用了属性绑定，当listViewActive set value 1时，使currentIndex置0，从而跳转到列表页面
                    console.log('stocqt.qml',
                                ' ', 'Image',' ',
                                ' ', 'MouseArea',' ',
                                ' ','onClicked',' ',
                                ' ','id_qml_stocqt.listViewActive:',id_qml_stocqt.listViewActive);
                    id_qml_stocqt.listViewActive = 1;
                }
            }
        }

        Item
        {// 将相关组件放在一个Item容器中 "StocQt"
            id: m_Item_text
            width: m_Text_stoc.width + m_Text_qt.width           // 容器的尺寸由组件决定
            height: m_Text_stoc.height + m_Text_qt.height
            anchors.horizontalCenter: m_Rectangle_banner.horizontalCenter
            anchors.verticalCenter: m_Rectangle_banner.verticalCenter

            Text
            {                                  // Stoc
                id: m_Text_stoc
                anchors.verticalCenter: m_Item_text.verticalCenter
                color: "#ffffff"
                font.family: "Abel"
                font.pointSize: 40
                text: "Stoc"
            }

            Text
            {                                   // Qt
                id: m_Text_qt
                anchors.verticalCenter: m_Item_text.verticalCenter
                anchors.left: m_Text_stoc.right
                color: "#5caa15"
                font.family: "Abel"
                font.pointSize: 40
                text: "Qt"
            }
        }//Item
    }//Rectangle 导航栏




    //////////////////////////////////////////
    ListView
    {// 标题栏下方则是ListView的内容，它为列表页面与曲线页面提供了滑动切换的能力
        id: m_ListView_Main
        width: parent.width
        anchors.top: m_Rectangle_banner.bottom
        anchors.bottom: parent.bottom
        snapMode: ListView.SnapOneItem        // 设置该属性使View停止在一个完整的页面上
        highlightRangeMode: ListView.StrictlyEnforceRange
        highlightMoveDuration: 250                  // 这里设置了一个无形的高亮，它不显示，但提供了0.25秒的切换动画
        focus: false
        orientation: ListView.Horizontal //水平方向上放了两个页面  StockListView（列表页面） StockView（曲线页面）
        boundsBehavior: Flickable.StopAtBounds     // 滑动时停在边界，默认可以拉拽更远并在弹回时带有超调效果
        //listViewActive is value 1
        //使用属性绑定，当listViewActive被激活时，使currentIndex置0，从而跳转到列表页面
        currentIndex: id_qml_stocqt.listViewActive == 0 ? 1 : 0

        onCurrentIndexChanged:
        {
            console.log('stocqt.qml', ' ', 'onCurrentIndexChanged:',
                        ' ','currentIndex:',currentIndex,
                        ' ','listViewActive:',listViewActive);

            if (currentIndex == 1)
            {
                id_qml_stocqt.listViewActive = 0;
            }
        }



        model: ObjectModel
        {       // ObjectModel源自上面import的Qt.QML.Model 2.1，它使得ListView可以使用一组对象作为模型
            //index=0
            StockListView
            {           //列表页面
                id: m_page_listView
                width: m_ListView_Main.width
                height: m_ListView_Main.height;
            }

            //index=1
            StockView
            {               //曲线页面
                id: m_page_stockView;
                width: m_ListView_Main.width
                height: m_ListView_Main.height
                m_page_listView_ref: m_page_listView
                m_data_stock_ref: m_data_stock
            }
        }//model: ObjectModel


        //data in m_ListView_Main
        StockModel
        {
            // 初始化数据模型
            id: m_data_stock
            //stockId binding with m_page_listView.currentStockId
            //when m_page_listView.currentStockId changed, stockId will changed, then emit stockIdChanged();
            stockId: m_page_listView.currentStockId     // 注意这个listView不是其父ListView，而是下面那个，即列表页面
            stockName: m_page_listView.currentStockName  // 列表页面将当前所选的股票ID及名字赋给StockModel，使其取得相应的数据

            onStockIdChanged:
            {
                console.log('stocqt.qml',' ','onStockIdChanged:',
                            ' ','stockId:',stockId,
                            ' ','stockName:',stockName);
                // 当ID改变时数据更新
                m_data_stock.updateStock();
            }

            onStockNameChanged:
            {
                console.log('stocqt.qml',' ','onStockNameChanged:',
                            ' ','stockId:',stockId,
                            ' ','stockName:',stockName);
            }


            onSignalDataReady:
            {
                //log
                //AAPL Apple Inc.
                //ADBE Adobe Systems Inc.
                console.log('stocqt.qml',
                            ' ','onSignalDataReady:',
                            ' ','currentStockId:',m_page_listView.currentStockId,
                            ' ','currentStockName:',m_page_listView.currentStockName);

                //上面的高亮即为这里的ListView.SnapPosition做准备，数据变更后切换到曲线页面，带有0.25秒的过渡动画
                //显示曲线页面
                m_ListView_Main.positionViewAtIndex(1, ListView.SnapPosition)
                // 页面更新
                m_page_stockView.update()
            }
        }//StockModel
    }//ListView

    //////////////////////////////////////////
}//Rectangle


