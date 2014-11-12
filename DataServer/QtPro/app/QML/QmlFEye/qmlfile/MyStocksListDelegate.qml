import QtQuick 2.0

//ListView 中每个元素怎样显示
Component
{
    // 委托组件，基本都是布局
    id: id_qml_MyStocksListDelegate;

    Item
    {
        id:m_id_Item_MyStocksListDelegate;

        width: parent.width;
        height: 60;

        property real m_n_rect_width_baseinfo : parent.width * (1 / 3);
        property real m_n_rect_width_priceinfo : parent.width * (1 / 3);
        property real m_n_rect_width_changeinfo : parent.width * (1 / 5);

        property real m_n_details_opacity : 0;//0.0-1.0

        property real m_n_height_nomal : 60;
        property real m_n_height_details : 200;


        Rectangle
        {
            id:m_id_Rectangle_BaseInfo

            width:m_n_rect_width_baseinfo
            height: m_n_height_nomal;

            anchors.top: parent.top
            //anchors.bottom: parent.bottom
            anchors.left: parent.left
            color:"transparent"
            //color:"LightYellow"

            Text
            {
                id:m_id_Text_Name
                text: m_n_Name
                font.family: "Abel";//"Abel" Helvetica
                font.bold: true;
                font.pointSize: 20
                color: "blue"
            }
            Text
            {
                id:m_id_Text_Symbol
                anchors.top: m_id_Text_Name.bottom
                text: m_s_Symbol
                font.family: "Abel";//"Abel" Helvetica
                font.bold: true;
                font.pointSize: 10
                color: "blue"
            }

            Component.onCompleted:
            {
                console.log("MyStocksListDelegate.qml",
                            " ", "Text Component.onCompleted",
                            " ", "fun_Update_RealTimeInfo_byindex index=", index);
                //id_qml_MyStocksListDelegate.ListView.view
                id_qml_MyStocksListView.fun_Update_RealTimeInfo_byindex(index);

            }//Component.onCompleted:
        }//m_id_Rectangle_BaseInfo


        Rectangle
        {
            id:m_id_Rectangle_PriceInfo
            width:m_n_rect_width_priceinfo
            height: m_n_height_nomal;
            anchors.top: parent.top
            //anchors.bottom: parent.bottom
            anchors.left: m_id_Rectangle_BaseInfo.right
            color:"transparent"
            //color:"Yellow"

            Text
            {
                id:m_id_Text_PriceInfo
                anchors.horizontalCenter: m_id_Rectangle_PriceInfo.horizontalCenter
                anchors.verticalCenter: m_id_Rectangle_PriceInfo.verticalCenter
                text: m_l1_Last_Trade_Price_Only
                font.family: "Abel";//"Abel" Helvetica
                font.bold: true;
                font.pointSize: 20
                color: m_c6_Change_Realtime < 0 ? "red" : "green"
            }

        }//m_id_Rectangle_PriceInfo

        Rectangle
        {
            id:m_id_Rectangle_ChangeInfo
            width:m_n_rect_width_changeinfo
            height: m_n_height_nomal;
            anchors.top: parent.top
            //anchors.bottom: parent.bottom

            //anchors.left: m_id_Rectangle_PriceInfo.right
            anchors.right: parent.right
            //color:"transparent"
            color: m_c6_Change_Realtime < 0 ? "red" : "green"

            Text
            {
                id:m_id_Text_ChangeInfo
                anchors.horizontalCenter: m_id_Rectangle_ChangeInfo.horizontalCenter
                anchors.verticalCenter: m_id_Rectangle_ChangeInfo.verticalCenter
                font.family: "Helvetica";//"Abel"
                font.bold: true;
                font.pointSize: 20
                text: m_c6_Change_Realtime;//m_c6_Change_Realtime;
                color:"white"
                //color: m_c6_Change_Realtime < 0 ? "red" : "green"


            }//m_id_Text_ChangeInfo

            MouseArea
            {
                anchors.fill: m_id_Rectangle_ChangeInfo;
                onClicked:
                {
                    if (m_id_Rectangle_ChangeInfo.state == "states_show_Change_in_Percent")
                    {
                        m_id_Rectangle_ChangeInfo.state = "states_show_Change_Realtime";
                        console.log("MyStocksListDelegate.qml",
                                    " ", "m_id_Rectangle_ChangeInfo.state=", m_id_Rectangle_ChangeInfo.state);
                    }
                    else
                    {
                        m_id_Rectangle_ChangeInfo.state = "states_show_Change_in_Percent";//first
                        console.log("MyStocksListDelegate.qml",
                                    " ", "m_id_Rectangle_ChangeInfo.state=", m_id_Rectangle_ChangeInfo.state);

                    }
                }
            }//MouseArea

            states:
            [
                State
                {
                    name: "states_show_Change_in_Percent"
                    //PropertyChanges { target: m_id_Text_Name; color:"green"; }
                    PropertyChanges { target: m_id_Text_ChangeInfo; text:m_p2_Change_in_Percent; }
                },
                State
                {
                    name: "states_show_Change_Realtime"
                    //PropertyChanges { target: m_id_Text_Name; color:"red";}//font.pointSize:25;
                    PropertyChanges { target: m_id_Text_ChangeInfo; text:m_c6_Change_Realtime; }
                }
            ]//states

            transitions: Transition
            {
                // Make the state changes smooth
                ParallelAnimation
                {
                    ColorAnimation
                    {
                        property: "color";
                        duration: 100
                    }//ColorAnimation
                    NumberAnimation
                    {
                        duration: 100;
                        properties: "font.pointSize,m_n_details_opacity,height,width"
                    }//NumberAnimation
                }//ParallelAnimation
            }//transitions: Transition

        }//m_id_Rectangle_ChangeInfo

        Row
        {
            id:m_id_Row_DetailInfo
            width:m_id_Item_MyStocksListDelegate.width
            anchors.bottom: m_id_Item_MyStocksListDelegate.bottom;
            spacing: 10;
            opacity:m_id_Item_MyStocksListDelegate.m_n_details_opacity;
            Text
            {
                text:"AAAA";
            }
            Text
            {
                text:"BBB";
            }
            Text
            {
                text:"CCC";
            }
        }//m_id_Row_DetailInfo


        MouseArea
        {
            x:0
            y:0
            width: m_id_Item_MyStocksListDelegate.width * (2/3);
            height:m_id_Item_MyStocksListDelegate.height
            //anchors.left: m_id_Item_MyStocksListDelegate.left
            //anchors.fill: m_id_Item_MyStocksListDelegate;
            onClicked:
            {
                if (m_id_Item_MyStocksListDelegate.state == "states_detail")
                {
                    m_id_Item_MyStocksListDelegate.state = "states_nomal";
                    console.log("MyStocksListDelegate.qml",
                                " ", "m_id_Item_MyStocksListDelegate.state=", m_id_Item_MyStocksListDelegate.state);
                }
                else
                {
                    m_id_Item_MyStocksListDelegate.state = "states_detail";
                    console.log("MyStocksListDelegate.qml",
                                " ", "m_id_Item_MyStocksListDelegate.state=", m_id_Item_MyStocksListDelegate.state);

                }
            }
        }//MouseArea



        states:
        [
            State
            {
                name: "states_detail"
                PropertyChanges { target: m_id_Item_MyStocksListDelegate; height:m_n_height_details; }
                PropertyChanges { target: m_id_Item_MyStocksListDelegate; m_n_details_opacity: 1;} // Make details visible
            },
            State
            {
                name: "states_nomal"
                PropertyChanges { target: m_id_Item_MyStocksListDelegate; height:m_n_height_nomal; }
            }
        ]//states


        transitions: Transition
        {
            // Make the state changes smooth
            ParallelAnimation
            {
                ColorAnimation
                {
                    property: "color";
                    duration: 500;
                }//ColorAnimation
                NumberAnimation
                {
                    duration: 500;
                    properties: "m_n_details_opacity,font.pointSize,height,width"
                }//NumberAnimation
            }//ParallelAnimation
        }//transitions: Transition

    }//Item m_Item_MyStocksListDelegate

}//Component



