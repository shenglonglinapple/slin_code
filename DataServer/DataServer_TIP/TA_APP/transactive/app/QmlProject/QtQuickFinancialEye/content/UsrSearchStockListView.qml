import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with StockListDelegate.qml StockListModel.qml
Rectangle
{
    id: id_qml_UsrSearchStockListView

    width:parent.width;
    //anchors.top: parent.top
    //anchors.bottom: parent.bottom

    color: "white"

    property string m_str_SeachStock : "002024";



    //mvc data
    UsrSearchStockListModel
    {
        id: m_UsrSearchStockListModel
        //no width height
    }

    //mvc 怎样显示这些数据
    UsrSearchStockListDelegate
    {
        id: m_UsrSearchStockListDelegate
        //no width height
    }

    //Component for ListView
    Component
    {
        id: m_Component_highlight
        //no width height

        Rectangle
        {
            id:m_Rectangle_highlight;
            width: parent.width
            height: 30;//m_Rectangle_StockListDelegate.height;//60
            color: "#eeeeee";
            //color: "lightsteelblue";
            //color: "red";
        }
    }

    ListView
    {
        //0
        id: m_ListView_UsrSearchStock
        //1
        width:parent.width;
        height:parent.height*(18/20)
        anchors.top: parent.top
        //anchors.bottom: m_BorderImage_footer.top;
        //anchors.fill: parent

        clip: true// clip以延时加载数据
        keyNavigationWraps: true
        highlightMoveDuration: 0
        focus: true
        snapMode: ListView.SnapToItem
        model: m_UsrSearchStockListModel; // 定义model
        delegate: m_UsrSearchStockListDelegate;//显示Item
        highlight: m_Component_highlight;
        currentIndex: 0;


        onCurrentIndexChanged:
        {// 当该ListView中的某个项目被选中

        }//onCurrentIndexChanged



    }//ListView






    //user input
    BorderImage
    {
        id: m_BorderImage_footer

        width:parent.width;
        //height:parent.height*(1/10)

        anchors.top: m_ListView_UsrSearchStock.bottom
        anchors.bottom: parent.bottom
        source: "qrc:///imgfile/images/delegate.png"
        border.left: 5;
        border.top: 5;
        border.right: 5;
        border.bottom: 5;

        Rectangle
        {
            y: -1 ;
            height: 1
            width: parent.width
            color: "#bbb"
        }
        Rectangle
        {
            y: 0 ;
            height: 1
            width: parent.width
            color: "white"
        }


        BorderImage
        {
            id: m_BorderImage_TextField

            anchors.left: parent.left
            anchors.right: m_Item_addButton.left
            anchors.verticalCenter: parent.verticalCenter
            anchors.margins: 5
            source:"qrc:///imgfile/images/textfield.png"
            border.left: 5 ;
            border.right: 5 ;
            border.top: 5 ;
            border.bottom: 5;

            TextInput
            {
                id: m_TextInput_textInput
                anchors.fill: parent
                clip: true
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.height/2
                Text
                {
                    id: m_Text_placeholderText
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    visible: !(parent.text.length || parent.inputMethodComposing)
                    font: parent.font
                    text: "002024"
                    color: "#aaa"
                }//Text

                onAccepted:
                {
                    //m_TextInput_textInput.text = ""
                }//onAccepted
            }//TextInput
        }//BorderImage

        Item
        {
            id: m_Item_addButton

            width: m_BorderImage_TextField.height;
            height: m_BorderImage_TextField.height;
            //anchors.margins: 5
            anchors.right: parent.right
            anchors.rightMargin: 10
            anchors.verticalCenter: parent.verticalCenter
            enabled: m_TextInput_textInput.text.length

            Image
            {
                source: m_MouseArea_addMouseArea.pressed ? "qrc:///imgfile/images/add_icon_pressed.png" : "qrc:///imgfile/images/add_icon.png"
                anchors.centerIn: parent
                opacity: enabled ? 1 : 0.5
            }//Image

            MouseArea
            {
                id: m_MouseArea_addMouseArea
                anchors.fill: parent
                onClicked:
                {
                    m_TextInput_textInput.accepted();//emit accepted();
                }

            }//MouseArea

        }//Item
    }//BorderImage





}//Rectangle


