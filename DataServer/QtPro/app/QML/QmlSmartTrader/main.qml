import QtQuick 2.3
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.1

// 添加其他qml文件路径
import "qmlfile"

ApplicationWindow
{
    visible: true
    width: 640
    height: 480
    title: qsTr("QmlSmartTrader")

    menuBar: MenuBar{
        Menu{
            id:m_id_Menu_File
            title: qsTr("File")
            MenuItem {
                text: qsTr("&Open")
                onTriggered: console.log("Open action triggered");
            }
            MenuItem {
                text: qsTr("Exit")
                onTriggered: Qt.quit();
            }
        }//m_id_Menu_File

        Menu{
            id:m_id_Menu_Indicators
            title: qsTr("Indicators")
        }//m_id_Menu_Indicators
        Menu{
            id:m_id_Menu_Themes
            title: qsTr("Themes")
        }//m_id_Menu_Themes
        Menu{
            id:m_id_Menu_Language
            title: qsTr("Language")
        }//m_id_Menu_Language
        Menu{
            id:m_id_Menu_Settings
            title: qsTr("Settings")
        }//m_id_Menu_Settings
        Menu{
            id:m_id_Menu_About
            title: qsTr("About")
        }//m_id_Menu_About
    }//menuBar: MenuBar


    toolBar: ToolBar{
        RowLayout{
            anchors.fill: parent
            ToolButton{
                text:"m1";
            }
            ToolButton{
                text:"m5";
            }
            ToolButton{
                text:"m15";
            }
            ToolButton{
                text:"m30";
            }
            ToolButton{
                text:"H1";
            }
            ToolButton{
                text:"D";
            }

            Item {
                Layout.fillWidth: true
            }
            /*
            CheckBox{
                text: "Enabled"
                checked: true
                Layout.alignment: Qt.AlignRight
            }
            */

        }//RowLayout
    }//toolBar: ToolBar


    SmartInfoWindow{
        id:m_id_SmartInfoWindow;
    }

    OrderInfoWindow{
        id:m_id_OrderInfoWindow;
        anchors.top:m_id_SmartInfoWindow.bottom


    }

}//ApplicationWindow
