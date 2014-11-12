import QtQuick 2.0

Rectangle
{
    width: 100
    height: 62
    color: "white"

    property alias text: m_id_Text_txt.text


    Text
    {
        id: m_id_Text_txt

        anchors.centerIn: parent

        font.family: "Helvetica";//font.family: "Open Sans"
        font.pointSize: 10
        font.weight: Font.DemiBold

        color: "#14aaff"

    }//Text

}//Rectangle
