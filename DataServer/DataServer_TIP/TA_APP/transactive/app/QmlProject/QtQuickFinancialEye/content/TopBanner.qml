import QtQuick 2.0
import QtQuick.Window 2.1               
import QtQml.Models 2.1


//导航栏
Rectangle
{
    //0
    id: id_qml_TopBanner
    //1
    width: parent.width
    height: 20
    anchors.top: parent.top

    //2
    color: "#000000";

    //"<"
    Image
    {
        //0
        id: m_Image_left_arrow

        //1
        height: id_qml_TopBanner.height
        width:20

        anchors.left: id_qml_TopBanner.left
        anchors.leftMargin: 10
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter

        source:"qrc:///imgfile/images/icon_left_arrow.png"

        //第一个主页面不显示 其余页面都要显示
        //visible: true
        visible : m_Mainpage_ListView.currentIndex == 0 ? false : true

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                //0 1 2 < 3
                if (m_Mainpage_ListView.currentIndex >= 0)
                {
                    if (m_Mainpage_ListView.currentIndex === 0)
                    {
                        m_Mainpage_ListView.currentIndex = m_Mainpage_ListView.count - 1;//go to last page
                    }
                    else
                    {
                       m_Mainpage_ListView.currentIndex = m_Mainpage_ListView.currentIndex - 1;
                    }
                }

                console.log('TopBanner.qml',
                            ' ', 'Image <',
                            ' ', 'MouseArea',
                            ' ','onClicked',
                            ' ','m_MainPage_ListView_ref.currentIndex:',m_Mainpage_ListView.currentIndex,
                            ' ','m_MainPage_ListView_ref.count:',m_Mainpage_ListView.count);
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
            font.pointSize: id_qml_TopBanner.height/2;// - 10
            //text: "Financial Eye"
            text: m_CurrentUserStockData.m_str_title_current;
        }
    }//Item



    //">"
    Image
    {
        id: m_Image_right_arrow


        height: id_qml_TopBanner.height
        width:20

        anchors.right: id_qml_TopBanner.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter

        source:"qrc:///imgfile/images/icon_right_arrow.png"
        //第一个主页面不显示 其余页面都要显示
        //visible: true
        visible : m_Mainpage_ListView.currentIndex == 2 ? false : true

        MouseArea
        {
            anchors.fill: parent
            onClicked:
            {
                //0 1 2 < 3
                if (m_Mainpage_ListView.currentIndex < m_Mainpage_ListView.count)
                {
                    if (m_Mainpage_ListView.currentIndex === m_Mainpage_ListView.count - 1)
                    {
                        m_Mainpage_ListView.currentIndex = 0;//back to begin page
                    }
                    else
                    {
                       m_Mainpage_ListView.currentIndex = m_Mainpage_ListView.currentIndex + 1;
                    }
                }

                console.log('TopBanner.qml',
                            ' ', 'Image >',
                            ' ', 'MouseArea',
                            ' ','onClicked',
                            ' ','m_MainPage_ListView_ref.currentIndex:',m_Mainpage_ListView.currentIndex,
                            ' ','m_MainPage_ListView_ref.count:',m_Mainpage_ListView.count);

            }//onClicked


        }//MouseArea
    }//Image


}//Rectangle 导航栏


