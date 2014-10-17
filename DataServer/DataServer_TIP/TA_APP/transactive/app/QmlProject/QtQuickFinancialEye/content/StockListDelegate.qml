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
                m_PageListData.m_str_stockId = m_listViewStock.model.get(m_listViewStock.currentIndex).stockId;
                m_PageListData.m_str_stockName = m_listViewStock.model.get(m_listViewStock.currentIndex).name;
                m_PageListData.fun_setDefaultValue();
                console.log('StockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','m_listViewStock.currentIndex:',m_listViewStock.currentIndex,
                            ' ','m_PageListData.m_str_stockId:',m_PageListData.m_str_stockId,
                            ' ','m_PageListData.m_str_stockName:',m_PageListData.m_str_stockName);

                //emit signal signalUpdateStockInfo
                console.log('StockListDelegate.qml',
                            ' ','MouseArea onClicked',
                            ' ','emit signalUpdateStockInfo');
                m_Mainpage_ListView.signalUpdateStockInfo();
                //current show StockListView
                //m_Mainpage_ListView.currentIndex = 0;
                //then show StockDetailView  m_Mainpage_ListView.currentIndex = 1;
                m_Mainpage_ListView.currentIndex = 1;
            }
        }

        Text
        {
            id: stockIdText

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

            text: stockId
        }

        Text
        {
            id: stockValueText

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

            text: value

            Component.onCompleted:
            {//value=close value
                //显示出来后调用这个函数
                console.log('StockListDelegate.qml',
                            ' ','Text value',' ',
                            ' ','Component.onCompleted',' ',
                            ' ','index:',index);

                //m_listViewStock.getCloseValue(index);
            }
        }

        Text
        {
            id: stockValueChangeText

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

            text: change

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
            id: stockNameText

            width: 330
            height: 30

            anchors.top: stockIdText.bottom
            anchors.left: parent.left
            anchors.leftMargin: 15

            color: "#000000"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 16
            font.bold: false
            elide: Text.ElideRight
            maximumLineCount: 1
            verticalAlignment: Text.AlignVCenter

            text: name
        }

        Text
        {
            id: stockValueChangePercentageText

            width: 120
            height: 30

            anchors.top: stockIdText.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20

            color: "#328930"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 18
            font.bold: false
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter

            text: changePercentage

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
