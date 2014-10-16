import QtQuick 2.0
import QtQml.Models 2.1

// 使用Screen引入这个模块 QtQuick.Window 2.1

// 添加其他qml文件路径
import "./content"

Rectangle
{
    id: id_qml_QtQuickFinancialEye;
    width: 1000;
    height: 800;

    //////////////////////////////////////////
    //导航栏
    TopBanner
    {
        id:m_TopBanner;
        width: id_qml_QtQuickFinancialEye.width
        anchors.top: id_qml_QtQuickFinancialEye.top
        m_MainPage_ListView_ref:m_Mainpage_ListView;
    }

    PageListView
    {
        id:m_Mainpage_ListView;
        width: parent.width;
        //notice:大小位置必须制定清楚才能看到滑动效果
        anchors.top: m_TopBanner.bottom;
        anchors.bottom: parent.bottom;
    }


    //////////////////////////////////////////
}//Rectangle


