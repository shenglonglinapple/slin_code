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
    color: "#000000";
    //color: "transparent"

    //AddStock
    Rectangle
    {
        id: m_Rectangle_AddStock
        // 容器的尺寸由组件决定
        width: m_Text_AddStock.width;//指定了width才能居中
        height: id_qml_BottomBanner.height
        anchors.horizontalCenter: id_qml_BottomBanner.horizontalCenter
        anchors.verticalCenter: id_qml_BottomBanner.verticalCenter

        color:"Peru"

        MouseArea
        {
            anchors.fill: parent

            onClicked:
            {
                m_Mainpage_ListView.currentIndex = m_PageListData.m_n_MainpageListView_Index_TotalStockListView;
                console.log('BottomBanner.qml',
                            ' ','AddStock',
                            ' ','MouseArea',
                            ' ','onClicked',
                            ' ','m_Mainpage_ListView.currentIndex:',m_Mainpage_ListView.currentIndex,
                            ' ','m_Mainpage_ListView.count:',m_Mainpage_ListView.count);
            }

        }//MouseArea

        Text
        {// Stocqt
            id: m_Text_AddStock

            anchors.verticalCenter: m_Rectangle_AddStock.verticalCenter

            color: "Gold";//"#ffffff"
            font.family: "Abel"
            font.pointSize: m_Rectangle_AddStock.height/2;// - 10
            //text: "Financial Eye"
            text: "AddStock";
        }
    }//Item




}//Rectangle


