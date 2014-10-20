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
        height: 102
        width: parent.width;

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
        {
            id: m_Text_Symbol

            width: 125
            height: 40

            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15

            color: "#0c34f9"
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
        {
            id: m_Text_LastTradePriceOnly

            width: 190
            height: 40

            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 0.31 * parent.width

            color: "#000000"
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

            width: 135
            height: 40

            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 20

            color: "#328930"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: m_c6_Change_Realtime



            onTextChanged:
            {
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
            }
        }

        Text
        {
            id: m_Text_Name

            width: 330
            height: 30

            anchors.top: m_Text_Symbol.bottom
            anchors.left: parent.left
            anchors.leftMargin: 15

            color: "#000000"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 16
            font.bold: false
            elide: Text.ElideRight
            maximumLineCount: 1
            verticalAlignment: Text.AlignVCenter

            text: m_n_Name


        }

        Text
        {
            id: m_Text_ChangeInPercent

            width: 120
            height: 30

            anchors.top: m_Text_Symbol.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20

            color: "#328930"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 18
            font.bold: false
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: m_p2_Change_in_Percent


            onTextChanged:
            {
                if (parseFloat(text) >= 0.0)
                    color = "#328930";
                else
                    color = "#d40000";
            }
        }

        Rectangle
        {
            id: endingLine

            height: 1
            width: parent.width

            anchors.bottom: parent.bottom
            anchors.left: parent.left

            color: "#d7d7d7"
        }
    }

}//Component mvc_delegate
