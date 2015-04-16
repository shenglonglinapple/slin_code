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




    Rectangle
    {
        id:m_Rectangle_UsrSearch

        width:parent.width;
        height:20

        anchors.top: parent.top
        //anchors.bottom: m_BorderImage_footer.top;
        //anchors.fill: parent

        color: "cyan";

        Rectangle
        {
            id:m_Rectangle_UsrSearch_InputText

            width:parent.width*(3/4);
            height:parent.height

            anchors.left: parent.left

            color: "gray";


            TextInput
            {
                id: m_TextInput_UsrInputText

                anchors.fill: parent
                //anchors.right: m_Buttom_Search.left

                clip: true
                anchors.leftMargin: 5
                anchors.rightMargin: 5
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: parent.height/2
                focus:true

                /*
                MouseArea
                {
                      anchors.fill: parent
                      onClicked:
                      {
                          console.log('UsrSearchStockListView.qml',
                                      ' ','TextInput MouseArea onClicked use Qt.inputMethod.show()');
                          m_TextInput_UsrInputText.focus = true;
                          Qt.inputMethod.show();
                      }
                }*/

                Text
                {
                    id: m_Text_SampleSearchText
                    anchors.fill: parent
                    verticalAlignment: Text.AlignVCenter
                    visible: !(parent.text.length || parent.inputMethodComposing)
                    font: parent.font
                    text: "input stock id"
                    color: "red"
                }//Text

                onAccepted:
                {
                    console.log('UsrSearchStockListView.qml',
                                ' ','TextInput onAccepted',
                                ' ','process accepted() use Qt.inputMethod.hide()');
                    m_str_SeachStock = m_TextInput_UsrInputText.text;

                    //Qt.inputMethod.hide();
                    m_UsrSearchStockListModel.clear();
                    m_UsrSearchStockListModel.fun_db_select_from_TableTotalStock(m_str_SeachStock);

                }//onAccepted

            }//TextInput
        }//FocusScope

        //Buttom_Search
        Button
        {
            id: m_Buttom_Search

            anchors.topMargin: 5
            anchors.left: m_Rectangle_UsrSearch_InputText.right
            anchors.right: parent.right
            anchors.rightMargin: 10

            text: "Search"
            buttonEnabled: true
            onClicked:
            {
                console.log('UsrSearchStockListView.qml',
                            ' ','Button.onClicked',
                            ' ','emit accepted()');
                m_TextInput_UsrInputText.accepted();//emit accepted();

            }
        }//Button

    }//Rectangle

    ////////////////////////

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
            //width: parent.width
            //height: 30;//m_Rectangle_StockListDelegate.height;//60
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
        //height:parent.height*(18/20)
        anchors.top: m_Rectangle_UsrSearch.bottom
        anchors.bottom: parent.bottom;
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

}//Rectangle


