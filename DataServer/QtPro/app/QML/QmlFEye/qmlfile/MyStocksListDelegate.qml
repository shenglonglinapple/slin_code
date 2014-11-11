import QtQuick 2.0

//ListView 中每个元素怎样显示
Component
{
    // 委托组件，基本都是布局
    id: id_qml_MyStocksListDelegate;

    Item
    {
        id:m_Item_MyStocksListDelegate;

        width: parent.width;
        height: 60;

        property real detailsOpacity : 0;//0.0-1.0


        Row
        {
            id:m_Row_MyStocksListDelegate;
            width: parent.width;
            height: parent.height;
            spacing: 10

            Text
            {
                text: m_n_Name
                font.bold: true;
                font.pointSize: 10
            }

            Text
            {
                text: m_s_Symbol
                font.bold: true;
                font.pointSize: 10
            }

            Text
            {
                text: m_l1_Last_Trade_Price_Only
                font.bold: true;
                font.pointSize: 10
            }

            Text
            {
                text: m_c6_Change_Realtime
                font.bold: true;
                font.pointSize: 10
            }

            Text
            {
                text: m_p2_Change_in_Percent
                font.bold: true;
                font.pointSize: 10
            }


        }//Row m_Row_MyStocksListDelegate



    }//Item m_Item_MyStocksListDelegate

}//Component



