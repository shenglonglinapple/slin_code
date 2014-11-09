import QtQuick 2.3
import QtQuick.Controls 1.2

import "./qmlfile"

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    menuBar: MenuBar {
        Menu {
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }
    }//menuBar: MenuBar



    PageListView
    {
        id: m_PageListView;
        anchors.fill: parent;

        onSignalUpdateCurrentUserStockData:
        {
            console.log("main.qml",
                        " ", "PageListView",
                        " ", "onSignalUpdateCurrentUserStockData");

        }//onSignalUpdateCurrentUserStockData
    }//PageListView










}//ApplicationWindow



//doc begin
/*
  qsTr("Hello World");
  qsTr("%1").arg("Hello World")
*/
//doc end














