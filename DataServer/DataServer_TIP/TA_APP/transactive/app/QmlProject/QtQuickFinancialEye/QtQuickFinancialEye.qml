import QtQuick 2.0
import QtQml.Models 2.1

// 使用Screen引入这个模块 QtQuick.Window 2.1

// 添加其他qml文件路径
import "./content"


Rectangle
{
    //0
    id: id_qml_QtQuickFinancialEye;
    //1
    width: 1000;
    height: 800;

    //////////////////////////////////////////
    //导航栏
    TopBanner
    {
        //0
        id:m_TopBanner;
        //1
        width: id_qml_QtQuickFinancialEye.width;
        height: 40;
        anchors.top: id_qml_QtQuickFinancialEye.top
        //anchors.bottom:
    }

    //水平方向上的多个页面
    PageListView
    {
        //0
        id:m_Mainpage_ListView;
        //1
        width: parent.width;
        //height: 40;
        //notice:大小位置必须制定清楚才能看到滑动效果
        anchors.top: m_TopBanner.bottom;
        anchors.bottom: parent.bottom;
        //
        onSignalUpdateStockInfo:
        {
            //emit signal signalUpdateStockInfo
            console.log('QtQuickFinancialEye.qml',
                        ' ','PageListView onSignalUpdateStockInfo',
                        ' ','slot signalUpdateStockInfo');

            m_PageListData.fun_setDefaultValue();

        }
    }

    //
    PageListData
    {
        //0
        id:m_PageListData;
        //no width height
        //



    }

    //////////////////////////////////////////
}//Rectangle


