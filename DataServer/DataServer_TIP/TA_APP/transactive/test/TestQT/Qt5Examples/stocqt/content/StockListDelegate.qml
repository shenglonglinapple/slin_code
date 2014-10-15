import QtQuick 2.0

//work with StockListModel.qml StockListView.qml
Component
{
    id: id_qml_StockListDelegate;

    Rectangle
    {                    // 委托组件，基本都是布局，不多说了
        height: 102
        width: parent.width;
        color: "transparent";

        MouseArea
        {
            anchors.fill: parent;
            onClicked:
            {
                console.log('StockListDelegate.qml',
                            ' ','onClicked:',
                            ' ','m_listViewStock.currentIndex:', m_listViewStock.currentIndex,
                            ' ','index:', index);
                m_listViewStock.currentIndex = index;//where is index define?????
            }
        }

        Text
        {
            id: stockIdText
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.left: parent.left
            anchors.leftMargin: 15
            width: 125
            height: 40
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
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 0.31 * parent.width
            width: 190
            height: 40
            color: "#000000"
            font.family: "Helvetica";//font.family: "Open Sans"
            font.pointSize: 20
            font.bold: true
            horizontalAlignment: Text.AlignRight
            verticalAlignment: Text.AlignVCenter
            text: value
            Component.onCompleted:
            {//value=close value
                console.log('StockListDelegate.qml',
                            ' ','Text value',' ',
                            ' ','Component.onCompleted',' ',
                            ' ','index:',index);
                m_listViewStock.getCloseValue(index);
            }
        }

        Text
        {
            id: stockValueChangeText
            anchors.top: parent.top
            anchors.topMargin: 15
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 135
            height: 40
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
            anchors.top: stockIdText.bottom
            anchors.left: parent.left
            anchors.leftMargin: 15
            width: 330
            height: 30
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
            anchors.top: stockIdText.bottom
            anchors.right: parent.right
            anchors.rightMargin: 20
            width: 120
            height: 30
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
            anchors.bottom: parent.bottom
            anchors.left: parent.left
            height: 1
            width: parent.width
            color: "#d7d7d7"
        }
    }

}//Component mvc_delegate
