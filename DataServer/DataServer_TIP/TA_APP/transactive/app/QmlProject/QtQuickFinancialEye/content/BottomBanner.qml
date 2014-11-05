import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1


//导航栏
Rectangle
{
    //0
    id: id_qml_BottomBanner
    //1
    width: parent.width
    height: 20
    anchors.bottom: parent.bottom

    //2
    //color: "#000000";
    //color: "transparent"
    color: "PowderBlue"

    //visible: m_Mainpage_ListView.currentIndex == m_PageListData.m_n_MainpageListView_Index_StockDetailBigView ? false : true

    //UI
    Row
    {//1行 Row布局了自定义的按钮
        id: m_Row_Buttons;
        anchors.fill: parent;
        spacing: 10

        onWidthChanged:
        {// 该函数保证宽度变化时优先压缩spacing，且不会造成按钮重叠
            var buttonsLen = m_Button_MyStocks.width + m_Button_AddStock.width;
            var space = (width - buttonsLen) / 10;
            spacing = Math.max(space, 4);
        }

        //Button MyStocks
        Button
        {
            id: m_Button_MyStocks
            text: "MyStocks"
            buttonEnabled: m_Mainpage_ListView.currentIndex == m_PageListData.m_n_MainpageListView_Index_StockListView ? false : true
            onClicked:
            {
                m_Mainpage_ListView.currentIndex = m_PageListData.m_n_MainpageListView_Index_StockListView;
                console.log('BottomBanner.qml',
                            ' ','MyStocks',
                            ' ','MouseArea',
                            ' ','onClicked',
                            ' ','m_Mainpage_ListView.currentIndex:',m_Mainpage_ListView.currentIndex,
                            ' ','m_Mainpage_ListView.count:',m_Mainpage_ListView.count);
            }
        }//Button MyStocks

        //Button AddStock
        Button
        {
            id: m_Button_AddStock
            text: "AddStock"
            buttonEnabled: m_Mainpage_ListView.currentIndex == m_PageListData.m_n_MainpageListView_Index_UsrSearchStockListView ? false : true
            onClicked:
            {
                m_Mainpage_ListView.currentIndex = m_PageListData.m_n_MainpageListView_Index_UsrSearchStockListView;
                console.log('BottomBanner.qml',
                            ' ','AddStock',
                            ' ','MouseArea',
                            ' ','onClicked',
                            ' ','m_Mainpage_ListView.currentIndex:',m_Mainpage_ListView.currentIndex,
                            ' ','m_Mainpage_ListView.count:',m_Mainpage_ListView.count);
            }
        }//Button MyStocks

    }//Row


}//Rectangle


