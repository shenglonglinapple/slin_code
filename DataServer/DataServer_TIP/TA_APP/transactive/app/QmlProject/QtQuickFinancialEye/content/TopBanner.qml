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

    property real m_n_Image_arrow_width: id_qml_TopBanner.height/2;
    property real m_n_Image_arrow_height: id_qml_TopBanner.height/2;
    property real m_n_Image_arrow_Margin: id_qml_TopBanner.height/2;

    //"<"
    Image
    {
        //0
        id: m_Image_left_arrow

        //1
        height : m_n_Image_arrow_height;
        width : m_n_Image_arrow_width;

        anchors.left: id_qml_TopBanner.left
        anchors.leftMargin: m_n_Image_arrow_Margin;
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
    Rectangle
    {// 将相关组件放在一个Item容器中 "Financial Eye"
        id: m_Item_text_Financial_Eye
        // 容器的尺寸由组件决定
        width: m_Text_Financial_Eye.width;//指定了width才能居中
        height: id_qml_TopBanner.height
        anchors.horizontalCenter: id_qml_TopBanner.horizontalCenter
        anchors.verticalCenter: id_qml_TopBanner.verticalCenter

        color:"Peru"

        Text
        {// Stocqt
            id: m_Text_Financial_Eye

            anchors.verticalCenter: m_Item_text_Financial_Eye.verticalCenter

            color: "Gold";//"#ffffff"
            font.family: "Abel"
            font.pointSize: m_Item_text_Financial_Eye.height/2;// - 10
            //text: "Financial Eye"
            text: m_CurrentUserStockData.m_str_title_current;
        }
    }//Item



    //">"
    Image
    {
        id: m_Image_right_arrow


        height: m_n_Image_arrow_height
        width:m_n_Image_arrow_width

        anchors.right: id_qml_TopBanner.right
        anchors.rightMargin: m_n_Image_arrow_Margin
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


