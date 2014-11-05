import QtQuick 2.0

ListModel
{
    // ListModel作为根项目，自定义属性作为接口，并定义了多个函数。但他本身在初始化时并不进行运算
    id: id_qml_PageListData

    //
    property bool m_b_print_log: true;
    property int m_n_TotalStockListModel_Count : 3325;//total 3325 stocks in SS and SZ
    //
    property int m_n_MainpageListView_Index_StockListView : 0;//PageListaView m_Mainpage_ListView.currentIndex=0
    property int m_n_MainpageListView_Index_StockDetailView : 1;
    property int m_n_MainpageListView_Index_StockDetailBigView : 2;
    property int m_n_MainpageListView_Index_UsrSearchStockListView : 3;
    //property int m_n_MainpageListView_Index_PageView : 4;


}//ListModel


