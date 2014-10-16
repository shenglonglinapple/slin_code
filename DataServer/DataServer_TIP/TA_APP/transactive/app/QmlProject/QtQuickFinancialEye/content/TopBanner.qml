import QtQuick 2.0
import QtQuick.Window 2.1               
import QtQml.Models 2.1

Rectangle
{ // 导航栏
    id: id_qml_TopBanner
    height: 40
    anchors.top: parent.top
    width: parent.width
    color: "#000000";

    property var m_MainPage_ListView_ref: null

    //"<"
    Image
    {
        id: m_Image_left_arrow
        source:"qrc:///imgfile/images/icon_left_arrow.png"
        anchors.left: id_qml_TopBanner.left
        anchors.leftMargin: 10
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter
        //第一个主页面不显示 其余页面都要显示
        //visible: m_List_PageView.currentIndex > 0 ? true : false
        visible: true

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                //0 1 2 < 3
                if (m_MainPage_ListView_ref.currentIndex >= 0)
                {
                    if (m_MainPage_ListView_ref.currentIndex === 0)
                    {
                        m_MainPage_ListView_ref.currentIndex = m_MainPage_ListView_ref.count - 1;//go to last page
                    }
                    else
                    {
                       m_MainPage_ListView_ref.currentIndex = m_MainPage_ListView_ref.currentIndex - 1;
                    }
                }

                console.log('TopBanner.qml',
                            ' ', 'Image <',
                            ' ', 'MouseArea',
                            ' ','onClicked',
                            ' ','m_MainPage_ListView_ref.currentIndex:',m_MainPage_ListView_ref.currentIndex,
                            ' ','m_MainPage_ListView_ref.count:',m_MainPage_ListView_ref.count);
            }//onClicked
        }//MouseArea
    }//Image

    //"Financial Eye"
    Item
    {// 将相关组件放在一个Item容器中 "Financial Eye"
        id: m_Item_text_Financial_Eye
        // 容器的尺寸由组件决定
        width: m_Text_Financial_Eye.width
        height: m_Text_Financial_Eye.height
        anchors.horizontalCenter: id_qml_TopBanner.horizontalCenter
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter

        Text
        {// Stocqt
            id: m_Text_Financial_Eye
            anchors.verticalCenter: m_Item_text_Financial_Eye.verticalCenter
            color: "#ffffff"
            font.family: "Abel"
            font.pointSize: id_qml_TopBanner.height - 10
            text: "Financial Eye"
        }
    }//Item



    //">"
    Image
    {
        id: m_Image_right_arrow
        source:"qrc:///imgfile/images/icon_right_arrow.png"
        anchors.right: id_qml_TopBanner.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter
        //第一个主页面不显示 其余页面都要显示
        //visible: m_List_PageView.currentIndex > 0 ? true : false
        visible: true

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {


                //0 1 2 < 3
                if (m_MainPage_ListView_ref.currentIndex < m_MainPage_ListView_ref.count)
                {
                    if (m_MainPage_ListView_ref.currentIndex === m_MainPage_ListView_ref.count - 1)
                    {
                        m_MainPage_ListView_ref.currentIndex = 0;//back to begin page
                    }
                    else
                    {
                       m_MainPage_ListView_ref.currentIndex = m_MainPage_ListView_ref.currentIndex + 1;
                    }
                }

                console.log('TopBanner.qml',
                            ' ', 'Image >',
                            ' ', 'MouseArea',
                            ' ','onClicked',
                            ' ','m_MainPage_ListView_ref.currentIndex:',m_MainPage_ListView_ref.currentIndex,
                            ' ','m_MainPage_ListView_ref.count:',m_MainPage_ListView_ref.count);

            }//onClicked


        }//MouseArea
    }//Image


}//Rectangle 导航栏


