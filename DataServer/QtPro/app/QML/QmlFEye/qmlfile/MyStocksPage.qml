import QtQuick 2.0

Rectangle
{
    id: id_qml_MyStocksPage

    width: 100
    height: 62

    color: "lightsteelblue"



    MyStocksListView
    {
        id:m_id_MyStocksListView;
        anchors.fill: parent;

    }//MyStocksListView

}//Rectangle
