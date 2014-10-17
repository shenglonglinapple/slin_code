import QtQuick 2.0

Rectangle
{
    //0
    id: id_qml_Button
    //1
    width: Math.max(64, m_Text_txt.width + 16)
    height: 32

    //设置txt.text的属性别名为text，这样Rectangle就不用再声明一个属性以访问txt的text
    property alias text: m_Text_txt.text
    property bool buttonEnabled: false

    signal clicked



    color: "transparent"

    MouseArea
    {
        anchors.fill: parent

        onClicked:
        {
            id_qml_Button.clicked();
        }

    }//MouseArea

    Text
    {
        id: m_Text_txt

        anchors.centerIn: parent

        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 19
        font.weight: Font.DemiBold

        color: id_qml_Button.buttonEnabled ? "#000000" : "#14aaff"

    }//Text
}//Rectangle
