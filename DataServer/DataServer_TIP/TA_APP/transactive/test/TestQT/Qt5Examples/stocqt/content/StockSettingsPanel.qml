import QtQuick 2.0

Rectangle
{
    id: id_qml_StockSettingsPanel
    width: 440
    height: 160
    color: "transparent"

    // 对外的标志位
    property bool drawOpenPrice: openButton.buttonEnabled
    property bool drawClosePrice: closeButton.buttonEnabled
    property bool drawHighPrice: highButton.buttonEnabled
    property bool drawLowPrice: lowButton.buttonEnabled

    // 各曲线的颜色设置
    property string openColor: "#face20"
    property string closeColor: "#14aaff"
    property string highColor: "#80c342"
    property string lowColor: "#f30000"
    // 成交量绘制颜色
    property string volumeColor: "#14aaff"

    Text
    {//"Open"
        id: openText
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.top: id_qml_StockSettingsPanel.top
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 19
        text: "Open"
    }

    Text
    {//"Close"
        id: closeText
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.top: openText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 19
        text: "Close"
    }

    Text
    {// "High"
        id: highText
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.top: closeText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 19
        text: "High"
    }

    Text
    {//"Low"
        id: lowText
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.top: highText.bottom
        anchors.topMargin: 10
        color: "#000000"
        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 19
        text: "Low"
    }

    Rectangle
    {
        height: 4
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.leftMargin: 114
        anchors.right: openButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: openText.verticalCenter
        color: openColor
    }

    Rectangle
    {
        height: 4
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.leftMargin: 114
        anchors.right: closeButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: closeText.verticalCenter
        color: closeColor
    }

    Rectangle
    {
        height: 4
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.leftMargin: 114
        anchors.right: highButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: highText.verticalCenter
        color: highColor
    }

    Rectangle
    {
        height: 4
        anchors.left: id_qml_StockSettingsPanel.left
        anchors.leftMargin: 114
        anchors.right: lowButton.left
        anchors.rightMargin: 65
        anchors.verticalCenter: lowText.verticalCenter
        color: lowColor
    }

    CheckBox
    {                             // 自定义的CheckBox，提供了属性buttonEnabled表明是否被checked
        id: openButton
        buttonEnabled: false
        anchors.verticalCenter: openText.verticalCenter
        anchors.right: id_qml_StockSettingsPanel.right
        anchors.rightMargin: 40
    }

    CheckBox
    {
        id: closeButton
        buttonEnabled: false
        anchors.verticalCenter: closeText.verticalCenter
        anchors.right: id_qml_StockSettingsPanel.right
        anchors.rightMargin: 40
    }

    CheckBox
    {
        id: highButton
        buttonEnabled: true
        anchors.verticalCenter: highText.verticalCenter
        anchors.right: id_qml_StockSettingsPanel.right
        anchors.rightMargin: 40
    }

    CheckBox
    {
        id: lowButton
        buttonEnabled: true
        anchors.verticalCenter: lowText.verticalCenter
        anchors.right: id_qml_StockSettingsPanel.right
        anchors.rightMargin: 40
    }
}
