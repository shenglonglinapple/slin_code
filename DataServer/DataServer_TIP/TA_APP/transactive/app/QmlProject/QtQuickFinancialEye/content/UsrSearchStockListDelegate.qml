import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with TotalStockListModel.qml
//ListView 中每个元素怎样显示
Component
{
    // 委托组件，基本都是布局
    id: id_qml_UsrSearchStockListDelegate

    Rectangle
    {
        id:m_Rectangle_UsrSearchStockListDelegate

        width: parent.width;
        height: 60;


        color: "transparent";

        property real m_n_Text_Symbol_height: 22;
        property real m_n_Text_Name_height: 20;
        property real m_n_Text_rightMargin: 10;
        property real m_n_Text_leftMargin: 10;
        property real m_n_Text_topMargin: 3;
        property real m_n_Text_fontsize_percent: 0.5;

        visible: true

        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                console.log('TotalStockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','m_UsrSearchStockListModel.count:', m_UsrSearchStockListModel.count,
                            ' ','m_ListView_UsrSearchStock.currentIndex:', m_ListView_UsrSearchStock.currentIndex,
                            ' ','new index:', index);

                //if m_listViewStock.currentIndex the same as index  then will not emit currentIndexChanged
                if (m_ListView_UsrSearchStock.currentIndex != index)
                {
                    m_ListView_UsrSearchStock.currentIndex = index;//where is index define?????
                }



            }
        }

        //
        Text
        {//Symbol
            id: m_Text_Symbol

            //width: 128
            height: m_n_Text_Symbol_height;

            anchors.top: parent.top
            anchors.topMargin: m_n_Text_topMargin
            anchors.left: parent.left
            anchors.leftMargin: m_n_Text_leftMargin

            //color: "#0c34f9"
            color:"blue"
            font.family: "Helvetica";//font.family: "Open Sans"// 我的机器貌似不支持这种字体
            font.pointSize: m_n_Text_Symbol_height * m_n_Text_fontsize_percent
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter

            text: m_s_Symbol


            Component.onCompleted:
            {
                console.log('TotalStockListDelegate.qml',
                            ' ','Text m_s_Symbol',' ',
                            ' ','Component.onCompleted',' ',
                            ' ','index:',index,
                            ' ','m_s_Symbol:',m_s_Symbol);
            }//Component.onCompleted:

        }//Text


        Text
        {//Name
            id: m_Text_Name

            //width: 256
            height: m_n_Text_Name_height

            anchors.top: parent.top
            anchors.topMargin: m_n_Text_topMargin
            anchors.left: m_Text_Symbol.right
            anchors.leftMargin: m_n_Text_leftMargin

            //color: "#000000"
            color:"blue"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: m_n_Text_Name_height * m_n_Text_fontsize_percent
            font.bold: false
            elide: Text.ElideRight
            maximumLineCount: 1
            verticalAlignment: Text.AlignVCenter

            text: m_n_Name
        }//Text


    }//Rectangle Item

}//Component
