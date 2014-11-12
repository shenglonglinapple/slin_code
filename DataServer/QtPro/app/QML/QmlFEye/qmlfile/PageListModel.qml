import QtQuick 2.0
import QtQml.Models 2.1



ObjectModel
{
    id: id_qml_PageListModel


    //index=0
    MyStocksPage
    {//
        id: m_id_page_SamplePage;
        width: id_qml_PageListView.width
        height: id_qml_PageListView.height
        //text: qsTr("MyStocksPage");
    }

    //index=1
    SamplePage
    {//
        id: m_id_page_SamplePage_1;
        width: id_qml_PageListView.width
        height: id_qml_PageListView.height
        text:qsTr("index=1");
    }

    //index=2
    SamplePage
    {//
        id: m_id_page_SamplePage_2;
        width: id_qml_PageListView.width
        height: id_qml_PageListView.height
        text:qsTr("index=2");
    }

}//model: ObjectModel

