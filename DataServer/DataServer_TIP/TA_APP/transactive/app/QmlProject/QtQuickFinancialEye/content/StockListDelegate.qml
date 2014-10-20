import QtQuick 2.0
import QtQuick.Window 2.1
import QtQml.Models 2.1

//work with StockListModel.qml StockListView.qml
//ListView 中每个元素怎样显示
Component
{
    // 委托组件，基本都是布局
    id: id_qml_StockListDelegate;

    Rectangle
    {
        id:m_Rectangle_StockListDelegate;

        width: parent.width;
        height: 128


        color: "transparent";

        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                console.log('StockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','m_listViewStock.currentIndex:', m_listViewStock.currentIndex,
                            ' ','new index:', index);

                //if m_listViewStock.currentIndex the same as index  then will not emit currentIndexChanged
                if (m_listViewStock.currentIndex != index)
                {
                    m_listViewStock.currentIndex = index;//where is index define?????
                }

                // 获取 Id 与 name
                //set value and emit
                m_CurrentUserStockData.m_s_Symbol_current = m_listViewStock.model.get(m_listViewStock.currentIndex).m_s_Symbol;

                console.log('StockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','m_listViewStock.currentIndex:',m_listViewStock.currentIndex,
                            ' ','m_CurrentUserStockData.m_s_Symbol_current:',m_CurrentUserStockData.m_s_Symbol_current);

                //emit signal signalUpdateStockInfo
                console.log('StockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','emit signalUpdateCurrentUserStockData');
                m_Mainpage_ListView.signalUpdateCurrentUserStockData();

                //current show StockListView
                //m_Mainpage_ListView.currentIndex = 0;
                //then show StockDetailView  m_Mainpage_ListView.currentIndex = 1;
                m_Mainpage_ListView.currentIndex = 1;
            }
        }

        //
        Text
        {//Symbol
            id: m_Text_Symbol

            width: 128
            height: 32

            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15

            //color: "#0c34f9"
            color:"blue"
            font.family: "Helvetica";//font.family: "Open Sans"// 我的机器貌似不支持这种字体
            font.pointSize: 20
            font.weight: Font.Bold
            verticalAlignment: Text.AlignVCenter

            text: m_s_Symbol                      


            Component.onCompleted:
            {
                console.log('StockListDelegate.qml',
                            ' ','Text m_s_Symbol',' ',
                            ' ','Component.onCompleted',' ',
                            ' ','index:',index,
                            ' ','m_s_Symbol:',m_s_Symbol);


                m_page_StockListView.fun_Update_RealTimeInfo_byindex(index);

                //set CurrentUserStockData default value
                if (0 == index)
                {
                    m_CurrentUserStockData.m_s_Symbol_current = m_s_Symbol;
                }

            }//Component.onCompleted:

        }//Text


        Text
        {//Name
            id: m_Text_Name

            width: 256
            height: 32

            anchors.top: m_Text_Symbol.bottom
            anchors.left: parent.left
            anchors.leftMargin: 15

            //color: "#000000"
            color:"blue"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 16
            font.bold: false
            elide: Text.ElideRight
            maximumLineCount: 1
            verticalAlignment: Text.AlignVCenter

            text: m_n_Name
        }//Text

        Text
        {
            id: m_Text_LastTradePriceOnly

            width: 256
            height: 32

            anchors.top: parent.top
            anchors.topMargin: 0.3 * parent.height
            anchors.right: parent.right
            anchors.rightMargin: 0.31 * parent.width

            //color: "#000000"
            color: m_c6_Change_Realtime < 0 ? "red" : "green"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: m_l1_Last_Trade_Price_Only

            Component.onCompleted:
            {
                //显示出来后调用这个函数
            }
        }

        Text
        {
            id: m_Text_ChangeRealtime

            width: 128
            height: 32

            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 20

            //color: "#328930"
            color: m_c6_Change_Realtime < 0 ? "red" : "green"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: m_c6_Change_Realtime



            onTextChanged:
            {
                /*
                if (parseFloat(text) >= 0.0)           // 正为绿色，负为红色
                {
                    //color = "#328930";
                    color = "green";
                }
                else
                {
                    //color = "#d40000";
                    color = "red";
                }
                */

            }
        }



        Text
        {
            id: m_Text_ChangeInPercent

            width: 128
            height: 32

            anchors.top: m_Text_Symbol.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20

            //color: "#328930"
            color: m_c6_Change_Realtime < 0 ? "red" : "green"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 18
            font.bold: false
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: m_p2_Change_in_Percent


            onTextChanged:
            {
                /*
                if (parseFloat(text) >= 0.0)
                    color = "#328930";
                else
                    color = "#d40000";
                */
            }
        }

        //Item diff line
        Rectangle
        {
            id: endingLine

            height: 1
            width: m_Rectangle_StockListDelegate.width

            anchors.bottom: m_Rectangle_StockListDelegate.bottom
            anchors.left: m_Rectangle_StockListDelegate.left

            color: "#d7d7d7"
        }

    }//Rectangle Item

}//Component mvc_delegate
